#ifndef ZADANKO5_MYSMARTPOINTER_H
#define ZADANKO5_MYSMARTPOINTER_H

#include <iostream>

class RefCounter
{
public:
    RefCounter() { counter=0; }
    int increment() { return(++counter); }
    int decrement() { return(--counter); };
    int get() { return(counter); }
private:
    int counter;
};

template <typename T> class SmartPointer
{
public:
    SmartPointer(T *otherPointer)
    {
        pointer = otherPointer;
        counter = new RefCounter();
        counter->increment();
    }
    SmartPointer(const SmartPointer &otherPointer)
    {
        pointer = otherPointer.pointer;
        counter = otherPointer.counter;
        counter->increment();
    }
    SmartPointer(SmartPointer&& otherPointer)
    {
        counter = otherPointer.counter;
        pointer = otherPointer.pointer;
        otherPointer.counter = new RefCounter();
        otherPointer.pointer = NULL;
    }

    ~SmartPointer() {
        clearSafely();
    }
    T& operator*() { return(*pointer); }
    T* operator->() { return(pointer); }
    SmartPointer operator=(const SmartPointer &otherPointer){
        this->clearSafely();
        pointer = otherPointer.pointer;
        counter = otherPointer.counter;
        counter->increment();
        return (*this);
    }
    T *getPointer(){
        return pointer;
    }
private:
    T *pointer;
    RefCounter *counter;
    void clearSafely()
    {
        counter->decrement();
        if (counter->get() == 0) {
            delete pointer;
            delete counter;
        }
    }
};




#endif
