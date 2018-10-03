#include "Node.h"
using namespace std;

Node::Node() {
    this->word = "";
    this->next = NULL;
    this->prev = NULL;
}

Node::Node(std::string word) {
    this->word = word;
    this->next = this;
    this->prev = this;
}

Node::Node(std::string word, Node *prev) {
    this->word = word;
    this->prev = prev;
    this->next = NULL;
    if (prev->next != NULL) {
        this->next = prev->next;
        this->next->setPrev(this);
        this->prev->setNext(this);
    }
}

std::string& Node::getWord() {
    return this->word;
}

Node* Node::getNext() const {
    return this->next;
}

Node* Node::getPrev() const {
    return this->prev;
}

void Node::setWord(std::string new_word) {
    this->word = new_word;
}

void Node::setNext(Node *new_next) {
    this->next = new_next;
}

void Node::setPrev(Node *new_prev) {
    this->prev = new_prev;
}
