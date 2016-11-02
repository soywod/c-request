CC=gcc
CFLAGS=-W -Wall
SOURCES=$(wildcard *.c)

all:
	$(CC) $(CFLAGS) $(SOURCES) node_modules/c-map/map.c
