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

private: 
    static const unsigned int DEFAULT_MAX_INVENTORY;
    
    std::vector<T> contents;
    
    // The maximum number of items that the inventory can contain.
    int maxInventory;

};

