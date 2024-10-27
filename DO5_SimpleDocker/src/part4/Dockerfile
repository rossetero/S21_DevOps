FROM nginx:latest
WORKDIR /home/
COPY nginx.conf /etc/nginx/nginx.conf
COPY ./server.c /home/server.c
COPY ./run.sh /home/run.sh

RUN apt-get update &&  \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \ 
    chmod +x /home/run.sh

ENTRYPOINT ["./run.sh"]