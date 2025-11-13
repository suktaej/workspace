#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// =============================
//  B-Tree (Order-based version)
// =============================
//
//  정의:
//   - order(m): 한 노드가 가질 수 있는 최대 child 수
//   - 각 노드의 key 개수는 [ceil(m/2)-1, m-1]
//   - 각 노드의 child 개수는 [ceil(m/2), m]
//   - 모든 leaf는 동일한 깊이
//

template <typename T>
class BTree {
public:
    struct Node {
        bool leaf;
        vector<T> keys;
        vector<Node*> children;

        Node(bool isLeaf, int order) : leaf(isLeaf) {
            keys.reserve(order - 1);
            children.reserve(order);
        }
    };

    explicit BTree(int order)
        : root(nullptr), m(order)
    {
        if (order < 3)
            throw invalid_argument("Order must be >= 3");
    }

    ~BTree() { freeNode(root); }

    // ---------- Search ----------
    bool search(const T& key) const {
        return searchNode(root, key) != nullptr;
    }

    // ---------- Insert ----------
    void insert(const T& key) {
        if (!root) {
            root = new Node(true, m);
            root->keys.push_back(key);
            return;
        }

        if ((int)root->keys.size() == m - 1) {
            Node* newRoot = new Node(false, m);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    // ---------- Delete ----------
    void remove(const T& key) {
        if (!root) return;

        removeNode(root, key);

        // 루트가 비었고 자식이 하나라면 그 자식으로 대체
        if (root->keys.empty() && !root->leaf) {
            Node* old = root;
            root = root->children[0];
            delete old;
        }
    }

    // ---------- Traverse ----------
    void traverse() const {
        traverseNode(root);
        cout << "\n";
    }

private:
    Node* root;
    int m; // order

    // 최소 키 개수
    int minKeys() const { return (int)ceil(m / 2.0) - 1; }
    // 최소 자식 개수
    int minChildren() const { return (int)ceil(m / 2.0); }

    // ==============================
    //         내부 유틸 함수들
    // ==============================
    void freeNode(Node* node) {
        if (!node) return;
        for (auto* ch : node->children)
            freeNode(ch);
        delete node;
    }

    Node* searchNode(Node* node, const T& key) const {
        if (!node) return nullptr;
        int i = 0;
        while (i < (int)node->keys.size() && key > node->keys[i]) ++i;

        if (i < (int)node->keys.size() && node->keys[i] == key)
            return node;

        if (node->leaf)
            return nullptr;

        return searchNode(node->children[i], key);
    }

    void traverseNode(Node* node) const {
        if (!node) return;
        int i;
        for (i = 0; i < (int)node->keys.size(); ++i) {
            if (!node->leaf) traverseNode(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->leaf) traverseNode(node->children[i]);
    }

    // ------------------------------------
    // Split a full child into two halves
    // ------------------------------------
    void splitChild(Node* parent, int index, Node* fullChild) {
        int mid = (m - 1) / 2; // 중앙 인덱스

        Node* sibling = new Node(fullChild->leaf, m);

        // 오른쪽 절반 키 이동
        for (int j = mid + 1; j < (int)fullChild->keys.size(); ++j)
            sibling->keys.push_back(fullChild->keys[j]);

        // 자식 노드 복사 (leaf 아님)
        if (!fullChild->leaf) {
            for (int j = mid + 1; j < (int)fullChild->children.size(); ++j)
                sibling->children.push_back(fullChild->children[j]);
        }

        // fullChild 크기 조정
        fullChild->keys.resize(mid);
        if (!fullChild->leaf)
            fullChild->children.resize(mid + 1);

        // 부모에 삽입
        parent->keys.insert(parent->keys.begin() + index, fullChild->keys[mid]);
        parent->children.insert(parent->children.begin() + index + 1, sibling);
    }

    void insertNonFull(Node* node, const T& key) {
        int i = (int)node->keys.size() - 1;

        if (node->leaf) {
            node->keys.push_back(T());
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                --i;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && key < node->keys[i]) --i;
            ++i;

            if ((int)node->children[i]->keys.size() == m - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i]) ++i;
            }
            insertNonFull(node->children[i], key);
        }
    }

    // ------------------------------------
    // 삭제 관련 함수들
    // ------------------------------------
    void removeNode(Node* node, const T& key) {
        int idx = findKey(node, key);

        // (1) key 존재함
        if (idx < (int)node->keys.size() && node->keys[idx] == key) {
            if (node->leaf)
                removeFromLeaf(node, idx);
            else
                removeFromInternal(node, idx);
        } else {
            if (node->leaf)
                return; // 존재하지 않음

            bool atEnd = (idx == (int)node->keys.size());

            // 자식이 최소 키만 가질 경우 보정
            if ((int)node->children[idx]->keys.size() == minKeys())
                fill(node, idx);

            if (atEnd && idx > (int)node->keys.size())
                removeNode(node->children[idx - 1], key);
            else
                removeNode(node->children[idx], key);
        }
    }

    int findKey(Node* node, const T& key) {
        int idx = 0;
        while (idx < (int)node->keys.size() && node->keys[idx] < key)
            ++idx;
        return idx;
    }

    void removeFromLeaf(Node* node, int idx) {
        node->keys.erase(node->keys.begin() + idx);
    }

    void removeFromInternal(Node* node, int idx) {
        T k = node->keys[idx];

        if ((int)node->children[idx]->keys.size() >= minChildren()) {
            T pred = getPredecessor(node->children[idx]);
            node->keys[idx] = pred;
            removeNode(node->children[idx], pred);
        }
        else if ((int)node->children[idx + 1]->keys.size() >= minChildren()) {
            T succ = getSuccessor(node->children[idx + 1]);
            node->keys[idx] = succ;
            removeNode(node->children[idx + 1], succ);
        }
        else {
            merge(node, idx);
            removeNode(node->children[idx], k);
        }
    }

    T getPredecessor(Node* node) {
        while (!node->leaf)
            node = node->children.back();
        return node->keys.back();
    }

    T getSuccessor(Node* node) {
        while (!node->leaf)
            node = node->children.front();
        return node->keys.front();
    }

    void fill(Node* node, int idx) {
        if (idx != 0 && (int)node->children[idx - 1]->keys.size() >= minChildren())
            borrowFromPrev(node, idx);
        else if (idx != (int)node->keys.size() && (int)node->children[idx + 1]->keys.size() >= minChildren())
            borrowFromNext(node, idx);
        else {
            if (idx != (int)node->keys.size())
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    void borrowFromPrev(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx - 1];

        child->keys.insert(child->keys.begin(), node->keys[idx - 1]);
        if (!child->leaf)
            child->children.insert(child->children.begin(), sibling->children.back());

        node->keys[idx - 1] = sibling->keys.back();

        sibling->keys.pop_back();
        if (!sibling->leaf)
            sibling->children.pop_back();
    }

    void borrowFromNext(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);
        if (!child->leaf)
            child->children.push_back(sibling->children.front());

        node->keys[idx] = sibling->keys.front();

        sibling->keys.erase(sibling->keys.begin());
        if (!sibling->leaf)
            sibling->children.erase(sibling->children.begin());
    }

    void merge(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);

        for (T k : sibling->keys)
            child->keys.push_back(k);

        if (!child->leaf) {
            for (auto* ch : sibling->children)
                child->children.push_back(ch);
        }

        node->keys.erase(node->keys.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);

        delete sibling;
    }
};

// =============================
// Example usage
// =============================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BTree<int> bt(5); // order = 5 (최대 child 5개, 최대 key 4개)

    vector<int> vals = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : vals) bt.insert(v);

    cout << "Traversal after inserts: ";
    bt.traverse();

    bt.remove(6);
    cout << "After deleting 6: ";
    bt.traverse();

    bt.remove(13);
    cout << "After deleting 13 (not exist): ";
    bt.traverse();

    bt.remove(7);
    cout << "After deleting 7: ";
    bt.traverse();

    bt.remove(4);
    cout << "After deleting 4 (not exist): ";
    bt.traverse();

    bt.remove(10);
    cout << "After deleting 10: ";
    bt.traverse();

    return 0;
}
