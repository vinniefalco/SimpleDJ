# Build and run:
#   docker build -t clion/ubuntu/cpp-env:1.0 -f Dockerfile.cpp-env-ubuntu .

FROM ubuntu:20.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt-get update \
  && apt-get install -y build-essential \
      gcc \
      g++ \
      gdb \
      git \
      clang \
      make \
      ninja-build \
      cmake \
      autoconf \
      automake \
      libtool \
      valgrind \
      tar \
  && apt-get clean
