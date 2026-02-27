FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y && apt-get install mariadb-server -y && rm -rf /var/lib/apt/lists/*
# directory and for safe user run
RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

COPY conf/99-customwp.cnf /etc/mysql/mariadb.conf.d/99-customwp.cnf

COPY tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 3306

ENTRYPOINT ["/entrypoint.sh"]
