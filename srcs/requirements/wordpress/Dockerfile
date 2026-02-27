FROM debian:bookworm
# fPacketManager gd:resizeImages mbString:non-ASCII xml:internal zip:plugins
RUN apt-get update && apt-get upgrade -y && \
	apt-get install wget -y && \
	apt-get install php-fpm -y && \
	apt-get install php-mysql -y && \
	apt-get install php-curl -y && \
	apt-get install php-gd -y && \
	apt-get install php-mbstring -y && \
	apt-get install php-xml -y && \
	apt-get install php-zip -y && \
	apt-get install default-mysql-client -y && \
	rm -rf /var/lib/apt/lists/*

RUN wget -q https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -O /usr/local/bin/wp && chmod +x /usr/local/bin/wp

COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

COPY tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/entrypoint.sh"]
