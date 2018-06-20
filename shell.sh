docker rm -f osdev

docker build -t osdev ./docker
docker run \
  -ti \
  --hostname="osdev" \
  --name=osdev \
  --volume="${PWD}:/usr/src/osdev" \
  --publish="1234:1234" \
  --privileged \
  osdev