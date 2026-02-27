-include srcs/.env
export

DOCKER = docker compose -f srcs/docker-compose.yml

all:
	mkdir -p $(DATA_DIR)/mariadb $(DATA_DIR)/wordpress
	$(DOCKER) up --build -d

clean:
	$(DOCKER) down

fclean:
	$(DOCKER) down --rmi all --volumes
	docker volume prune -f
	docker container prune -f
	docker image prune -af
	sudo rm -rf $(DATA_DIR)
	sudo rm -rf ./srcs/$(DATA_DIR)

fullclean: fclean
	docker system prune -af --volumes
	docker builder prune -af

re: fclean all

start:
	$(DOCKER) start

stop:
	$(DOCKER) stop

logs:
	$(DOCKER) logs -f

.PHONY: all clean fclean re start stop logs fullclean
