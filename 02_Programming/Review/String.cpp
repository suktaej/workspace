#include <iostream>
#include <string>   // std::string
#include <cstring>  // str function
#include <sstream>  // for string stream
#include <iomanip>  // setprecision, setw
#include <vector>

void StringToken(char* str)
{
    char* token;
    char* context = NULL;

#if defined(_MSC_VER)
    token = strtok_s(str," ",&context);
#elif defined(__GNUC__)
    token = strtok_r(str," ",&context);
#endif
    if(NULL!=token)
        std::cout<<"token: "<<token<<" context: "<<context<<std::endl;
}

void SwapChar(const char* str)
{
    std::string str1 = str;    // operator
    std::string str2(str);     // constructor 

    // data() : string의 시작 주소를 반환(char* type) C++17
    // C++14에서는 return 'const char*'
    StringToken(str1.data());
    
    // c_str() : string to char
    // const char*를 반환하므로 strtok 사용불가
    const char* ch1 = str2.c_str();  

    std::vector<char> vec1(str2.begin(),str2.end());
    vec1.push_back('\0');  // 문자열 끝 삽입

    // data() : vector의 시작 주소를 반환(char* type)
    StringToken(vec1.data());

    // assign() : 기존 vector 내부를 비우고 overwrite
    vec1.assign(str2.begin(),str2.end());
    vec1.push_back('\0');

    // char 삽입(문자열 시작주소, 문자열 끝주소)
    vec1.assign(str, str+strlen(str));
    vec1.push_back('\0');

    // loop(string)
    vec1.clear();
    vec1.shrink_to_fit();   
    // std::vector<char>(vec1).swap(vec1);
    // copy constructor 방식
    // Temporary vector를 생성하여 원본과 swap
    // 문장종료(;)시 임시벡터 소멸
    
    for(char c : str2)
        vec1.push_back(c);
    
    vec1.push_back('\0');

    // loop(char)
    vec1.clear();
    vec1.shrink_to_fit();

    int charCnt = 0;
    while ('\0' != ch1[charCnt])
        vec1.push_back(ch1[charCnt++]);
    
    vec1.push_back('\0');
}

void StringStream(std::string str)
{
    // 형변환
    std::string strnum = "100";
    int num = std::stoi(strnum);
    std::cout<<"int num: "<<num<<"\n";
    
    num = atoi(strnum.c_str());
    std::cout<<"int num: "<<num<<"\n";

    strnum = std::to_string(num);
    std::cout<<"string num: "<<strnum<<"\n";
    
    // istringstream : 자료형 변환 가능
    std::string intstr = "10 20 30 40 50";
    std::istringstream iss(intstr);

    while(iss >> num)
        std::cout<<num<<" ";
    
    std::cout<<std::endl;

    // ostringstream : 여러 자료형 복합 출력
    // C++ 20 부터 std::format 지원
    double pi = 3.141592;
    int digit = 3;
    int fixedPoint = 2;
    int n = 4;

    std::ostringstream oss;

    oss << "Result_file_"
    << std::setfill('0') << std::setw(digit) << n   // 자리수(digit), 빈 영역 0으로 채우기
    <<"_PI_"
    << std::fixed << std::setprecision(fixedPoint) << pi     // 소수점 고정
    <<".txt";

    std::string fileName = oss.str();
    std::cout<<fileName<<"\n";

    // istringstream, ostringstream 기능 복합
    std::stringstream ss(str);
    std::string word;

    while(ss >> word)
        std::cout<<word<<" ";
    
    std::cout<<std::endl;
}

int main()
{
    const char* ch1 = "apple banana orange";
    std::string str1 = ch1;

    SwapChar(ch1);
    StringStream(str1);
    
    std::cout<<"Input for str2:";
    std::string str2;
    // string용 (공백 포함, Enter까지 입력)
    std::getline(std::cin, str2);
    std::cout<<str2<<"\n";

    std::cout<<"Input for str3:";
    char ch2[100];
    // char용 (공백포함, Enter까지 입력)
    std::cin.getline(ch2,sizeof(ch2));
    std::cout<<ch2<<"\n";

    const char* ch3 = "10 20";
    int num1, num2;
    sscanf(ch3,"%d %d",&num1, &num2);

    return 0;
}