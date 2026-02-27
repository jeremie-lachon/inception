#!/bin/bash
set -e

MYSQL_PASSWORD=$(cat /run/secrets/db_password)
MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

# First run detection
if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then

	echo "First run — initializing database..."


	# Run initialization SQL via bootstrap mode
	mysqld --user=mysql --bootstrap --skip-networking <<HERE
FLUSH PRIVILEGES;
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
HERE

	echo "Database initialized successfully."

else
	echo "Data directory exists — skipping initialization."
fi

# Start MariaDB as PID 1
exec mysqld --user=mysql
