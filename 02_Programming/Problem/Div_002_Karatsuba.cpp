#include <vector>

void Normalize(std::vector<int>& num)
{
    num.push_back(0);

    for(int i=0;i<num.size();++i)
    {
        if(num[i] < 0)
        {
            int borrow = std::abs(num[i] + 9) / 10;

            num[i + 1] -= borrow;
            num[i] += borrow;
        }
        else
        {
            num[i+1] += num[i] /10;
            num[i] %= 10;
        }
    }

    while(num.size() > 1 && num.back()==0)
        num.pop_back();
}

std::vector<int> Multiply(const std::vector<int> &a, const std::vector<int> &b)
{
    std::vector<int> res(a.size()+b.size()+1,0);
    for(int i=0;i<a.size();++i)
        for(int j=0;j<b.size();++j)
            res[i+j] += a[i]*b[j];

    Normalize(res);
    return res;
}