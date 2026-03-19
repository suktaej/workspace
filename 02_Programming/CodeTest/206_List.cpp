#include <iostream>
#include <vector>

class List
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int x, Node *next) : data(x), next(next) {}
    };

private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

public:
    void push_front(int x);
    void push_back(int x);
    void pop_front();
    void insert_after(Node* pre, int x);
    void remove_after(Node* pre);
    Node* find(int x);
};


int main()
{
    return 0;
}