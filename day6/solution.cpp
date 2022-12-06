#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

size_t startOfMessage(std::string const& str, size_t cnt)
{
    auto   itrBegin = str.begin();
    auto   itrEnd   = str.begin() + cnt;
    size_t charCnt  = cnt;

    while (itrEnd < str.end())
    {
        std::set<char> charSet(itrBegin, itrEnd);
        if (charSet.size() == cnt)
        {
            return charCnt;
        }
        itrBegin++;
        itrEnd++;
        charCnt++;
    }
    return charCnt;
}

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    if (std::getline(input, line))
    {
        if (line.empty())
        {
            return 0;
        }

        std::cout << "Start of packet chars: " << startOfMessage(line, 4) << std::endl;
        std::cout << "Start of message chars: " << startOfMessage(line, 14) << std::endl;
    }

    return 0;
}