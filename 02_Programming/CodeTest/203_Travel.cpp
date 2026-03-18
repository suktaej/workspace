#include <iostream>
#include <vector>

char tree[128] = {'1', '+', '4', '-' ,'7'};

int parent(int i) { return (i - 1) / 2; }
int left(int i)   { return 2 * i + 1; }
int right(int i)  { return 2 * i + 2; }

void inOrder(int i)
{
    int ts = sizeof(tree)/sizeof(int);
    
    if(i >= ts)
        return;

    inOrder(left(i));
    std::cout<<tree[i];
    inOrder(right(i));
}

void inOrder(int i)
{
    int ts = sizeof(tree)/sizeof(int);
    
    if(i >= ts)
        return;

    inOrder(left(i));
    std::cout<<tree[i];
    inOrder(right(i));
}

int main()
{
    inOrder(0);
    return 0;
}