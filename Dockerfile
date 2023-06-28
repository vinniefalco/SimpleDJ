# Build and run:
#   docker build -t clion/ubuntu/cpp-env:1.0 -f Dockerfile .

# base image
FROM ubuntu:20.04

#TODO define target-specific env variables

#TODO bring back builder user and set as sudoer

# non interactive mode plays nice with CLion debug window
RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

# setup
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
      pkg-config \
      libfreetype6-dev \
      libasound2-dev \
      libwebkit2gtk-4.0-dev \
      libgtk-3-dev \
      libcurl4-openssl-dev \
      autoconf \
      automake \
      libtool \
      valgrind \
      locales-all \
      dos2unix \
      rsync \
      tar \
      python \
      python-dev \
  && apt-get clean