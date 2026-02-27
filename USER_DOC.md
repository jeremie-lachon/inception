# User Documentation

## Services
- This project builds and serves a WordPress website backed by a MariaDB database and served through NGINX over HTTPS.
- WordPress handles the website content, MariaDB stores it, and NGINX is the only public-facing entry point.

## Start and Stop
- Start the project with `make` or `make all`
- Stop the stack with `make stop` — data is preserved
- Resume with `make start`
- `make re` rebuilds the project from a clean state, volumes are cleared
- `make fclean` removes containers, images, and data
- `make fullclean` does everything `fclean` does and also clears the Docker build cache

## Accessing the Website
- Navigate to [jla-chon.42.fr](https://jla-chon.42.fr)
- The site uses a self-signed certificate — accept the browser security warning to proceed

## Accessing the Administration Panel
- Navigate to [jla-chon.42.fr/wp-admin](https://jla-chon.42.fr/wp-admin)
- Log in with the admin credentials from `secrets/credentials.txt`

## Credentials
- All credentials are stored in `./secrets/`
- Each file is named after the service or role it corresponds to
- These files are gitignored and must never be committed to the repository

## Checking Services
- **NGINX**: if the website loads over HTTPS, NGINX and PHP-FPM are working
- **MariaDB**: add a comment on the site, run `make stop` then `make start` — if the comment is still there, the database is persisting correctly
- **WordPress**: if the site displays a WordPress page rather than a default NGINX page, WordPress is running correctly
