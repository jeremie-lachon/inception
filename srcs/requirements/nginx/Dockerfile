FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y && apt-get install nginx -y && apt-get install openssl -y && apt-get install gettext-base -y && \
	rm -rf /var/lib/apt/lists/*

COPY conf/nginx.conf /etc/nginx/conf.d/wordpress.conf

COPY tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 443

ENTRYPOINT ["/entrypoint.sh"]
