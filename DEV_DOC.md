# Developer Documentation

## Prerequisites
- Docker and Docker Compose v2 must be installed
- `make` must be available
- Add `jla-chon.local` to `/etc/hosts` pointing to the host machine's IP

## Setup from Scratch

### 1. Clone the repository
- Clone the repo and navigate into it

### 2. Create the secrets
- `secrets/` is gitignored and must be created manually at the root of the repo
- `secrets/db_password.txt` — password for the MariaDB WordPress user
- `secrets/db_root_password.txt` — MariaDB root password
- `secrets/credentials.txt` — line 1: WordPress admin password, line 2: WordPress user password

### 3. Create the environment file
- `srcs/.env` is gitignored and must be created manually inside `srcs/`
- It must define: `DOMAIN_NAME`, `MYSQL_DATABASE`, `MYSQL_USER`, `WP_TITLE`, `WP_ADMIN_USER`, `WP_ADMIN_EMAIL`, `WP_USER`, `WP_USER_EMAIL`, and `DATA_DIR`
- `DATA_DIR` must be an absolute path on the host where volume data will be stored, e.g. `/home/jla-chon/data`

## Build and Launch
- Run `make` or `make all` to build images and start the stack
- The Makefile reads `DATA_DIR` from `srcs/.env` and creates the host directories before starting
- Run `make re` for a quick clean and rebuild
- Run `make fullclean` then `make` to guarantee a fully fresh build with no cached layers

## Managing Containers and Volumes
- `make logs` follows live logs for all containers
- `docker logs -f <container>` for individual container logs
- `docker exec -it <container> bash` to open a shell inside a running container
- `make stop` and `make start` to pause and resume without losing data
- `make clean` stops and removes containers but keeps images and data
- `make fclean` removes containers, images, volumes, and deletes host data
- `make fullclean` does everything `fclean` does plus clears the Docker build cache

## Data Storage and Persistence
- Volume data is stored on the host at the path defined by `DATA_DIR` in `srcs/.env`
- `$DATA_DIR/mariadb` contains the MariaDB database files
- `$DATA_DIR/wordpress` contains the WordPress core files and uploads
- Data survives `make stop`/`make start` and `make clean`, and is only deleted by `make fclean` or `make fullclean`
- Docker secrets are mounted read-only inside containers at `/run/secrets/` and are never baked into any image
