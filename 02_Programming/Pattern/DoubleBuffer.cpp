#include <iostream>

constexpr char WHITE = ' ';
constexpr char BLACK = 'x';

class Framebuffer {
public:
    Framebuffer() { clear(); }
    void clear() {
        for(int i = 0; i < WIDTH * HEIGHT; ++i) {
            pixels_[i] = WHITE;
        }
    }
    void draw(int x, int y) {
        pixels_[(WIDTH * y) + x] = BLACK;
    }

    void view()
    {
        for(int i=0;i<HEIGHT;++i)
        {
            for(int j =0; j<WIDTH;++j)
                std::cout << pixels_[(i * WIDTH) + j];
            std::cout<<'\n';
        }
    }

    const char* getPixels() { return pixels_; }

private:
    static const int WIDTH = 16;
    static const int HEIGHT = 9;
    char pixels_[WIDTH * HEIGHT];
};

class Scene {
public:
    Scene() : current_(&buffers_[0]), next_(&buffers_[1]) {}

private:
    Framebuffer buffers_[2];
    Framebuffer* current_;
    Framebuffer* next_;

public:
    void draw() {
        next_->clear();
        next_->draw(1, 1);
        next_->draw(4, 1);
        next_->draw(1, 3);
        next_->draw(2, 4);
        next_->draw(3, 4);
        next_->draw(4, 3);
        next_->view();
    }

    Framebuffer& getBuffer() { return *current_; }

private:
    void swap() {
        // Framebuffer* temp = current_;
        // current_ = next_;
        // next_ = temp;
        std::swap(next_,current_);
    }

};

class Actor {
public:
    // Actor(const char* name) : slapped_(false), name_(name) {}
    Actor(const char* name) : currentSlapped_(false), name_(name) {}
    virtual ~Actor() {}
    virtual void update() = 0;
    // void reset() { slapped_ = false; }
    // void slap() { slapped_ = true; }
    void slap() { nextSlapped_ = true; }
    // bool wasSlapped() { return slapped_;  }
    bool wasSlapped() { return currentSlapped_;  }
    void swap() 
    { 
        currentSlapped_ = nextSlapped_;
        nextSlapped_ = false;
    }
    const std::string& name() const { return name_; }

private:
    bool currentSlapped_;
    bool nextSlapped_;
    //bool slapped_;
    std::string name_;
};

class Comedian : public Actor {
public:
    Comedian(const char* name): Actor(name) {}
    void face(Actor* actor) { facing_ = actor; }
    virtual void update() 
    {
        if(wasSlapped())
        {
            facing_->slap();
            std::cout<<name()<<" slap to "<<facing_->name()<<'\n';
        }
    }

private:
    Actor* facing_;
};

class Stage {
public:
    void add(Actor* actor, int index) { actors_[index] = actor; }
    void update() 
    {
        // for(int i = 0; i < NUM_ACTORS; ++i) 
        // {
        //     actors_[i]->update();
        //     actors_[i]->reset();
        // }
        for (int i = 0; i < NUM_ACTORS; ++i)
            actors_[i]->update();
        for (int i = 0; i < NUM_ACTORS; ++i)
            actors_[i]->swap();
    }

private:
    static const int NUM_ACTORS = 3;
    Actor* actors_[NUM_ACTORS];
};

int main()
{
    Stage stage;

    Comedian *harry = new Comedian("harry");
    Comedian *baldy = new Comedian("baldy");
    Comedian *chump = new Comedian("chump");

    harry->face(baldy);
    baldy->face(chump);
    chump->face(harry);

    // stage.add(harry, 0);
    // stage.add(baldy, 1);
    // stage.add(chump, 2);
    stage.add(harry, 2);
    stage.add(baldy, 1);
    stage.add(chump, 0);

    harry->slap();
    stage.update();

    return 0;
}