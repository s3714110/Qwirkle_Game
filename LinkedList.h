//#pragma once
#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include "Tile.h"

// Used to wrap tiles in the linked list
class Node {
private:
	Tile* tile;
	Node* next;

public:
	Node(Tile* tile);
	Tile* getTile();
	Node* setNext(Node* next);
	Node* nextNode();
};

class LinkedList {
private:
	Node* head;
	int count;

	// Node wrapper functions
	void addNode(Node* delNode, Node* prev);
	void addHeadNode(Node* node);
	void addTailNode(Node* node);	

	void removeNode(Node* delNode, Node* prev);
	void removeHeadNode();
	void removeTailNode();

	Node* getNode(int index);
	Node* getHeadNode();
	Node* getTailNode();

public:
	LinkedList();
	~LinkedList();

	void add(Tile* tile);
	void add(Tile* tile, int index);
	void addHead(Tile* tile);
	void addTail(Tile* tile);

	void remove(Tile* tile);
	void remove(int index);
	void removeHead();
	void removeTail();

	Tile* get(int index);
	Tile* getHead();
	Tile* getTail();

	bool contains(Tile* tile);

	int size();		
};
#endif