#include "Iterator.h"
using namespace std;

Iterator::Iterator(Node *currIn) {
    this->curr = currIn;
}

const std::string Iterator::operator*() const {
    return this->curr->getWord();
}

Iterator& Iterator::operator++() {
    this->curr = this->curr->getNext();
    return *this;
}

Iterator Iterator::operator++(int i) {
    Node* old_curr = this->curr;
    this->curr = this->curr->getNext();
    return old_curr;
}

Iterator Iterator::operator+(const int &i) {
    if (i == 0) return *this;
    return (++(*this)) + (i - 1);
}

Iterator Iterator::operator+=(const int &i) {
    for (int j = 0; j < i; ++j) {
        ++(*this);
    }
}

Iterator& Iterator::operator--() {
    this->curr = this->curr->getPrev();
    return *this;
}

Iterator Iterator::operator--(int i) {
    Node* old_curr = this->curr;
    this->curr = this->curr->getPrev();
    return old_curr;
}

Iterator Iterator::operator-(const int &i) {
    if (i == 0) return *this;
    return (--(*this)) + (i - 1);
}

Iterator Iterator::operator-=(const int &i) {
    for (int j = 0; j < i; ++j) {
        --(*this);
    }
}

bool Iterator::operator==(const Iterator &other) {
    if (this->curr == other.curr) return true;
    return false;
}

bool Iterator::operator!=(const Iterator &other) {
    if (this->curr != other.curr) return true;
    return false;
}

Node*& Iterator::getCurr() {
    return this->curr;
}
