main.o: main.cpp
	g++ -c main.cpp
IOUtils.o: IOUtils.cpp
	g++ -c IOUtils.cpp
ListNode.o: ListNode.cpp
	g++ -c ListNode.cpp
all: main.o IOUtils.o ListNode.o
	g++ -o bitcoin main.o IOUtils.o ListNode.o
clean:
	rm -f *.o bitcoin
