#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/select.h>

int sockfd = -1;
int maxfd = 0;
int maxid = 0;
int cli_fd[4096] = {-1};
int cli_fd_id[4096] = {-1};
char *cli_msg[4096] = {0};

void	exitclean()
{
	if (sockfd != -1)
		close(sockfd);
	write(2, "Fatal error\n", strlen("Fatal error\n"));
	exit(1);
}

void writeToAll(int fd, char *msg)
{
	for (int i = 0; i < maxid; i++)
	{
		if (cli_fd[i] != -1 && cli_fd[i] != fd)
		{
			write(cli_fd[i], msg, strlen(msg));
		}
	}
}

void setmax()
{
	for (int i = 0; i < maxid; i++)
	{
		if (cli_fd[i] > maxfd)
		{
			maxfd = cli_fd[i];
		}
	}	
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main(int ac, char **av) {

	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", strlen("Wrong number of arguments\n"));
		exit(1);
	}
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1)
		exitclean();
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = 16777343; //127.0.0.1
	int lul = atoi(av[1]);
	int a = lul >> 8;
	int b = lul & 0xFF;
	lul = b << 8 | a;
	servaddr.sin_port = lul; 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		exitclean();
	if (listen(sockfd, 10) != 0)
		exitclean();
	
	fd_set setall, setwrite, setread;
	FD_ZERO(&setall);
	FD_SET(sockfd, &setall);
	maxfd = sockfd;
	char buf[50];
	while (1)
	{
		setwrite = setread = setall;
		if (select(maxfd + 1, &setread, &setwrite, 0, 0) <= 0)
		{
			;
		}
		else
		{
			for (int i = 0; i <= maxfd; i++)
			{
				if (FD_ISSET(i, &setread))
				{
					if (i == sockfd)
					{
						connfd = accept(sockfd, 0, 0);
						if (connfd != -1)
						{
							int id = maxid++;
							cli_fd[id] = connfd;
							cli_fd_id[connfd] = id;
							bzero(&buf, sizeof(buf));
							sprintf(buf, "server: client %d just arrived\n", id);
							writeToAll(connfd, buf);
							FD_SET(connfd, &setall);
							setmax();
							break;
						}
					}
					else
					{
						int cid = cli_fd_id[i];
						char full[4096];
						bzero(&full, sizeof(full));
						if (read(i, full, 4095) <= 0)
						{
							bzero(&buf, sizeof(buf));
							sprintf(buf, "server: client %d just left\n", cid);
							writeToAll(i, buf);
							close(i);
							FD_CLR(i, &setall);
							free(cli_msg[cid]);
							cli_fd[cid] = -1;
						}
						else
						{
							char *msg = 0;
							cli_msg[cid] = str_join(cli_msg[cid], full);
							while (extract_message(&cli_msg[cid], &msg))
							{
								bzero(&buf, sizeof(buf));
								sprintf(buf, "client %d: ", cid);
								writeToAll(i, buf);
								writeToAll(i, msg);
								free(msg);
								msg = 0;
							}
						}
					}
				}
			}
		}
	}
	return (0);
}