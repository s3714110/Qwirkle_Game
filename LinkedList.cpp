#include "LinkedList.h"


// Linked List Functions
LinkedList::LinkedList() {
	head = nullptr;
	count = 0;
}
LinkedList::~LinkedList() {
	Node* delNode = nullptr;
	Node* node = head;

	while (node != nullptr) {
		delNode = node;
		node = node->nextNode();
		delete delNode;
	}
}

void LinkedList::add(Tile* tile) {

	if (tile == nullptr) {
		return;
	}


	Node* newNode = new Node(tile);

	if (count == 0) {
		addHeadNode(newNode);
	}
	else {
		addTailNode(newNode);
	}
}
void LinkedList::add(Tile* tile, int index) {

	if (index > count || index < 0) {
		return;
	}
	if (tile == nullptr) {
		return;
	}


	Node* newNode = new Node(tile);

	if (index == 0) {
		addHeadNode(newNode);
	}
	else {
		Node* prev = getNode(index - 1);
		addNode(prev, newNode);
	}
}
void LinkedList::addHead(Tile* tile) {

	if (tile == nullptr) {
		return;
	}


	Node* newNode = new Node(tile);
	addHeadNode(newNode);
}
void LinkedList::addTail(Tile* tile) {

	if (tile == nullptr) {
		return;
	}

	Node* newNode = new Node(tile);

	if (count == 0) {
		addHeadNode(newNode);
	}
	else {
		addTailNode(newNode);
	}
}

void LinkedList::remove(Tile* tile) {
	
	Node* delNode = head;
	Node* prev = nullptr;

	if (delNode != nullptr && tile != nullptr) {

		bool found = false;
		int counter = 0;

		while (counter < count && !found) {
			if (tile->equal(delNode->getTile())) {
				found = true;
				if (counter == 0) {
					removeHead();
				}
				else {
					removeNode(prev, delNode);
				}
			}
			prev = delNode;
			delNode = delNode->nextNode();
			counter++;
		}
	}
}
void LinkedList::remove(int index) {

	if (index == 0) {
		removeHead();
	}
	else if (index > 0 && index < count) {
		Node* delNode = getNode(index);
		Node* prev = getNode(index - 1);

		removeNode(prev, delNode);
	}
}
void LinkedList::removeHead() {
	removeHeadNode();
}
void LinkedList::removeTail() {
	removeTailNode();
}

Tile* LinkedList::get(int index) {
	Tile* tile = nullptr;
	Node* node = getNode(index);

	if (node != nullptr) {
		tile = node->getTile();
	}

	return tile;
}
Tile* LinkedList::getHead() {
	Tile* tile = nullptr;
	Node* node = getHeadNode();

	if (node != nullptr) {
		tile = node->getTile();
	}

	return tile;
}
Tile* LinkedList::getTail() {
	Tile* tile = nullptr;
	Node* node = getTailNode();

	if (node != nullptr) {
		tile = node->getTile();
	}

	return tile;
}

bool LinkedList::contains(Tile* tile) {
	bool found = false;

	Node* node = head;
	Tile* checkTile = nullptr;
	while (node != nullptr && !found) {
		checkTile = node->getTile();

		if (tile->equal(checkTile)) {
			found = true;
		}

		node = node->nextNode();
	}

	return found;
}

int LinkedList::size() {
	return count;
}

// private functions
void LinkedList::addNode(Node* prev, Node* newNode) {
	newNode->setNext(prev->nextNode());
	prev->setNext(newNode);
	count++;
}
void LinkedList::addHeadNode(Node* newNode) {
	newNode->setNext(head);
	head = newNode;
	count++;
}
void LinkedList::addTailNode(Node* newNode) {
	Node* tail = getTailNode();
	tail->setNext(newNode);
	count++;
}

void LinkedList::removeNode(Node* prev, Node* delNode) {

	prev->setNext(delNode->nextNode());
	delete delNode;
	count--;
}
void LinkedList::removeHeadNode() {
	Node* delNode = head;

	head = delNode->nextNode();
	delete delNode;
	count--;
}
void LinkedList::removeTailNode() {
	Node* delNode = head;
	Node* prev = nullptr;

	while (delNode->nextNode() != nullptr) {
		prev = delNode;
		delNode = delNode->nextNode();
	}

	removeNode(prev, delNode);

}

Node* LinkedList::getNode(int index) {

	Node* node = head;

	for (int i = 0; i < index; i++) {
		node = node->nextNode();
	}

	return node;
}
Node* LinkedList::getHeadNode() {
	return head;
}
Node* LinkedList::getTailNode() {
	Node* node = head;

	if (node != nullptr) {
		while (node->nextNode() != nullptr) {
			node = node->nextNode();
		}
	}

	return node;
}


// Node Functions
Node::Node(Tile* tile) {
	Node::tile = tile;
	Node::next = nullptr;
}
Tile* Node::getTile() {
	return Node::tile;
}
Node* Node::setNext(Node* next) {
	return Node::next = next;
}
Node* Node::nextNode() {
	return Node::next;
}
