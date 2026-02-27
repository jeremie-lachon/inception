#!/bin/bash
set -e

#First run detection
if [ ! -d "/etc/nginx/ssl" ]; then

	echo "First run - creating ssl"

	mkdir -p /etc/nginx/ssl

	openssl req -x509 -newkey rsa:2048 -nodes -subj "/CN=${DOMAIN_NAME}" -keyout /etc/nginx/ssl/key.pem -out /etc/nginx/ssl/cert.pem -days 365 


fi

envsubst '${DOMAIN_NAME}' < /etc/nginx/conf.d/wordpress.conf > /tmp/wp.conf && mv /tmp/wp.conf /etc/nginx/conf.d/wordpress.conf

exec nginx -g 'daemon off;'
