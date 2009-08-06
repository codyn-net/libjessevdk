INCLUDES=-I/usr/include/python2.6 `pkg-config --cflags libjessevdk-base-0.1`
CFLAGS=-g -fPIC
LIBS=-lpython2.6 `pkg-config --libs libjessevdk-base-0.1`
NAME=base

all:
	swig -c++ -python $(INCLUDES) $(NAME).i
	g++ $(CFLAGS) $(INCLUDES) -c -o _$(NAME).o $(NAME)_wrap.cxx
	g++ -shared $(LIBS) -o _$(NAME).so _$(NAME).o
