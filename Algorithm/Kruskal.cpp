#include "GraphInput.cpp"

struct FDisjointSet
{
    std::vector<int> parent;
    std::vector<int> rank;

    explicit FDisjointSet(int n)
        : parent(n + 1), rank(n + 1, 0)
    {
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;

        return parent[i] = find(parent[i]); // Path Compression
    }

    bool unite(int i, int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti == rootj)
            return false; // already same group(사이클 형성방지)

        // Rank가 높은 쪽을 rooti로 설정
        if(rank[rooti] < rank[rootj])
            std::swap(rooti,rootj);

        // 낮은쪽(rootj)을 높은 쪽(rooti)아래에 할당
        parent[rootj] = rooti; 
        
        // 높이가 같아졌다면 합쳐지고 높이를 1 증가
        if(rank[rooti] == rank[rootj])
            rank[rooti]++;
        
        return true;
    }

    bool NonRankUnite(int i, int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti != rootj)
        {
            parent[rooti] = rootj;
            return true;
        }

        return false;
    }
};

void Kruskal()
{
    std::sort(edges.begin(), edges.end(), [](const FEdge &a, const FEdge &b)
              {
                  return a.weight < b.weight;
              });

    FDisjointSet ds(gVertexCount);
    int mstWeight = 0;
    int edgesCount = 0;

    for(const auto& edge : edges)
    {
        if(ds.unite(edge.from, edge.to))
        {
            mstWeight += edge.weight;
            ++edgesCount;
            std::cout<<edge.from<<"-"<<edge.to<<'\n';         

            if(edgesCount == gVertexCount -1)
                break;
        }
    }
}

int main()
{
    FileInput();
    Kruskal();

    return 0;
}