FROM ubuntu:16.04

MAINTAINER chris.seaton@oracle.com

RUN apt-get update
RUN apt-get install -y gcc clang llvm time zlib1g-dev

WORKDIR /test
RUN useradd -ms /bin/bash test
RUN chown test /test
USER test

COPY graalvm-ee-1.0.0-rc1-linux-amd64.tar.gz TopTen.java large.txt small.txt \
  color.js color-server.js polyglot.js fizzbuzz.js fizzbuzz.py fizzbuzz.rb \
  fizzbuzz.r render.rb gzip.c Distance.java sis.jar distance.c \
  extendc.c /test/
