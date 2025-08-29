#include "CPPGraph.h"
#include "CPPQueue.h"
#include <vector>
#include <limits>

void CGraph::AddVertex()
{
	mAdj.emplace_back(CList<Edge>{});	// 임시객체 생성
	++mVtxCnt;
}

void CGraph::AddEdge(size_t src, size_t dest, const int& weight)
{
	if (src >= mVtxCnt || dest >= mVtxCnt)
		throw std::out_of_range("add_edge : invalid vertex");

	mAdj[src].push_back(dest, weight);

	if (false == mDir)
		mAdj[dest].push_back(src, weight);
}

bool CGraph::RemoveEdge(size_t src, size_t dest)
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

void CGraph::SetDirection(bool value)
{
	mDir = value;
}

void CGraph::PrintGraph()
{
	for (size_t u = 0; u < mVtxCnt; ++u)
	{
		std::cout << "Vertex " << u << ": ";

		for (auto it = mAdj[u].begin(); it != mAdj[u].end(); ++it)
			std::cout << "(to: " << it->to << ", weight: " << it->weight << ") ";

		std::cout << "\n";
	}
}

void CGraph::Dijkstra(size_t start, size_t end)
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

