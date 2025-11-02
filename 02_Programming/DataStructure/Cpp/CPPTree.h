#include "CPPVector.h"

enum NodeColor
{
    Red,
    Black
};

template<typename T>
struct TreeNode
{
public:
    T data;
    TreeNode* left;
    TreeNode* right;
    int nodeHeight;     // AVL Tree
    TreeNode* parent;   // RedBlack Tree
    NodeColor color;    // RedBlack Tree

    public:
    TreeNode(T value) 
    : data(value), left(nullptr), right(nullptr), nodeHeight(0), parent(nullptr), color(Red) {}
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

protected:
    TreeNode<T>* root;

public:
    virtual void insert(const T& value)
    {
        root = insert_Recursive(root, value);
    }

    // delete is keyward in C++
    virtual void remove(const T& value)
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

    TreeNode<T>* FindNode(const T& value)
    {
        TreeNode<T>* currentNode = root;

        while (currentNode)
        {
            if (value == currentNode->data)
                return currentNode;
            else if (value < currentNode->data)
                currentNode = currentNode->left;
            else if (value > currentNode->data)
                currentNode = currentNode->right;
        }

        return nullptr;
    }

protected:
    // 자식 노드가 2개 일 때 탐색용
    TreeNode<T>* FindMin(TreeNode<T>* node)
    {
        while(node && node->left != nullptr)
            node =  node->left;

        return node;
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

private:
    void DestroyTree(TreeNode<T>* node)
    {
        if (nullptr == node)
            return;

        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
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

                delete temp;      // Heap에서 삭제
            }
            else                    // 자식이 두 개일 경우
            {
                // 오른쪽 서브트리 최소값으로 대체
                TreeNode<T>* temp = this->FindMin(node->right);
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

template<typename T>
class CRedBlackTree : public CBinarySearchTree<T>
{
protected:
    using CBinarySearchTree<T>::insert_Recursive;   // name hiding 방지
    using CBinarySearchTree<T>::root;               // 부모 클래스의 root를 자식의 scope에 노출

public:
    void insert(const T& value) override
    {
        this->root = insert_Recursive(this->root, nullptr, value);
        FixInsert(this->FindNode(value)); // 새로 삽입된 노드 포인터를 이용
        this->root->color = Black;
    }

    void remove(const T& value) override
    {
        TreeNode<T>* node = this->FindNode(value);

        if (!node) 
            return;

        DeleteNode(node);
    }

private:
    TreeNode<T>* insert_Recursive(TreeNode<T>* node, TreeNode<T>* parent, const T& value)
    {
        if (node == nullptr)
        {
            TreeNode<T>* newNode = new TreeNode<T>(value);
            newNode->parent = parent;
            newNode->color = Red;
            return newNode;
        }

        if (value < node->data)
            node->left = insert_Recursive(node->left, node, value);
        else if (value > node->data)
            node->right = insert_Recursive(node->right, node, value);

        return node;
    }

    void FixInsert(TreeNode<T>* node) 
    {
        while (node != root && node->parent->color == Red)
        {
            TreeNode<T>* parent = node->parent;
            TreeNode<T>* grand = parent->parent;

            if (parent == grand->left)
            {
                TreeNode<T>* uncle = grand->right;
                
                // Uncle is red (Recoloring)
                if (uncle && uncle->color == Red)
                {
                    parent->color = Black;
                    uncle->color = Black;
                    grand->color = Red;
                    node = grand;
                }
                else
                {
                    // Uncle is black (Restructuring)
                    if (node == parent->right)
                    {
                        node = parent;
                        LRot(node);
                    }

                    parent->color = Black;
                    grand->color = Red;
                    RRot(grand);
                }
            }
            else if(parent == grand->right)
            {
                TreeNode<T>* uncle = grand->left;

                if (uncle && uncle->color == Red)
                {
                    parent->color = Black;
                    uncle->color = Black;
                    grand->color = Red;
                    node = grand;
                }
                else
                {
                    if (node == parent->left)
                    {
                        node = parent;
                        RRot(node);
                    }

                    parent->color = Black;
                    grand->color = Red;
                    LRot(grand);
                }
            }
        }
        root->color = Black;
    }

    void DeleteNode(TreeNode<T>* node)
    {
        TreeNode<T>* fixNode = nullptr;
        TreeNode<T>* replacementNode = node;
        NodeColor originalColor = replacementNode->color;

        // Child가 1개일 경우
        if (!node->left) 
        {
            fixNode = node->right;
            Transplant(node, node->right);
        }
        else if (!node->right) 
        {
            fixNode = node->left;
            Transplant(node, node->left);
        }
        // Child가 2개일 경우
        else 
        {
            replacementNode = this->FindMin(node->right);
            originalColor = replacementNode->color;
            fixNode = replacementNode->right;

            if (replacementNode->parent == node)
            {
                if (fixNode)
                    fixNode->parent = replacementNode;
            }
            else
            {
                Transplant(replacementNode, replacementNode->right);
                replacementNode->right = node->right;

                if (replacementNode->right) 
                    replacementNode->right->parent = replacementNode;
            }

            Transplant(node, replacementNode);
            replacementNode->left = node->left;

            if (replacementNode->left) 
                replacementNode->left->parent = replacementNode;

            replacementNode->color = node->color;
        }

        delete node;

        if (originalColor == Black)
            FixDelete(fixNode);
    }

    void Transplant(TreeNode<T>* oldNode, TreeNode<T>* newNode)
    {
        if (!oldNode->parent)
            root = newNode;
        else if (oldNode == oldNode->parent->left)
            oldNode->parent->left = newNode;
        else if (oldNode == oldNode->parent->right)
            oldNode->parent->right = newNode;

        if (newNode)
            newNode->parent = oldNode->parent;
    }

    void FixDelete(TreeNode<T>* fixNode)
    {
        while (fixNode != root && (!fixNode || fixNode->color == Black))
        {
            TreeNode<T>* parent = fixNode ? fixNode->parent : nullptr;

            if (!parent) 
                break;

            TreeNode<T>* siblingNode = (fixNode == parent->left) ? parent->right : parent->left;

            if (siblingNode && siblingNode->color == Red) 
            {
                siblingNode->color = Black;
                parent->color = Red;

                if (fixNode == parent->left) 
                    LRot(parent);
                else 
                    RRot(parent);

                siblingNode = (fixNode == parent->left) ? parent->right : parent->left;
            }

            if ((!siblingNode->left || siblingNode->left->color == Black) &&
                (!siblingNode->right || siblingNode->right->color == Black)) 
            {
                if (siblingNode) 
                    siblingNode->color = Red;

                fixNode = parent;
            }
            else 
            {
                if (fixNode == parent->left) 
                {
                    if (!siblingNode->right || siblingNode->right->color == Black) 
                    {
                        if (siblingNode->left) 
                            siblingNode->left->color = Black;

                        siblingNode->color = Red;
                        RRot(siblingNode);
                        siblingNode = parent->right;
                    }
                    if (siblingNode)
                        siblingNode->color = parent->color;

                    parent->color = Black;

                    if (siblingNode && siblingNode->right)
                        siblingNode->right->color = Black;

                    LRot(parent);
                    fixNode = root;
                }
                else 
                {
                    if (!siblingNode->left || siblingNode->left->color == Black) 
                    {
                        if (siblingNode->right)
                            siblingNode->right->color = Black;

                        siblingNode->color = Red;
                        LRot(siblingNode);
                        siblingNode = parent->left;
                    }
                    if (siblingNode)
                        siblingNode->color = parent->color;

                    parent->color = Black;

                    if (siblingNode && siblingNode->left) 
                        siblingNode->left->color = Black;

                    RRot(parent);
                    fixNode = root;
                }
            }
        }

        if (fixNode) 
            fixNode->color = Black;
    }
    
    void LRot(TreeNode<T>* node)
    {
        TreeNode<T>* rotNode = node->right;
        node->right = rotNode->left;

        if (rotNode->left)
            rotNode->left->parent = node;

        rotNode->parent = node->parent;

        if (!node->parent)
            root = rotNode;
        else if (node == node->parent->left)
            node->parent->left = rotNode;
        else
            node->parent->right = rotNode;

        rotNode->left = node;
        node->parent = rotNode;
    }
    
    void RRot(TreeNode<T>* node)
    {
        TreeNode<T>* rotNode = node->left;
        node->left = rotNode->right;
        
        // parents 정보갱신
        if (rotNode->right)
            rotNode->right->parent = node;

        rotNode->parent = node->parent;

        if (!node->parent)
            root = rotNode;
        else if (node == node->parent->right)
            node->parent->right = rotNode;
        else
            node->parent->left = rotNode;
        //parent 갱신완료

        rotNode->right = node;
        node->parent = rotNode;
    }
};