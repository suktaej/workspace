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

public:
    ~List() {
        // head가 nullptr이 될 때까지 반복하며 소유권을 하나씩 해제
        while (head) 
            head = std::move(head->next);
            // head가 가리키는 노드를 직접 파괴하는 대신,
            // head를 다음 노드로 옮기면 이전 노드는 자동으로 안전하게 삭제됨
            
            // 동작 원리:
            // 1. head->next의 소유권을 일시적으로 뺏어와서 head에 넣음
            // 2. 이 과정에서 원래 head가 소유하던 노드는 소유주가 없어지므로 삭제됨
            // 3. 루프를 돌기 때문에 스택을 깊게 쌓지 않고 하나씩 순차적으로 처리함
    }

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
    Node* find(int x) const;
    void print_reverse(Node* n);
    void reverse();
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

List::Node* List::find(int x) const
{
    Node* temp = head.get();

    while (temp != nullptr)
    {
        if(temp->data == x)
            return temp;

        temp = temp->next.get();
    }

    return nullptr;
}

void List::print_reverse(Node *n)
{
    if(!n)
        return;
    print_reverse(n->next.get());
    std::cout<<n->data<<' ';
}

void List::reverse()
{
    if(!head || !head->next)
        return;

    std::unique_ptr<Node> prev = nullptr;
    std::unique_ptr<Node> curr = std::move(head);
    tail = curr.get();

    while(curr)
    {
        std::unique_ptr<Node> nextNode = std::move(curr->next);
        curr->next = std::move(prev);
        prev = std::move(curr);
        curr = std::move(nextNode);
    }

    head = std::move(prev);
}

int main()
{
    return 0;
}