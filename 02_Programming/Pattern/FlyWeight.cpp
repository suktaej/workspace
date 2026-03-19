#include <vector>
#include <cstdlib>
#include <iostream>

struct Mesh {};
enum Texture
{
    GRASS_TEXTURE,
    HILL_TEXTURE,
    RIVER_TEXTURE
};
struct Vector {};
struct Color {};

class Tree {
private:
    Mesh mesh;       
    Texture bark;    
    Texture leaves;  
    Vector position;
    double height;
    double thickness;
    Color barTint;
    Color leafTint;
};

class TreeModel {
private:
    Mesh mesh;
    Texture bark;
    Texture leaves;
};

class NewTree {
private:
    TreeModel* model;

    Vector position;
    double height;
    double thickness;
    Color barkTint;
    Color leafTint;
};

//===

enum Terrain {
    TERRAIN_GRASS,
    TERRAIN_HILL,
    TERRAIN_RIVER
};

class NewTerrain 
{
private:
    int movementCost_;
    bool isWater_;
    Texture texture_;

public:
    NewTerrain(int movementCost, bool isWater, Texture texture)
    : movementCost_(movementCost), isWater_(isWater), texture_(texture) { }

    int getMovementCost() const { 
        return movementCost_;
    }

    bool isWater() const { 
        return isWater_;
    }

    const Texture& getTexture() const {
        return texture_;
    }
};


class World 
{
private:
    Terrain tiles[100][100];
    
    NewTerrain* ntiles[100][100];
    NewTerrain grassTerrain_;
    NewTerrain hillTerrain_;
    NewTerrain riverTerrain_;

public:
    World()
        : grassTerrain_(1, false, GRASS_TEXTURE),
          hillTerrain_(3, false, HILL_TEXTURE),
          riverTerrain_(2, true, RIVER_TEXTURE) 
          {}

    int getMovementCost(int x, int y) 
    {
        switch (tiles[x][y])
        {
        case TERRAIN_GRASS:
            return 1;
        case TERRAIN_HILL:
            return 2;
        case TERRAIN_RIVER:
            return 3;
        }
    }

    bool isWater(int x, int y)
    {
        switch (tiles[x][y])
        {
        case TERRAIN_GRASS:
            return false;
        case TERRAIN_HILL:
            return false;
        case TERRAIN_RIVER:
            return true;
        }
    }

    void generateTerrain() 
    {
    for(int x = 0; x < 100; ++x)
        for(int y = 0; y < 100; ++y)
        {
            if(rand()%100 == 0)
                ntiles[x][y] = &hillTerrain_;
            else
                ntiles[x][y] = &grassTerrain_;
        }

    int x = rand()%100;
    for(int y = 0; y < 100; ++y)
        ntiles[x][y] = &riverTerrain_;
    }

    const NewTerrain& getTile(int x, int y) const 
    {
        return *ntiles[x][y];
    }
};

