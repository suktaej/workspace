#include "CPPHashMap.h"

struct TrieNode
{
	bool bEnd;	// 단어의 끝
	CHashMap<char, TrieNode*> children;

	TrieNode()
		: bEnd(false) { }
};

class CTrie
{
private:
	TrieNode* root;

public:
	CTrie()
	{
		root = new TrieNode;
	}
	~CTrie()
	{
		delete root;
	}

public:
	void insert(const std::string& word)
	{
		TrieNode* node = root;

		for (char ch : word)
		{
			// 삽입할 단어가 children의 마지막일 경우(존재하지 않을 경우) Node를 추가
			if (node->children.iter_find(ch) == node->children.end())
				node->children[ch] = new TrieNode();

			node = node->children[ch];
		}

		node->bEnd = true;
	}

	bool search(const std::string& word)
	{
		TrieNode* node = root;

		for (char ch : word)
		{
			if (node->children.iter_find(ch) == node->children.end())
				return false;

			node = node->children[ch];
		}

		return node->bEnd;
	}
	
	// 접두사 존재여부 탐색
	bool StartsWith(const std::string& prefix)
	{
		TrieNode* node = root;

		for (char ch : prefix)
		{
			if (node->children.iter_find(ch) == node->children.end())
				return false;

			node = node->children[ch];
		}

		return true;
	}

	// 재귀적으로 모든 단어 출력 
	void PrintAll()
	{
		std::string word;
		PrintAllRecursive(root, word);
	}

private:
	void PrintAllRecursive(TrieNode* node, std::string& current)
	{
		if (node->bEnd)
			std::cout << current << std::endl;

		for (auto& [ch, next] : node->children)
		{
			current.push_back(ch);
			PrintAllRecursive(next, current);
			current.pop_back();
		}
	}
};