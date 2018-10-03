#ifndef __GENERICSET_H__
#define __GENERICSET_H__

#define MAX_ITEMS 30

#include <iostream>
using namespace std;
typedef int ItemType;
template <class ItemType>

class GenericSet
{
        protected: // changed: private->protected (to access the variables from template classes)
                int size;
                ItemType values[MAX_ITEMS];

        public:
                // Default Constructor
                // Post condition: an Empty generic set is created
                GenericSet();

                // Insert function
                virtual void Insert(ItemType item)=0;

                // Delete function
                virtual void Delete(ItemType item)=0;

                // Clear function
                // Post condition: all items are removed from the generic set, and the
                //                 size of the generic set becomes 0.
                void Clear();

                // GetSize function
                // Return value is the number of items in the generic set
                int GetSize();

                // IsFull function
                // Return true if there is no more space in the generic set,
                //        false otherwise.
                bool IsFull();

                // IsEmpty function
                // Return true if the generic set is empty,
                //        false otherwise.
                bool IsEmpty();

                friend std::ostream& operator<<(std::ostream& out, const GenericSet& s){
                        out << "{";
                        for(int i=0;i<s.size;i++){
                                out << s.values[i] ;
                                if(i < s.size-1) out << ", ";
                        }
                        out << "}";
                        return out;
                }
};

template <class ItemType> class Set: public GenericSet<ItemType>
{
private:
public:
    Set() { // default constructor for Set template class
        this->size = 0;
    };
    virtual void Insert(ItemType item); // prototype of Insert method
    virtual void Delete(ItemType item); // prototype of Delete method
};

template <class ItemType> class Bag: public GenericSet<ItemType>
{
private:
public:
    Bag() { // default constructor of Bag template class
        this->size = 0;
    };
    virtual void Insert(ItemType item); // prototype of Insert method
    virtual void Delete(ItemType item); // prototype of Delete method
};

template <class ItemType> GenericSet<ItemType>::GenericSet() {
    this->size = 0; // constructor of GenericSet class
}

template <class ItemType> int GenericSet<ItemType>::GetSize() {
    return this->size; // return the size of array
}

template <class ItemType> void GenericSet<ItemType>::Clear() {
    this->size = 0; // set size of array to 0
}

template <class ItemType> bool GenericSet<ItemType>::IsFull() {
    if (this->GetSize() >= MAX_ITEMS) return true; // return true if array is full
    return false; // otherwise return false
}
template <class ItemType> bool GenericSet<ItemType>::IsEmpty() {
    if (this->GetSize() = 0) return true; // if size equals to 0, return true
    return false; // otherwise return false
}

template <class ItemType> void Set<ItemType>::Insert(ItemType item) {
    for (int i = 0; i < this->GetSize(); ++i) { // check if the element already
        if (this->values[i] == item) return; // in the array, if yes, return back
    }
    if (this->IsFull()) { // if array is full, throw exception
        throw "Set Exception: No more space";
    }
    this->size += 1; // if everything okay, increase size by one
    this->values[this->size - 1] = item; // and add element to the end
}

template <class ItemType> void Set<ItemType>::Delete(ItemType item) {
    for (int i = 0; i < this->GetSize(); ++i) { // search for element
        if (this->values[i] == item) { // if found
            for (int j = i; j < this->GetSize() - 1; ++j) {
                this->values[j] = this->values[j + 1]; // overwrite this and next elements
            }
            this->size -= 1; // decrease the size by one
            return;
        }
    }
    throw "Set Exception: Not found"; // otherwise throw exception
}

template <class ItemType> void Bag<ItemType>::Insert(ItemType item) {
    if (this->IsFull()) { // if array is full, throw exception
        throw "Set Exception: No more space";
    }
    this->size += 1; // if everything okay, increase size by one
    this->values[this->size - 1] = item; // and add element to the end
}

template <class ItemType> void Bag<ItemType>::Delete(ItemType item) {
    for (int i = this->GetSize(); i >= 0; --i) { // search for element from the end
        if (this->values[i] == item) { // if found
            for (int j = i; j < this->GetSize() - 1; ++j) {
                this->values[j] = this->values[j + 1]; // overwrite this and next elements
            }
            this->size -= 1; // decrease size by one
            return;
        }
    }
    throw "Set Exception: Not found"; // otherwise throw exception
}
#endif
