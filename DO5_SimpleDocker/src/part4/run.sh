#!/bin/bash
gcc ./server.c -l fcgi -o ./webserver
spawn-fcgi -p 8080 ./webserver
nginx -g 'daemon off;'
nginx -s reload