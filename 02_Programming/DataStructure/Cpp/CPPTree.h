#include "CPPVector.h"

template<typename T>
struct TreeNode
{
public:
    T data;
    TreeNode* left;
    TreeNode* right;
    int nodeHeight;

public:
    TreeNode(T value) 
    : data(value), left(nullptr), right(nullptr), nodeHeight(0) {}
};

template<typename T>
class CBinarySearchTree
{
public:
    CBinarySearchTree() 
    : root(nullptr) {}

    virtual ~CBinarySearchTree()
    {
        DestroyTree(root);
    }

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

protected:
    // 자식 노드가 2개 일 때 탐색용
    TreeNode<T>* FindMin(TreeNode<T>* node)
    {
        while(node && node->left != nullptr)
            node =  node->left;

        return node;
    }

private:
    void DestroyTree(TreeNode<T>* node)
    {
        if (nullptr == node)
            return;

        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }

    virtual TreeNode<T>* insert_Recursive(TreeNode<T>* node, const T& value)
    {
        if(nullptr == node)
            return new TreeNode<T>(value);

        if (value < node->data)
            node->left = insert_Recursive(node->left, value);
        else if (value > node->data)
            node->right = insert_Recursive(node->right, value);

        return node;
    }

    virtual TreeNode<T>* delete_Recursive(TreeNode<T>* node, const T& value)
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
};

template<typename T>
class CAVLTree : public CBinarySearchTree<T>
{
private:
    int GetHeight(TreeNode<T>* node)
    {
        return node ? node->nodeHeight : 0; //leaf node는 0, Internal node는 자신의 height
    }

    int GetBalance(TreeNode<T>* node)
    {
        if (!node)
            return 0;

        return GetHeight(node->left) - GetHeight(node->right);
    }

    TreeNode<T>* LRot(TreeNode<T>* node)
    {
        TreeNode<T>* newRoot = node->right;
        TreeNode<T>* movedSubTree = newRoot->left;

        newRoot->left = node;
        node->right = movedSubTree;

        node->nodeHeight = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
        newRoot->nodeHeight = 1 + std::max(GetHeight(newRoot->left), GetHeight(newRoot->right));

        return newRoot;
    }

    TreeNode<T>* RRot(TreeNode<T>* node)
    {
        TreeNode<T>* newRoot = node->left;
        TreeNode<T>* movedSubTree = newRoot->right;

        newRoot->right = node;
        node->left = movedSubTree;

        node->nodeHeight = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
        newRoot->nodeHeight = 1 + std::max(GetHeight(newRoot->left), GetHeight(newRoot->right));

        return newRoot;
    }

    TreeNode<T>* LRRot(TreeNode<T>* node)
    {
        node->left = LRot(node->left);
        return RRot(node);
    }

    TreeNode<T>* RLRot(TreeNode<T>* node)
    {
        node->right = RRot(node->right);
        return LRot(node);
    }

private:
    TreeNode<T>* insert_Recursive(TreeNode<T>* node, const T& value) override
    {
        if (!node)
            return new TreeNode<T>(value);

        if (value < node->data)
            node->left = insert_Recursive(node->left, value);
        else if (value > node->data)
            node->right = insert_Recursive(node->right, value);
        else
            return node;

        // 높이 갱신
        node->nodeHeight = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

        int balance = GetBalance(node);

        // 불균형 시 회전
        if (balance > 1 && value < node->left->data)
            return RRot(node); // LL
        if (balance < -1 && value > node->right->data)
            return LRot(node); // RR
        if (balance > 1 && value > node->left->data)
            return LRRot(node); // LR
        if (balance < -1 && value < node->right->data)
            return RLRot(node); // RL

        return node;
    }

    TreeNode<T>* delete_Recursive(TreeNode<T>* node, const T& value) override
    {
        if (nullptr == node)
            return node;

        if (value < node->data)
            node->left = delete_Recursive(node->left, value);
        else if (value > node->data)
            node->right = delete_Recursive(node->right, value);
        else
		{
            // 삭제노드 발견 시 자식노드 탐색
            if (nullptr == node->left || nullptr == node->right)
            {
                TreeNode<T>* temp = node->left ? node->left : node->right;
                if (nullptr == temp) // Leaf node
                {
                    temp = node;
                    node = nullptr;
                }
                else                // 자식이 하나일 경우
                    *node = *temp;  // 값을 복사

                delete temp;        // Heap에서 삭제
            }
            else                    // 자식이 두 개일 경우
            {
                // 오른쪽 서브트리 최소값으로 대체
                TreeNode<T>* temp = FindMin(node->right);
                node->data = temp->data;
                node->right = delete_Recursive(node->right, temp->data);
            }
		}

        if (nullptr == node) // Leaf삭제 후 null처리
            return node;

        node->nodeHeight = 1 + std::max(GetHeight(node->left), GetHeight(node->right));

        int balance = GetBalance(node);

        if (balance > 1 && GetBalance(node->left) >= 0) 
            return RRot(node);     // LL
        if (balance > 1 && GetBalance(node->left) < 0)
            return LRRot(node);    // LR
        if (balance < -1 && GetBalance(node->right) <= 0)
            return LRot(node);     // RR
        if (balance < -1 && GetBalance(node->right) > 0)  
            return RLRot(node);    // RL

        return node;
    }
};