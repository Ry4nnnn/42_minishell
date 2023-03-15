FROM ubuntu:20.04

WORKDIR /minishell

RUN apt-get update && apt-get install -y \
	git \
	gcc \
	libreadline-dev \
	make \
	bash

RUN useradd -ms /bin/bash newuser
USER newuser
ENV USER=newuser
ENV HOME=/home


#CMD ["make", "DB=1"]

