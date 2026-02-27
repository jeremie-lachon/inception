#!/bin/bash
set -e

WP_PATH="/var/www/html/wordpress"

MYSQL_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(sed -n '1p' /run/secrets/credentials)
WP_USER_PASSWORD=$(sed -n '2p' /run/secrets/credentials)

# First run detection
if [ ! -f "$WP_PATH/wp-config.php" ]; then

	echo "First run — initializing database..."

	mkdir -p "$WP_PATH"

	wp core download --path="$WP_PATH" --allow-root

	wp config create \
		--path="$WP_PATH" \
		--dbname="${MYSQL_DATABASE}" \
		--dbuser="${MYSQL_USER}" \
		--dbpass="${MYSQL_PASSWORD}" \
		--dbhost="mariadb:3306" \
		--allow-root

	echo "Waiting for mariadb"
	until wp db check --path="$WP_PATH" --allow-root 2>/dev/null; do
		sleep 2
	done

	wp core install \
		--path="$WP_PATH" \
		--url="${DOMAIN_NAME}" \
		--title="${WP_TITLE}" \
		--admin_user="${WP_ADMIN_USER}" \
		--admin_password="${WP_ADMIN_PASSWORD}" \
		--admin_email="${WP_ADMIN_EMAIL}" \
		--skip-email \
		--allow-root

	wp user create \
		"${WP_USER}" "${WP_USER_EMAIL}" \
		--role=author \
		--user_pass="${WP_USER_PASSWORD}" \
		--path="$WP_PATH" \
		--allow-root


fi

exec /usr/sbin/php-fpm8.2 --nodaemonize
