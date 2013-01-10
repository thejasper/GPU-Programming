OBJS = testSet.o
CC = g++ -w

main: $(OBJS) 
	$(CC) $(OBJS) -o main

testSet.o: testSet.cpp Set.h
	$(CC) -c testSet.cpp

clean:
	rm -rf *.o main
