#include "Buffer.h"
#include <iostream>

Buffer::Buffer() {
    this->count = 0;
}

Buffer::Buffer(const Buffer &other) {
    this->count = 0;
    this->copy(other);
}

Buffer::~Buffer() {
    this->clear();
}

Buffer& Buffer::operator=(const Buffer &original) {
    clear();
    this->copy(original);
    return *this;
}

Node* Buffer::getHead() {
    return this->head;
}

Node* Buffer::getTail() {
    return this->head->getPrev();
}

std::string Buffer::getHeadElement() {
    if (this->isEmpty()) return "";
    return this->head->getWord();
}

std::string Buffer::getTailElement() {
    if (this->isEmpty()) return "";
    return this->getTail()->getWord();
}

void Buffer::produceAtHead(const std::string str) {
    if (count == 0) {
        head = new Node(str);
        ++count;
        return;
    }
    Node *p = new Node(str);
    p->setNext(head);
    p->setPrev(this->getTail());
    this->getTail()->setNext(p);
    head->setPrev(p);
    head = p;
    ++count;
}

void Buffer::produceAtTail(const std::string str) {
    Node *p = new Node(str);
    p->setNext(head);
    p->setPrev(this->getTail());
    this->getTail()->setNext(p);
    head->setPrev(p);
    ++count;
}

Iterator Buffer::produceAtMiddle(Iterator pos, const std::string str) {
    Node *new_node = new Node(str);
    Node *pos_node = pos.getCurr();
    Node *prev_node = pos_node->getPrev();
    prev_node->setNext(new_node);
    new_node->setNext(pos_node);
    new_node->setPrev(prev_node);
    pos_node->setPrev(new_node);
    Iterator it(new_node);
    ++count;
    return it;
}

void Buffer::consumeAtHead() {
    if (count == 0) return;
    if (count == 1) {
        this->clear();
        return;
    }
    Node *new_head = head->getNext();
    Node *next = head -> getNext ();
    Node *prev = head -> getPrev ();
    next->setPrev(prev);
    prev->setNext(next);
    delete head;
    head = new_head;
    --count;
}

void Buffer::consumeAtTail() {
    if (count == 0) return;
    if (count == 1) {
        this->clear();
        return;
    }
    Node *p = getTail();
    this->getTail()->getPrev()->setNext(head);
    head->setPrev(this->getTail()->getPrev());
    delete p;
    --count;
}

void Buffer::consume(Iterator it) {
    Node *temp = it.getCurr();
    if (temp == head) {
        consumeAtHead();
        return;
    }
    if (temp == this->getTail()) {
        consumeAtTail();
        return;
    }
    Node *prev_node = temp->getPrev();
    Node *next_node = temp->getNext();
    prev_node->setNext(next_node);
    next_node->setPrev(prev_node);
    delete temp;
    --count;
}

void Buffer::consume(Iterator s, Iterator t) {
    while (s != t) {
        consume(s);
        s += 1;
    }
}

unsigned Buffer::size() const {
    return count;
}

bool Buffer::isEmpty() {
    if (this->head == NULL || count == 0) return true;
    return false;
}

std::string& Buffer::operator[](int i) const {
    Iterator it = this->head;
    it += i;
    return (it.getCurr())->getWord();
}

Iterator Buffer::getHeadItr() {
    Iterator it(this->getHead());
    return it;
}

Iterator Buffer::getTailItr() {
    Iterator it(this->getTail());
    return it;
}

Iterator Buffer::getNextItr(Iterator it) {
    return it + 1;
}

Iterator Buffer::getPrevItr(Iterator it) {
    return it - 1;
}

void Buffer::print() {
    Node *p = head;
    for (unsigned i = 0; i < count; ++i) {
        std::cout << p->getWord();
        if (i == count - 1) break;
        std::cout << " -> ";
        p = p->getNext();
    }
    std::cout << '\n' << '\n';
}

void Buffer::copy(const Buffer &other) {
    if (other.size() == 0) return;
    Node *p = other.head;
    std::string str = p->getWord();
    head = new Node(str);
    ++count;
    for (unsigned i = 1; i < other.size(); ++i) {
        p = p->getNext();
        this->produceAtTail(p->getWord());
    }

}

void Buffer::clear() {
    deleteBuffer(head);
}

void Buffer::deleteBuffer(Node *p) {
    if (p == NULL || count == 0) return;
    if (count == 1) {
        delete p;
        --count;
        return;
    }
    Node *next_node = p->getNext();;
    delete p;
    --count;
    if (next_node != NULL) deleteBuffer(next_node);
}

bool findNode(Iterator first, Iterator last, std::string str) {
    Iterator it(first);
    while(1) {
        if (it.getCurr()->getWord() == str) {
            return true;
        }
        if (it == last) break;
        ++it;
    }
    return false;
}
