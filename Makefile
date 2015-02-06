VPATH = src:include

LIB_DIR = lib

INCLUDE_DIR = include

LIB = $(LIB_DIR)/libxgl.a

objects = except.o assert.o memchk.o fb_env.o

all: $(objects)
	ar crs $(LIB) $(objects)


except.o: except.c except.h assert.h
	gcc -pg -g -c $< -I$(INCLUDE_DIR)

assert.o: assert.c assert.h except.h
	gcc -pg -g -c $< -I$(INCLUDE_DIR)

memchk.o: memchk.c mem.h assert.h except.h
	gcc -pg -g -c $< -I$(INCLUDE_DIR)

fb_env.o: fb_env.c fb_env.h
	gcc -pg -g -c $< -I$(INCLUDE_DIR)

clean:
	rm *.o
	rm $(LIB)
