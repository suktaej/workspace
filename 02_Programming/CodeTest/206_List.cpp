#include <iostream>
#include <memory>
#include <vector>

class List
{
public:
    struct Node
    {
        int data;
        // Node *next;
        std::unique_ptr<Node> next;
        Node(int x, Node *next) : data(x), next(next) {}
    };

private:
    // Node* head = nullptr;
    std::unique_ptr<Node> head = nullptr;
    Node* tail = nullptr;
    int size = 0;

public:
    void push_front(int x);
    void push_back(int x);
    void pop_front();
    void pop_back();
    void insert_after(Node* pre, int x);
    void remove_after(Node* pre);
    Node* find(int x);
};

void List::push_front(int x)
{
    auto newNode = std::make_unique<Node>(x, nullptr);

    if(size == 0)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    ++size;
}

void List::push_back(int x)
{
    auto newNode = std::make_unique<Node>(x,nullptr);

    if(size == 0)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        Node* rawNewNode = newNode.get();
        tail->next = std::move(newNode);
        tail = rawNewNode;
    }
    ++size;
}

void List::pop_back()
{
    if(!head)
        return;

    if(head.get() == tail)
    {
        head.reset();
        tail = nullptr;
    }
    else
    {
        Node* temp = head.get();
        while (temp->next.get() != tail)
            temp = temp->next.get();

        temp->next.reset();
        tail = temp;
    }
    --size;
}

void List::pop_front()
{
    if(!head)
        return;

    if (head.get() == tail)
    {
        head.reset();
        tail = nullptr;
    }
    else
    {
        head = std::move(head->next);
    }
    --size;
}

void List::insert_after(Node* pre, int x)
{
    if(!head || !pre)
        return;

    auto newNode = std::make_unique<Node>(x,nullptr);

    newNode->next = std::move(pre->next);
    pre->next = std::move(newNode);
    
    if(pre == tail)
        tail = pre->next.get();

    ++size;
}

void List::remove_after(Node* pre)
{
    if(!head || !pre ||!pre->next)
        return;

    std::unique_ptr<Node> target = std::move(pre->next);
    pre->next = std::move(target->next);
    
    if(pre->next == nullptr)
        tail = pre;

    --size;
}

Node* List::find(int x)
{

}

int main()
{
    return 0;
}