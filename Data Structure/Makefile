# Test all

all: TestTree TestTable TestList TestHeap TestQueue TestStack TestGraph

# Tree

TestTree: Tree/BinarySearchTree.exe
	./Tree/BinarySearchTree.exe

Tree/BinarySearchTree.exe: Tree/main.c Tree/BinarySearchTree.o Tree/QueueForBST.o # need QueueForBST
	gcc -Wall Tree/main.c Tree/BinarySearchTree.o Tree/QueueForBST.o -o Tree/BinarySearchTree.exe

Tree/BinarySearchTree.o: Tree/BinarySearchTree.c Tree/BinarySearchTree.h
	gcc -Wall -c Tree/BinarySearchTree.c -o Tree/BinarySearchTree.o

Tree/QueueForBST.o: Tree/QueueForBST.h Tree/QueueForBST.c
	gcc -Wall -c Tree/QueueForBST.c -o Tree/QueueForBST.o

# Table

TestTable: Table/HashTable.exe
	./Table/HashTable.exe

Table/HashTable.exe: Table/main.c Table/HashTable.o
	gcc -Wall Table/main.c Table/HashTable.o -o Table/HashTable.exe

Table/HashTable.o: Table/HashTable.c Table/HashTable.h
	gcc -Wall -c Table/HashTable.c -o Table/HashTable.o

# List

TestList: List/ArrayList.exe List/LinkedList.exe
	./List/ArrayList.exe
	./List/LinkedList.exe

List/ArrayList.exe: List/main.c List/ArrayList.o
	gcc -Wall List/main.c List/ArrayList.o -o List/ArrayList.exe

List/LinkedList.exe: List/main.c List/LinkedList.o
	gcc -Wall List/main.c List/LinkedList.o -o List/LinkedList.exe

List/ArrayList.o: List/ArrayList.c List/List.h
	gcc -Wall -c List/ArrayList.c -o List/ArrayList.o

List/LinkedList.o: List/LinkedList.c List/List.h
	gcc -Wall -c List/LinkedList.c -o List/LinkedList.o

# Heap

TestHeap: Heap/MaxHeap.exe
	./Heap/MaxHeap.exe

Heap/MaxHeap.exe: Heap/main.c Heap/MaxHeap.o
	gcc -Wall Heap/main.c Heap/MaxHeap.o -o Heap/MaxHeap.exe

Heap/MaxHeap.o: Heap/MaxHeap.c Heap/MaxHeap.h
	gcc -Wall -c Heap/MaxHeap.c -o Heap/MaxHeap.o

# Queue

TestQueue: Queue/ArrayQueue.exe Queue/LinkedQueue.exe
	./Queue/ArrayQueue.exe
	./Queue/LinkedQueue.exe

Queue/ArrayQueue.exe: Queue/main.c Queue/ArrayQueue.o
	gcc -Wall Queue/main.c Queue/ArrayQueue.o -o Queue/ArrayQueue.exe

Queue/LinkedQueue.exe: Queue/main.c Queue/LinkedQueue.o
	gcc -Wall Queue/main.c Queue/LinkedQueue.o -o Queue/LinkedQueue.exe

Queue/ArrayQueue.o: Queue/ArrayQueue.c Queue/Queue.h
	gcc -Wall -c Queue/ArrayQueue.c -o Queue/ArrayQueue.o

Queue/LinkedQueue.o: Queue/LinkedQueue.c Queue/Queue.h
	gcc -Wall -c Queue/LinkedQueue.c -o Queue/LinkedQueue.o

# Stack

TestStack: Stack/ArrayStack.exe Stack/LinkedStack.exe
	./Stack/ArrayStack.exe
	./Stack/LinkedStack.exe

Stack/ArrayStack.exe: Stack/main.c Stack/ArrayStack.o
	gcc -Wall Stack/main.c Stack/ArrayStack.o -o Stack/ArrayStack.exe

Stack/LinkedStack.exe: Stack/main.c Stack/LinkedStack.o
	gcc -Wall Stack/main.c Stack/LinkedStack.o -o Stack/LinkedStack.exe

Stack/ArrayStack.o: Stack/ArrayStack.c Stack/Stack.h
	gcc -Wall -c Stack/ArrayStack.c -o Stack/ArrayStack.o

Stack/LinkedStack.o: Stack/LinkedStack.c Stack/Stack.h
	gcc -Wall -c Stack/LinkedStack.c -o Stack/LinkedStack.o

# Graph

TestGraph: Graph/WeightedGraph.exe
	./Graph/WeightedGraph.exe

Graph/WeightedGraph.exe: Graph/main.c Graph/WeightedGraph.o Queue/ArrayQueue.o # need Queue
	gcc -Wall Graph/main.c Graph/WeightedGraph.o Queue/ArrayQueue.o -o Graph/WeightedGraph.exe

Graph/WeightedGraph.o: Graph/WeightedGraph.c Graph/WeightedGraph.h Queue/Queue.h
	gcc -Wall -c Graph/WeightedGraph.c -o Graph/WeightedGraph.o

# Clean files

clean:
	rm -f */*.o */*.exe
