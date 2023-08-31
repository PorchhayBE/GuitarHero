CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++17
LIBS = -lsfml-graphics	-lsfml-window -lsfml-system -lsfml-audio
TestLibs = -lboost_unit_test_framework
DEPS = CircularBuffer.h StringSound.h

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

all: GuitarHero

GuitarHero: CircularBuffer.o StringSound.o KSGuitarSim.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm *.o GuitarHero