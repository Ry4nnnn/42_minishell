FROM ubuntu:20.04

WORKDIR /home/wxuerui/Desktop/minishell

RUN apt-get update && apt-get install -y \
	git \
	gcc \
	libreadline-dev \
	make \
	bash

RUN useradd -ms /bin/bash wxuerui
USER wxuerui
ENV USER=wxuerui
ENV PWD=/home/wxuerui/Desktop/minishell


