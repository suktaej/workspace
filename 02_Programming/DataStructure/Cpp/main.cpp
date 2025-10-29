#include "CPPVector.h"
#include "CPPList.h"
#include "CPPGraph.h"
#include "CPPHashMap.h"
#include "CPPMap.h"
#include "CPPTrie.h"

void VectorTest();
void ListTest();
void PrintList(const CList<int>& list);
void GraphTest();
void TreeTest();
void AVLTreeTest();
void MapTest();
void HashTest();
void TrieTest();

int main()
{
	//HashTest();
	TrieTest();
	return 0;
}

void VectorTest()
{
	CVector<int>* vec = new CVector<int>;
	vec->push_back(10);
	vec->emplace_back(20);
	vec->pop_back();
	vec->push_back(30);
	vec->push_back(40);
	vec->push_back(50);
	vec->insert(1, 20);
	
	std::cout << vec->at(3) << std::endl;
	std::cout << vec->back() << std::endl;
	std::cout << vec->front() << std::endl;

	vec->PrintArray();

	delete vec;
}

void ListTest()
{
	CList<int>* lst = new CList<int>;

	lst->push_back(10);
	lst->push_back(20);
	lst->push_back(30);
	lst->pop_back();

	PrintList(*lst);

	CList<int>::iter it = lst->begin();
	++it;
	auto inserted_it = lst->insert(it,15);
	std::cout<< *it << " " << *inserted_it << std::endl;
	PrintList(*lst);
	
	lst->push_back(35);
	lst->erase(inserted_it);

	PrintList(*lst);

	delete lst;
}

void PrintList(const CList<int>& list)
{
	if (list.empty())
		std::cout << "List is empty.\n";
	else
	{
		for (CList<int>::iter it = list.begin(); it != list.end(); ++it)
			std::cout << *it << " ";

		std::cout << "nullptr\n";
	}
}

void GraphTest()
{
	CGraph* grp = new CGraph(5);

	grp->AddEdge(0, 1, 10);
	grp->AddEdge(0,2,20);
	grp->AddEdge(0,3,50);
	grp->AddEdge(1,2,60);
	grp->AddEdge(1,4,20);
	grp->AddEdge(2,3,20);
	grp->AddEdge(2,4,10);
	grp->AddEdge(3,4,50);
	grp->AddEdge(4,1,20);
	grp->AddEdge(3,0,60);

	// grp->Dijkstra(0, 4);
	grp->Kruskal();
}

void TreeTest()
{
	CBinarySearchTree<int>* bt = new CBinarySearchTree<int>;
	
	bt->insert(10);
	bt->insert(20);
	bt->insert(50);
	bt->insert(100);
	bt->insert(60);
	bt->insert(30);
	bt->insert(70);
	bt->insert(40);
	bt->insert(90);
	bt->remove(100);

	std::cout<<"PreOrder: ";
	bt->preorder();
	std::cout<<"InOrder: ";   
	bt->inorder();
	std::cout<<"PostOrder: "; 
	bt->postorder();
}

void AVLTreeTest()
{
	CAVLTree<int>* bt = new CAVLTree<int>;
	
	bt->insert(10);
	bt->insert(20);
	bt->insert(50);
	bt->insert(100);
	bt->insert(60);
	bt->insert(30);
	bt->insert(70);
	bt->insert(40);
	bt->insert(90);
	bt->remove(100);

	std::cout<<"PreOrder: ";
	bt->preorder();
	std::cout<<"InOrder: ";   
	bt->inorder();
	std::cout<<"PostOrder: "; 
	bt->postorder();
}

void MapTest()
{
	CMap<int, std::string> myMap;
	myMap.insert(10, "apple");
	myMap.insert(5, "banana");
	myMap.insert(20, "cherry");

	if (auto v = myMap.find(20))
		std::cout << *v << std::endl; // banana

	std::string ex = myMap.contains(10) ? "eixst" : "not exist";
	std::cout << ex <<std::endl;

	myMap.remove(10);
	ex = myMap.contains(10) ? "eixst" : "not exist";
	std::cout << ex <<std::endl;

	for (auto it = myMap.begin(); it != myMap.end(); ++it)
		std::cout << it->key << " : " << it->value << std::endl;
}

void HashTest()
{
	CHashMap<int, std::string> map;

    map.insert(10, "Ten");
    map.insert(20, "Twenty");
    map.insert(30, "Thirty");
	map.insert(40, "Forty");

    // 기존 키 업데이트
    map.insert(20, "Twenty Updated");

    // find 확인
    if (auto val = map.find(20))
        std::cout << "Key 20 -> " << *val << "\n";

    // contains 확인
    std::cout << "Contains 10 : " << (map.contains(10) ? "exist" : "does not exist") << "\n";
    std::cout << "Contains 50 : " << (map.contains(50) ? "exist" : "does not exist") << "\n";

    // operator[]
    map[40] = "Forty";
    std::cout << "Key 40 -> " << map[40] << "\n";

    // remove 확인
    map.remove(10);
    std::cout << "Contains 10 after remove : " << (map.contains(10)? "exist" : "does not exist") << "\n";

    // Rehash 테스트
    for (int i = 0; i < 100; ++i)
        map.insert(i, "Num" + std::to_string(i));

    std::cout << "Size after inserts: " << map.size() << "\n";

	// begin() ~ end()를 사용해서 전체 요소 순회
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		std::cout << "Key: " << it->first << ", Value: " << it->second << "\n";
	}

	std::cout << "\nTesting reverse iteration:\n";

	// end()에서 하나 뒤로 이동해서 마지막 요소부터 역순 순회
	auto it = map.end();
	while (it != map.begin())
	{
		--it;
		std::cout << "Key: " << it->first << ", Value: " << it->second << "\n";
	}
}

void TrieTest()
{
	CTrie trie;
	trie.insert("apple");
	trie.insert("app");
	trie.insert("banana");
	trie.insert("band");
	trie.insert("bat");

	std::cout << std::boolalpha;
	std::cout << "Search 'app': " << trie.search("app") << std::endl;        // true
	std::cout << "Search 'appl': " << trie.search("appl") << std::endl;      // false
	std::cout << "StartsWith 'ban': " << trie.StartsWith("ban") << std::endl; // true
	std::cout << "\nAll words in trie:\n";
	trie.PrintAll();
}
