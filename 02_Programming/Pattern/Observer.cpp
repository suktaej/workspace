#include <iostream>
#include <vector>

enum class Entity
{};
enum class Event
{
    EVENT_ENTITY_FELL
};

class Observer 
{
    friend class NewSubject;

private:
    Observer* next;

public:
    Observer() : next(nullptr){};
    virtual ~Observer(){};
    virtual void onNotify(const Entity& entity, Event evet) = 0;
};

class Achievements : public Observer
{
public:
    virtual void onNotify(const Entity& entity, Event evet) = 0;
};

class Subject 
{
private:
    std::vector<Observer*> observers;
    int numObservers;

public:
    void addObserver(Observer* o) { observers.push_back(o); }

protected:
    void notify(const Entity& entity, Event event) {
        for(int i = 0; i < numObservers; ++i) {
            observers[i]->onNotify(entity, event);
        }
    }
};

class NewSubject
{
private:
    Observer* head;
    int numObservers;

public:
    NewSubject() : head(nullptr){}

public:
    void addObserver(Observer* observer) {
        observer->next = head;
        head = observer;
    }

    void removeObserver(Observer* observer) {
        if(head == observer)
        {
            head = observer->next;
            observer->next = nullptr;
            return;
        }

        Observer* cur = head;

        while(cur!=nullptr)
        {
            if (cur->next == observer)
            {
                cur->next = observer->next;
                observer->next = nullptr;
                return;
            }
            cur = cur->next;
        }
    }

protected:
    void notify(const Entity& entity, Event event) {
        Observer* observer = head;
        while(observer!=nullptr)
        {
            observer->onNotify(entity,event);
            observer = observer->next;
        }
    }
};

class Physics : public NewSubject {
public:
    void updateEntity(Entity& entity);
};

int main()
{
    return 0;
}