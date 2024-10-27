#!/bin/bash
docker build -t mynginx .
docker run -d -p 80:81 --name test mynginx
open http://localhost:80/

read symbol
bash ./stop.sh