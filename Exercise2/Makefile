OBJS = racecar.o car.o exercises2.o
CC = g++
CFLAGS = -c 
LFLAGS = 

# linken
main: $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o main

# ojbect files
exercises2.o: exercises2.cpp car.h racecar.h
	$(CC) $(CFLAGS) exercises2.cpp

car.o: car.cpp car.h
	$(CC) $(CFLAGS) car.cpp

racecar.o: racecar.cpp racecar.h car.h
	$(CC) $(CFLAGS) racecar.cpp

# clean up
clean:
	rm -rf *.o main

