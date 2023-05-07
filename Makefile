# Simple makefile 

NAME = game_2048

#Linker flags
LIBS  = -lm -lraylib -lopengl32 -lgdi32 -lwinmm

#Compiler flags
CFLAGS =  -O1 -Wall -std=c99 -Wno-missing-braces

#Includes 
INCLUDES_DIRS= -Iinclude/ -Isrc/

LIB_DIRS = lib/

SRC_DIR = src/
#Compiler
CC = gcc

SRC = $(SRC_DIR)main.c 

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS) $(INCLUDES_DIRS) -L$(LIB_DIRS)
