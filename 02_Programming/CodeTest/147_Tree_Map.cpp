#include <iostream>
#include <unordered_map>

std::unordered_map<char,std::pair<char,char>> tree;

void preOrder(char node) {
    if (node == '.') return;
    std::cout << node;
    preOrder(tree[node].first);
    preOrder(tree[node].second);
}

void inOrder(char node) {
    if (node == '.') return;
    inOrder(tree[node].first);
    std::cout << node;
    inOrder(tree[node].second);
}

void postOrder(char node) {
    if (node == '.') return;
    postOrder(tree[node].first);
    postOrder(tree[node].second);
    std::cout << node;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin>>n;
    tree.reserve(n);

    char root;
    for (int i = 0; i < n; ++i)
    {
        char p,l,r;
        std::cin >> p >> l >> r;

        if (i == 0)
            root = p;

        tree[p] = {l,r};
    }

    preOrder(root);   std::cout << '\n';
    inOrder(root);    std::cout << '\n';
    postOrder(root);  std::cout << '\n';

    return 0;
}