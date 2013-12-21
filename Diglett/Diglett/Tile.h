#pragma once

class Tile {

public:
    enum Type {
        Dirt,
        Air,
        Surface,
        Gold,
        // Newly added types must be added to the diggableByType array!
        Count // A fake type whose value is the no. of elements in the enum.
    };
    Tile(void);
    Tile(Type type);
    ~Tile(void);
    Type getType();
    void dig();
    static bool diggable(Tile t);

private:
    Type type;
    static bool diggableByType[Count];
};