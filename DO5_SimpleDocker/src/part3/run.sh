#!/bin/bash
docker pull nginx
docker run -d -p 81:81 --name test nginx
docker cp ./server.c /home/
docker cp ./nginx.conf test:/etc/nginx/
docker exec test apt-get update 
docker exec test apt-get install -y gcc spawn-fcgi libfcgi-dev
docker exec test gcc /etc/nginx/server.c -o /etc/nginx/webserver -l fcgi
echo "complied"
docker exec test spawn-fcgi -p 8080 /etc/nginx/webserver
docker exec test nginx -s reload
curl http://localhost:81/
read symbol

bash ./stop.sh