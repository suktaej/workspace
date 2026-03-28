#include <iostream>
#include <vector>

int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

struct Node
{
public:
    char data;
    Node* left; 
    Node* right;

public:
    Node() : data(), left(nullptr), right(nullptr) {}
    Node(char inp, Node* pl, Node* pr) : data(inp), left(pl), right(pr) {}
};

std::vector<Node*> nodes;

Node* makeNode(char data)
{
    for (auto &k : nodes)
        if (k->data == data)
            return k;

    Node* newNode = new Node(data,nullptr,nullptr);
    nodes.push_back(newNode);
    return newNode;
}

void preOrder(Node* node)
{
    if(node == nullptr)
        return;

    std::cout<<node->data;
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(Node* node)
{
    if(node == nullptr)
        return;

    inOrder(node->left);
    std::cout<<node->data;
    inOrder(node->right);
}

void postOrder(Node* node)
{
    if(node == nullptr)
        return;

    postOrder(node->left);
    postOrder(node->right);
    std::cout<<node->data;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;
    nodes.reserve(n);

    for(int i =0;i<n;++i)
    {
        char data;
        Node* parents;

        for(int j=0;j<3;++j)
        {
            std::cin >> data;

            if (data == '.')
                continue;

            if(j == 0)
                parents = makeNode(data);
            else if(j == 1)
            {
                Node* temp = makeNode(data);
                parents->left = temp;
            }
            else if(j == 2)
            {
                Node* temp = makeNode(data);
                parents->right= temp;
            }
        }
    }

    preOrder(nodes[0]);
    std::cout<<'\n';
    inOrder(nodes[0]);
    std::cout<<'\n';
    postOrder(nodes[0]);

    for(auto &it : nodes)
        delete it;

    return 0;
}