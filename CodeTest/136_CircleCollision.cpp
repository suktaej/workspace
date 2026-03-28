#include <iostream>

int main()
{
    int testCase;
    int x1, y1, x2, y2, r1, r2;
    
    std::cin>>testCase;
    
    while(testCase--)
    {
        std::cin>>x1>>y1>>r1>>x2>>y2>>r2;
    
        int cntLen = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        int radSum = (r1+r2)*(r1+r2);
        int radSub = (r1-r2)*(r1-r2);
        
        if(cntLen == 0)
        {
            if(r1 == r2)
                std::cout<<-1<<'\n';
            else
                std::cout<<0<<'\n';
        }
        else if(cntLen == radSum || cntLen == radSub)
            std::cout<<1<<'\n';
        else if(cntLen < radSum && cntLen > radSub)
            std::cout<<2<<'\n';
        else
            std::cout<<0<<'\n';
    }
    return 0;
}
