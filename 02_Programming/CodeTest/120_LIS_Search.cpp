#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int n;
std::vector<int> arr;

int binarySearch(const std::vector<int>& vec, int value)
{
    int left = 0;
    int right = vec.size()-1;
    int res;
    
    while(left <= right)
    {
        int mid = left+(right-left)/2;
        
        // if(vec[mid]==value)
        //     return mid;
        // else if(vec[mid]<value)
        //     left = mid + 1;
        // else
            // right = mid - 1;
        
        if(vec[mid]>=value)
        {
            res = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    
    return res;
}

void solve()
{
    std::vector<int> lis;
    int target = 0;
    
    lis.push_back(arr[0]);
    
    for(int i=0;i<n;++i)
    {
        if(lis.back() < arr[i])
            lis.push_back(arr[i]);
        else
            // lis[binarySearch(lis,arr[i])] = arr[i];
        {
            auto it = std::lower_bound(lis.begin(),lis.end(),arr[i]);
            *it = arr[i];
        }
    }
    
    std::cout<<lis.size();
}

int main()
{
    std::cin>>n;
	arr.resize(n);
	for(int i=0; i<n; ++i)
		std::cin>>arr[i];

    solve();
	return 0;
}