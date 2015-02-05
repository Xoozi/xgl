VPATH = src:include

LIB_DIR = lib

INCLUDE_DIR = include

LIB = $(LIB_DIR)/libxgl.a

objects = fb_env.o

all: $(objects)
	ar crs $(LIB) $(objects)

fb_env.o: fb_env.c fb_env.h
	gcc -pg -g -c $< -I$(INCLUDE_DIR)


clean:
	rm *.o
	rm $(LIB)
