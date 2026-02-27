DOCKER = docker compose -f srcs/docker-compose.yml
DIR = ./data

all:
	mkdir -p $(DIR)/mariadb $(DIR)/wordpress
	$(DOCKER) up --build -d

clean:
	$(DOCKER) down

fclean:
	$(DOCKER) down --rmi all --volumes
	docker container prune -f
	docker image prune -af
	rm -rf $(DIR)

re: fclean all

check:
	docker compose -f srcs/docker-compose.yml ps
	docker compose -f srcs/docker-compose.yml logs -f

.PHONY: all clean fclean re check
