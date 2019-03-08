main.o: main.cpp
	g++ -c main.cpp
IOUtils.o: IOUtils.cpp
	g++ -c IOUtils.cpp
ListNode.o: ListNode.cpp
	g++ -c ListNode.cpp
Wallet.o: Wallet.cpp
	g++ -c Wallet.cpp
Bucket.o: Bucket.cpp
	g++ -c Bucket.cpp
DataBucket.o: DataBucket.cpp
	g++ -c DataBucket.cpp
UsersHashTable.o: UsersHashTable.cpp
	g++ -c UsersHashTable.cpp
Transaction.o: Transaction.cpp
	g++ -c Transaction.cpp
CoinTree.o: CoinTree.cpp
	g++ -c CoinTree.cpp
TreeHashTable.o: TreeHashTable.cpp
	g++ -c TreeHashTable.cpp
CoinNode.o: CoinNode.cpp
	g++ -c CoinNode.cpp
Timestamp.o: Timestamp.cpp
	g++ -c Timestamp.cpp
WalletHashTable.o: WalletHashTable.cpp
	g++ -c WalletHashTable.cpp
all: main.o IOUtils.o ListNode.o Timestamp.o Wallet.o Bucket.o DataBucket.o UsersHashTable.o Transaction.o CoinTree.o TreeHashTable.o CoinNode.o WalletHashTable.o
	g++ -o bitcoin main.o IOUtils.o Timestamp.o ListNode.o Wallet.o Bucket.o DataBucket.o UsersHashTable.o Transaction.o CoinTree.o TreeHashTable.o CoinNode.o WalletHashTable.o
clean:
	rm -f *.o bitcoin
