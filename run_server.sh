#!/bin/bash

IMAGE_NAME="http-server"

echo "building docker image"
docker build -t ${IMAGE_NAME} .

if [$? -ne 0]; then
    echo "docker build failed"
    exit 1
fi

echo "Running the server on http://localhost:8080/"

docker run --rm -p 8080:8080 ${IMAGE_NAME}

