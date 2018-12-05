CC=clang
CFLAGS=-g
CFLAGS+=-c -Wall -fpic -std=c++11 #-fpermissive
LIBS = my_lib.o

all: $(LIBS)

clean:
	@rm -f *.o *.so

%.o:%.cpp
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -shared -fpic -o libmy_lib.so $@
my_lib.o:my_lib.cpp
