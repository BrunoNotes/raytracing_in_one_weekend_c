config ?= debug
# config ?= release
CC := clang

main: build run

run:
	@./bin/main

build:
	@$(CC) -o nob nob.c
ifeq ($(config), debug)
	@./nob debug
else
	@./nob
endif

