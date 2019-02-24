main.o: main.cpp
	g++ -c main.cpp
IOUtils.o: IOUtils.cpp
	g++ -c IOUtils.cpp
all: main.o IOUtils.o
	g++ -o bitcoin main.o IOUtils.o
clean:
	rm -f *.o bitcoin
