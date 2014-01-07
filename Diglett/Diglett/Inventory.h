#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

template <class T>
class Inventory {
public:

    Inventory( int maxInventory = DEFAULT_MAX_INVENTORY );
    ~Inventory(void);

    // Adds the given Item to the inventory. Returns false if the Item is not 
    // added due to full inventory.
    bool addItem( T item );

    std::vector<T> getContents() const;
    int getCurrentSize() const;

    // Removes all items from the Inventory.
    void clear();

private: 
    static const unsigned int DEFAULT_MAX_INVENTORY;
    
    std::vector<T> contents;
    
    // The maximum number of items that the inventory can contain.
    int maxInventory;

};

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

template <class T> std::vector<T> Inventory<T>::getContents() const {
    return contents;
}

template <class T> int Inventory<T>::getCurrentSize() const {
    return contents.size();
}

template <class T> void Inventory<T>::clear() {
    contents.clear();
}

template <class T> const unsigned int Inventory<T>::DEFAULT_MAX_INVENTORY = 32;