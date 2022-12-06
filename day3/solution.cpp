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

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            break;
        }

        std::set<char>    firstCompartment(line.begin(), line.begin() + (line.size() / 2));
        std::set<char>    secondCompartment(line.begin() + (line.size() / 2), line.end());
        std::vector<char> intersection;
        std::set_intersection(
            firstCompartment.begin(),
            firstCompartment.end(),
            secondCompartment.begin(),
            secondCompartment.end(),
            std::back_inserter(intersection));

        for (char c : intersection)
        {
            sum += calc(c);
        }
    }

    std::cout << "Total sum part 1: " << sum << std::endl;

    return 0;
}