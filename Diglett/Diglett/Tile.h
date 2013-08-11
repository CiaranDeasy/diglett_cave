#pragma once

class Tile {

public:
    enum Type {
        Dirt,
        Air,
        Surface
    };
    Tile(void);
    Tile(Type type);
    ~Tile(void);
    Type getType();

private:
    Type type;
};