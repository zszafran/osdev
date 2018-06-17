docker rm -f osdev

docker build -t osdev ./docker
docker run \
  -ti \
  --hostname="osdev" \
  --name=osdev \
  --volume="${PWD}:/usr/src/osdev" \
  --privileged \
  osdev