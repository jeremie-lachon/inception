*This project has been created as part of the 42 curriculum by jla-chon.*

# Inception

## Description
- A DEVOPS introduction project — using Docker to build and coordinate multiple services.
- The end result is a self-hosted WordPress website, running across three containers: NGINX, WordPress/PHP-FPM, and MariaDB.

## Instructions
- Clone the repository and navigate into it
- Create `secrets/` at the root with `db_password.txt`, `db_root_password.txt`, and `credentials.txt`
- Create `srcs/.env` with the required environment variables (see DEV_DOC.md for the full list)
- Run `make` to build and start the stack
- Navigate to `https://jla-chon.42.fr` in your browser

## Project Description

### Virtual Machines vs Docker
A VM emulates an entire computer with its own OS and hardware drivers — heavy and slow to start. Docker shares the host kernel and only isolates the process and its dependencies, making containers much lighter and faster. Less isolated than a full VM, but the right tool for most deployment use cases due to its uniform nature.

### Secrets vs Environment Variables
Environment variables are fine for non-sensitive config (domain name, database name) but they show up in `docker inspect` and process listings. Docker secrets are mounted as read-only files at `/run/secrets/` inside the container and are never stored in the image. This project uses env vars for general config and secrets for all passwords.

### Docker Network vs Host Network
A Docker bridge network creates a private internal network — containers on the same network reach each other by container name. This project's three containers all communicate over the `inception` bridge network. Host network mode skips that isolation and shares the host's network stack directly, which is faster but removes all separation between the container and the host.

### Docker Volumes vs Bind Mounts
A bind mount maps a specific host path directly into a container — simple but tied to the host's directory layout. A named volume is managed by Docker and more portable. This project uses named volumes with a local bind driver, storing data at `/home/jla-chon/data` on the host while still being declared as named volumes in the compose file.

## Resources

**Docker**
- [Dockerfile reference](https://docs.docker.com/reference/dockerfile/)
- [Docker Compose file reference](https://docs.docker.com/reference/compose-file/)
- [Docker networking overview](https://docs.docker.com/engine/network/)
- [Docker volumes](https://docs.docker.com/engine/storage/volumes/)
- [Docker secrets](https://docs.docker.com/engine/swarm/secrets/)

**Services**
- [NGINX documentation](https://nginx.org/en/docs/)
- [PHP-FPM configuration](https://www.php.net/manual/en/install.fpm.configuration.php)
- [MariaDB documentation](https://mariadb.com/kb/en/documentation/)
- [WordPress CLI documentation](https://developer.wordpress.org/cli/commands/)

**AI**
- Claude was used throughout this project to review code, explain concepts, and help write the documentation.
