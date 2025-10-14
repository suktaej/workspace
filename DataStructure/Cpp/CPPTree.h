#include "CPPVector.h"

template<typename T>
struct TreeNode
{
public:
    T data;
    TreeNode* left;
    TreeNode* right;
    int balanceFactor;

public:
    TreeNode(T value) 
    : data(value), left(nullptr), right(nullptr), balanceFactor(0) {}
};

template<typename T>
class CBinarySearchTree
{
public:
    CBinarySearchTree() 
    : root(nullptr) {}

private:
    TreeNode<T>* root;

public:
    void insert(const T& value)
    {
        root = insert_Recursive(root, value);
    }

    // delete is keyward in C++
    void remove(const T& value)
    {
        root = delete_Recursive(root, value);            
    }

    void inorder()
    {
        inorder_Recursive(root);
        std::cout<<std::endl;
    }

    void preorder()
    {
        preorder_Recursive(root);
        std::cout<<std::endl; 
    }

    void postorder()
    {
        postorder_Recursive(root);
        std::cout<<std::endl; 
    }

private:
    TreeNode<T>* insert_Recursive(TreeNode<T>* node, const T& value)
    {
        if(nullptr == node)
            return new TreeNode<T>(value);

        if(value < node->data)
            node->left = insert_Recursive(node->left, value);
        else if(value > node->data)
            node->right = insert_Recursive(node->right, value);

        return node;
    }

    void inorder_Recursive(TreeNode<T>* node)
    {
        if(nullptr == node)
            return;

        inorder_Recursive(node->left);
        std::cout<<node->data<<" ";
        inorder_Recursive(node->right);
    }

    void preorder_Recursive(TreeNode<T>* node)
    {
        if(nullptr == node)
            return;

        std::cout<<node->data<<" ";
        preorder_Recursive(node->left);
        preorder_Recursive(node->right);
    }

    void postorder_Recursive(TreeNode<T>* node)
    {
        if(nullptr == node)
            return;

        postorder_Recursive(node->left);
        postorder_Recursive(node->right);
        std::cout<<node->data<<" ";
    }

    TreeNode<T>* delete_Recursive(TreeNode<T>* node, const T& value)
    {
        if(nullptr == node)
            return node;

        if(value < node->data)
            node->left = delete_Recursive(node->left, value);
        else if(value > node->data)
            node->right = delete_Recursive(node->right, value);
        else if(value == node->data)
        {
            // 리프 노드
            if(nullptr == node->left &&
                nullptr == node->right)
            {
                delete node;
                return nullptr;
            }
            // 자식이 하나일 경우
            else if(nullptr == node->left &&
                nullptr != node->right)
            {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if(nullptr == node->right &&
                nullptr != node->left)
            {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            // 자식이 둘 일 경우
            else 
            {
                // 삭제할 노드의 값보다 큰 값들 중 가장 작은 값을 삭제할 노드로 복사
                // predecessor : 작은 값들 중 가장 큰 값
                TreeNode<T>* successor = FindMin(node->right);
                node->data = successor->data;
                // 남아있는 복사대상을 제거
                node->right = delete_Recursive(node->right,successor->data);
            }
        }
        return node;
    }

    // 자식 노드가 2개 일 때 탐색용
    TreeNode<T>* FindMin(TreeNode<T>* node)
    {
        while(node && node->left != nullptr)
            node =  node->left;

        return node;
    }
};

template<typename T>
class CAVLTree : public CBinarySearchTree<T>
{
public:
    void LLRot();
    void RRRot();
    void LRRot();
    void RLRot();
};