FROM fedora:36 AS builder

WORKDIR /app
COPY . /app

RUN /app/docker/build.sh

COPY docker/entrypoint.sh /

ENTRYPOINT ["/entrypoint.sh"]
