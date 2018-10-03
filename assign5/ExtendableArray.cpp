#include <iostream>
#include "ExtendableArray.h"
using namespace std;

ElementRef::ElementRef(ExtendableArray &theArray, int i) {  // constructor for 1 element
    intArrayRef = &theArray; // pointer to the Extendable Array
    index = i; // index of the element
}

ElementRef::ElementRef(const ElementRef &other) { // copy constructor
    intArrayRef = other.intArrayRef; // copy the pointer to the Extendable Array
    index = other.index; // copy the index
}

ElementRef::~ElementRef() {} // destructor

ElementRef& ElementRef::operator=(const ElementRef &rhs) {//assigning operator in case of another Element Ref
    int size = intArrayRef->size; // the size of the array
    if (index < size) { // if index is in the existing array,
        intArrayRef->arrayPointer[index] = rhs.intArrayRef->arrayPointer[rhs.index];//then assign it to new value
    } else if (index >= size) { // if index is out of range
        int *a = new int [index + 1]; // create new array
        for (int i = 0; i < size; ++i) // copy the old array to new array
            a[i] = intArrayRef->arrayPointer[i];
        for (int i = size; i < index; ++i) // fill the empty elements with zeros
            a[i] = 0; //
        a[index] = rhs.intArrayRef->arrayPointer[rhs.index]; // assign needed element to new value
        delete [] intArrayRef->arrayPointer; // delete old array
        intArrayRef->arrayPointer = a; // assign this array to new array
        intArrayRef->size = index + 1; // change the size to index+1
    }
    return *this; // return
}

ElementRef& ElementRef::operator=(int val) { // assigning operator in case of integer value
    int size = intArrayRef->size; // the size of the array
    if (index < size) { // if index is in the existing array,
        intArrayRef->arrayPointer[index] = val; // then assign it to new value
    } else if (index >= size) { // if index is out of range
        int *a = new int [index + 1]; // create new array
        for (int i = 0; i < size; ++i) // copy the old array to new array
            a[i] = (intArrayRef->arrayPointer)[i];
        for (int i = size; i < index; ++i) // fill the empty elements with zeros
            a[i] = 0;
        a[index] = val; // assign needed element to new value
        delete [] intArrayRef->arrayPointer; // delete old array
        intArrayRef->arrayPointer = a; // assign this array to new array
        intArrayRef->size = index + 1; // change the size to index+1
    }
    return *this; // return
}

ElementRef::operator int() const {
    int size = intArrayRef->size; // the size of the array
    if (index >= 0 && index < size) // if the index is in the range
        return intArrayRef->arrayPointer[index]; // return the integer value
    return 0; // otherwise return integer 0;
}

ExtendableArray::ExtendableArray() { // constructor for extendable array
    size = 2; // default size 2
    arrayPointer = new int[size]; // creating an array with 2 element
    for (int i = 0; i < size; ++i) // initializing them with 0
        arrayPointer[i] = 0;
}

ExtendableArray::ExtendableArray(const ExtendableArray &other) {//copy constructor
    size = other.size; // the size of the array
    arrayPointer = new int[size]; // new array with the same size
    for (int i = 0; i < size; ++i) // copying the elements to our new array
        arrayPointer[i] = other.arrayPointer[i];
}

ExtendableArray::~ExtendableArray() { // destructor
    delete[] arrayPointer;
}

ExtendableArray& ExtendableArray::operator=(const ExtendableArray &rhs) {//assign operator
    size = rhs.size; // the size of rhs
    delete[] arrayPointer; // delete old array
    arrayPointer = new int[size]; // create new with the same size
    for (int i = 0; i < size; ++i)
        arrayPointer[i] = rhs.arrayPointer[i]; // copy element to our array
    return *this;
}

ElementRef ExtendableArray::operator[](int i) {
    return ElementRef(*this, i); // return new Element ref
}

