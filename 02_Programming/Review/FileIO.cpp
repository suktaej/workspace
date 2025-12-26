#include <fstream>
#include <iostream>
#include <string>

std::string ReadFile()
{
    std::ifstream readFile;
    readFile.open("input.txt");
    // char temp[256];
    std::string str;

    if(readFile.is_open())
    {
        while(!readFile.eof())
        {
            // 1. istream getline
            // readFile.getline(temp,256);

            // 2. std::getline
            std::getline(readFile,str);
        }

        readFile.close();
        return str;
    }
}

std::string ReadLine()
{
    std::ifstream readFile("input.txt");
    std::string fullText = "";
    std::string line;

    if(readFile.is_open())
    {
        while(std::getline(readFile, line))
            fullText += line + '\n';

        readFile.close();
    }
    return fullText;
}

std::string ReadyWord()
{
    std::ifstream readFile("input.txt");
    std::string fullText = "";
    std::string word;

    if(readFile.is_open())
    {
        while (readFile >> word)
            fullText += word + ' ';
        
        readFile.close();
    }

    return fullText;
}

void WriteFile(const std::string& str)
{
    std::ofstream writeFile;
    writeFile.open("output.txt");
    char arr[16] = "InputResult\n";
    std::string line = "End\nLine";

    if(writeFile.is_open())
    {
        writeFile.write(arr, 12);
        writeFile.write(str.c_str(), str.size());
        writeFile << line;
        writeFile.close();
    }
}

int main()
{
    WriteFile(ReadLine());
    return 0;
}