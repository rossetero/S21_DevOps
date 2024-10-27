#!/bin/bash

docker stop test
docker rm test
docker rmi -f nginx