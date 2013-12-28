#include "Inventory.h"

template <class T> Inventory<T>::Inventory( int maxInventory ) {
    this->maxInventory = maxInventory;
}

template <class T> Inventory<T>::~Inventory(void) {
}

template <class T> bool Inventory<T>::addItem( T item ) {
    if( contents.size() == maxInventory ) return false;
    if( item->getName() == "NULL" ) return true;
    contents.push_back( item );
    return true;
}

const unsigned int DEFAULT_MAX_INVENTORY = 32;