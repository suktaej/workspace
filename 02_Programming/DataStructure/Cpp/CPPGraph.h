#include "CPPVector.h"
#include "CPPList.h"
#include "CPPQueue.h"
#include "CPPDisjointSet.h"
#include <utility>
#include <limits>
#include <algorithm>

class CGraph
{
public:
	struct Edge
	{
		size_t to;
		int weight;
		Edge() : to(std::numeric_limits<size_t>::max()), weight(0) {}
		Edge(size_t _to, int _w) : to(_to), weight(_w) {}
	};

	struct Vertex
	{
		size_t id;
		std::string name;
		float x, y;
		CList<Edge> adjacency;
	};

public:
	explicit CGraph(size_t _vertex = 0) : mVtxCnt(_vertex), mAdj(_vertex), mDir(true) {}

	~CGraph()
	{
	}

private:
	size_t mVtxCnt;
	CVector<CList<Edge>> mAdj;
	bool mDir;

public:
	void AddVertex();
	void AddVertex(int _cnt);
	void AddEdge(size_t _u, size_t _v, const int& _w);
	bool RemoveEdge(size_t _u, size_t _v);
	void SetDirection(bool value);

	void PrintGraph();
	void Dijkstra(size_t start, size_t end);
	void Prim(size_t start);
	void Kruskal();
	void DFS(size_t start);
	void DFS_Recursive(size_t start, CVector<bool>& visited);
	void DFS_Stack(size_t start);
	void BFS(size_t start);
};

inline void CGraph::AddVertex()
{
	mAdj.emplace_back(CList<Edge>{});	// 임시객체 생성
	++mVtxCnt;
}

inline void CGraph::AddVertex(int _cnt)
{
	for(int i=0;i<_cnt;++i)
	{
		mAdj.emplace_back(CList<Edge>{});	// 임시객체 생성
		++mVtxCnt;
	}
}

inline void CGraph::AddEdge(size_t src, size_t dest, const int& weight)
{
	if (src >= mVtxCnt || dest >= mVtxCnt)
		throw std::out_of_range("add_edge : invalid vertex");

	mAdj[src].push_back(dest, weight);

	if (false == mDir)
		mAdj[dest].push_back(src, weight);
}

inline bool CGraph::RemoveEdge(size_t src, size_t dest)
{
	if (src >= mVtxCnt || dest >= mVtxCnt)
		return false;
	
	// vertex Source의 인접리스트를 순회
	for (CList<CGraph::Edge>::iter it = mAdj[src].begin(); it != mAdj[src].end(); ++it)
	{
		// 현재 iterator가 가리키는 edge(*it)의 Dest를  확인
		if ((*it).to == dest)
		{
			// Dest가 일치한다면 edge를 CList에서 제거
			mAdj[src].erase(it);
			return true;
		}
	}
	return false;
}

inline void CGraph::SetDirection(bool value)
{
	mDir = value;
}

inline void CGraph::PrintGraph()
{
	for (size_t u = 0; u < mVtxCnt; ++u)
	{
		std::cout << "Vertex " << u << ": ";

		for (auto it = mAdj[u].begin(); it != mAdj[u].end(); ++it)
			std::cout << "(to: " << it->to << ", weight: " << it->weight << ") ";

		std::cout << "\n";
	}
}

inline void CGraph::Dijkstra(size_t start, size_t end)
{
	CVector<int> dist(mVtxCnt, std::numeric_limits<int>::max()); // 거리(누적 가중치)
	dist[start] = 0;

	CVector<int> prev(mVtxCnt, -1);	// 경로추적

	CPriorityQueue_Min<std::pair<int, size_t>> minHeap;	//(거리, 노드)
	minHeap.push({dist[start],start});	//start node에 거리 0을 삽입

	while (false == minHeap.empty())
	{
		//auto [curDist, u] = minHeap.top();	// 구조적 바인딩(structured binding) C++ 17
		std::pair<int, size_t> topNode = minHeap.top();
		int curDist = topNode.first;
		size_t curNode = topNode.second;

		minHeap.pop();

		if (curDist > dist[curNode])	// 이미 경로가 짧다면 무시
			continue;

		if (curNode == end)	// 도착 노드에 도달할 시 종료
			break;
		
		for (CList<CGraph::Edge>::iter it = mAdj[curNode].begin(); it != mAdj[curNode].end(); ++it)
		{
			size_t nextNode = it->to;
			int weight = it->weight;

			if (dist[curNode] != std::numeric_limits<int>::max() &&	// 현재노드의 누적가중치가 무한대가 아니고
				dist[curNode] + weight < dist[nextNode])			// 현재노드의 누적가중치에 다음노드까지의 가중치를
			{														// 더한 값이 다음노드의 누적가중치보다 작다면(최초 접근 시 무한대)
				dist[nextNode] = dist[curNode] + weight;			// 다음노드의 거리는 누적가중치 + 가중치
				prev[nextNode] = static_cast<int>(curNode);			// 이전노드에 현재노드를 저장
				minHeap.push({ dist[nextNode],nextNode });			// heap에 push
			}
		}
	}

	// 결과 출력
	if (dist[end] == std::numeric_limits<int>::max())
	{
		std::cout << "No path from " << start << " to " << end << std::endl;
		return;
	}

	std::cout << "Shortest distance from " << start << " to " << end << " = " << dist[end] << std::endl;

	// 경로 복원
	CVector<size_t> path;
	for (int v = static_cast<int>(end); v != -1; v = prev[v])
		path.push_back(v);

	std::cout << "Path: ";
	for (int i = static_cast<int>(path.size()) - 1; i >= 0; --i)
		std::cout << path[i] << (i > 0 ? " -> " : "\n");
}

inline void CGraph::Prim(size_t start)
{
	CVector<bool> visited(mVtxCnt, false);
	CPriorityQueue_Min<std::pair<int, std::pair<size_t, size_t>>> edgeHeap; // {weight, {src, dest}}

	visited[start] = true;

	for (auto it = mAdj[start].begin(); it != mAdj[start].end(); ++it)
		edgeHeap.push({ it->weight,{start,it->to} });

	while (false == edgeHeap.empty())
	{
		auto top = edgeHeap.top();
		edgeHeap.pop();

		int weight = top.first;
		size_t src = top.second.first;
		size_t dest = top.second.second;

		if (visited[dest])
			continue;

		visited[dest] = true;
		std::cout << "(" << src << " -> " << dest << " weight: " << weight << ")\n";

		for (auto it = mAdj[dest].begin();it != mAdj[dest].end(); ++it)
		{
			if (false == visited[it->to])
				edgeHeap.push({ it->weight,{dest,it->to} });
		}
	}
}

inline void CGraph::Kruskal()
{
	struct EdgeInfo
	{
		size_t src;
		size_t dest;
		int weight;
	};

	if (mDir)
	{
		std::cout << "Kruskal Algorithm requires an undirected graph.\n";
		return;
	}

	CVector<EdgeInfo> edges;

	for (size_t srcIdx = 0; srcIdx < mVtxCnt; ++srcIdx)
	{
		for (auto it = mAdj[srcIdx].begin(); it != mAdj[srcIdx].end();++it)
		{
			size_t destIdx = it->to;
			int edgeWeight = it->weight;

			if (srcIdx > destIdx)	// 방향성이 없으므로
				continue;

			edges.push_back({ srcIdx, destIdx, edgeWeight });
		}
	}

	std::sort(&edges[0], &edges[0] + edges.size(),
		[](const EdgeInfo& f, const EdgeInfo& s)
		{
			return f.weight < s.weight;
		});

	CDisjointSet ds(mVtxCnt);

	int totalWeight = 0;

	for (size_t i = 0; i < edges.size(); ++i)
	{
		const auto& edge = edges[i];

		if (ds.Union(edge.src, edge.dest))
		{
			totalWeight += edge.weight;
			std::cout << "Edge (" << edge.src << " - " << edge.dest << ") : " << edge.weight << "\n";
		}
	}
	std::cout << "Total Weight = " << totalWeight << "\n";
}

inline void CGraph::DFS(size_t start)
{
	CVector<bool> visited(mVtxCnt, false);
	DFS_Recursive(start, visited);
}

inline void CGraph::DFS_Recursive(size_t node, CVector<bool>& visited)
{
	visited[node] = true;
	std::cout << node << ' ';

	for (CList<CGraph::Edge>::iter it = mAdj[node].begin(); it != mAdj[node].end(); ++it)
	{
		size_t nextNode = it->to;
		if (false == visited[nextNode])
			DFS_Recursive(nextNode, visited);
	}
}

inline void CGraph::DFS_Stack(size_t start)
{
	CVector<bool> visited(mVtxCnt, false);
	CVector<size_t> stack;
	stack.push_back(start);

	while (false == stack.empty())
	{
		size_t node = stack.back();
		stack.pop_back();

		if (false == visited[node])
		{
			visited[node] = true;
			std::cout << node << ' ';

			//for(auto it = mAdj[node].rbegin(); it != mAdj[node].rend();++i)
			for (auto it = mAdj[node].end(); it != mAdj[node].begin();)
			{
				--it;						 //end()는 nullptr을 가르키므로 내부에서 선행연산 후 진행
				size_t nextNode = it->to;

				if(!visited[nextNode])
					stack.push_back(nextNode);
			}
		}
	}
}

inline void CGraph::BFS(size_t start)
{
	CVector<bool> visited(mVtxCnt, false);
	CCircuitQueue<size_t> queue(mVtxCnt);

	visited[start] = true;
	queue.enqueue(start);

	while (false == queue.empty())
	{
		size_t node = queue.front();
		queue.dequeue();

		std::cout << node << " ";

		for (auto it = mAdj[node].begin(); it != mAdj[node].end(); ++it)
		{
			size_t nextNode = it->to;
			if (false == visited[nextNode])
			{
				visited[nextNode] = true;
				queue.enqueue(nextNode);
			}
		}
	}
}