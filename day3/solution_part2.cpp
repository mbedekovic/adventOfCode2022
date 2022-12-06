#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <vector>

size_t calc(char c)
{
    if (isupper(c))
    {
        size_t priority = static_cast<size_t>(c - 'A') + 27;
        return priority;
    }
    else
    {
        size_t priority = static_cast<size_t>(c - 'a') + 1;
        return priority;
    }
}

int main()
{
    std::ifstream input("input.txt");

    size_t sum = 0;

    std::string elf1, elf2, elf3;
    while (true)
    {
        if (!std::getline(input, elf1) || elf1.empty())
            break;
        if (!std::getline(input, elf2) || elf1.empty())
            break;
        if (!std::getline(input, elf3) || elf1.empty())
            break;

        std::set<char> elf1Set(elf1.begin(), elf1.end());
        std::set<char> elf2Set(elf2.begin(), elf2.end());
        std::set<char> elf3Set(elf3.begin(), elf3.end());
        std::set<char> intersection;
        std::set_intersection(
            elf1Set.begin(),
            elf1Set.end(),
            elf2Set.begin(),
            elf2Set.end(),
            std::inserter(intersection, intersection.end()));

        size_t result;
        std::set_intersection(intersection.begin(), intersection.end(), elf3Set.begin(), elf3Set.end(), &result);

        sum += calc(result);
    }

    std::cout << "Total sum part 2: " << sum << std::endl;

    return 0;
}