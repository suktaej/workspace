#pragma region basic
class OldMonster {};
class Sorcerer : public OldMonster {};

class OldSpawner {
public:
    virtual ~OldSpawner() {};
    virtual OldMonster* spawnMonster() = 0;
};

class SorcererSpawner : public OldSpawner {
public:
    virtual OldMonster* spawnMonster() {
        return new Sorcerer;
    }
};

#pragma endregion basic

#pragma region clone 
class Monster {
    public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;
};

class Ghost : public Monster {
public:
    Ghost(int health, int speed)
    : health_(health),
     speed_(speed) {
     }

    virtual Monster* clone() {
        return new Ghost(health_, speed_);
    }

private:
    int health_;
    int speed_;
};

class Spawner {
public:
    Spawner(Monster* prototype) : prototype_(prototype) {}

    Monster* spawnMonster() {
        return prototype_->clone();
    }

private:
    Monster* prototype_;

public:
    Spawner(Monster *(*spawn)()) : spawn_(spawn) {}
    // Spawner(std::function<Monster*()> spawn) : spawn_(spawn) {}
    Monster* spawnMonster() { return spawn_(); }

private:
    Monster*(*spawn_)();
    // std::function<Monster*()> spawn_;

};

class Demon : public Monster {
public:
    Demon(int health, int speed)
    : health_(health),
     speed_(speed) {
     }

    virtual Monster* clone() {
        return new Demon(health_, speed_);
    }

private:
    int health_;
    int speed_;
};

Monster* spawnDemon(int hp, int spd) {
    return new Demon(hp, spd);
}
#pragma endregion clone 

#pragma region template
class TemplateSpawner {
public:
    virtual ~TemplateSpawner() {}
    virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public TemplateSpawner {
public:
    virtual Monster* spawnMonster() {
        return new T();
    }
};
#pragma endregion template
int main()
{
    Monster* ghostPrototype = new Ghost(15, 3);
    Spawner* ghostSpawner = new Spawner(ghostPrototype);
    // function pointer
    Spawner* demonSpawner = new Spawner(spawnDemon(10,10));
    // template
    TemplateSpawner* ghostSpawner2 = new SpawnerFor<Ghost>();
    return 0;
}