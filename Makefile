main.o: main.cpp
	g++ -c main.cpp
IOUtils.o: IOUtils.cpp
	g++ -c IOUtils.cpp
ListNode.o: ListNode.cpp
	g++ -c ListNode.cpp
Wallet.o: Wallet.cpp
	g++ -c Wallet.cpp
HashTable.o: HashTable.cpp
	g++ -c HashTable.cpp
Bucket.o: Bucket.cpp
	g++ -c Bucket.cpp
DataBucket.o: DataBucket.cpp
	g++ -c DataBucket.cpp
all: main.o IOUtils.o ListNode.o Wallet.o HashTable.o Bucket.o DataBucket.o
	g++ -o bitcoin main.o IOUtils.o ListNode.o Wallet.o HashTable.o Bucket.o DataBucket.o
clean:
	rm -f *.o bitcoin
