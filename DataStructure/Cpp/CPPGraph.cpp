#include "CPPGraph.h"

void CGraph::AddVertex()
{
	mAdj.emplace_back(CList<Edge>{});
	++mVertexCount;
}

void CGraph::AddEdge(size_t _u, size_t _v, const int& _w)
{
	if (_u >= mVertexCount || _v >= mVertexCount)
		throw std::out_of_range("add_edge : invalid vertex");

	mAdj[_u].push_back(_v, _w);

	if (false == mDir)
		mAdj[_v].push_back(_u, _w);
}

bool CGraph::RemoveEdge(size_t _u, size_t _v)
{
	if (_u >= mVertexCount || _v >= mVertexCount)
		return false;
	
	// vertex _u의 인접리스트를 순회
	for (CList<CGraph::Edge>::iter it = mAdj[_u].begin(); it != mAdj[_u].end(); ++it)
	{
		// 현재 iterator가 가르리큰 edge(*it)의 Dest가 _v인지 확인
		if ((*it).to == _v)
		{
			// Dest가 일치한다면 edge를 CList에서 제거
			mAdj[_u].erase(it);
			return true;
		}
	}
	return false;
}
