FROM gcc:latest

RUN apt update && apt install -yy lua5.4 liblua5.4-dev

COPY . /app
WORKDIR /app

##### Criar e Rodar o container
### docker build -t lua_c .
# Mac e Linux
### docker run --rm -it -v $PWD:/app lua_c bash
# Windows
### docker run --rm -it -v ${PWD}:/app lua_c bash

## compilar dentro do container
### gcc -I/usr/include/lua5.4 -o main variaveis.c -llua5.4

##rodar o .exe
### ./main