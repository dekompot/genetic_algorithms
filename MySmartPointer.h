//
// Created by 48791 on 14.12.2022.
//

#ifndef ZADANKO5_MYSMARTPOINTER_H
#define ZADANKO5_MYSMARTPOINTER_H

#include <iostream>

#define DEBUG true
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

template <typename T> class MySmartPointer
{
public:
    MySmartPointer(T *otherPointer)
    {
        pointer = otherPointer;
        counter = new RefCounter();
        counter->increment();
        //if (DEBUG) std::cout<<"zwykly konstruktor, mam : "<< *pointer << std::endl;
    }
    MySmartPointer(const MySmartPointer &otherPonter)
    {
        pointer = otherPonter.pointer;
        counter = otherPonter.counter;
        counter->increment();
        if (DEBUG) std::cout<<"konstruktor kopiujacy mam : "<< *pointer << std::endl;
    }
    ~MySmartPointer() {
        clearSafely();
        if (DEBUG) std::cout<<"destruktor"<<std::endl;
    }
    T& operator*() { return(*pointer); }
    T* operator->() { return(pointer); }
    MySmartPointer operator=(const MySmartPointer &otherPointer){
        this->clearSafely();
        pointer = otherPointer.pointer;
        counter = otherPointer.counter;
        counter->increment();
        if (DEBUG) std::cout<<"operator przypisania : "<< *pointer << std::endl;
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
            std::cout<<"alibaba";
            delete[] pointer;
            delete counter;
        }
    }
};




#endif //ZADANKO5_MYSMARTPOINTER_H
