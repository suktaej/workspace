#include "CPPVector.h"
#include "CPPList.h"
#include "CPPGraph.h"
#include "CPPTree.h"

void VectorTest();
void ListTest();
void PrintList(const CList<int>& list);
void GraphTest();
void TreeTest();
void AVLTreeTest();

int main()
{
	// AVLTreeTest();
	GraphTest();
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