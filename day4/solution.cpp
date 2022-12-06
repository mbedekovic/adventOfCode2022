#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
std::array<int, 4> split(std::string const& input)
{
    std::stringstream ss(input);
    std::string       first, second;
    std::getline(ss, first, ',');
    std::getline(ss, second, ',');

    std::array<int, 4> ranges;
    std::string        lower, upper;

    std::stringstream lowerSS(first);
    std::getline(lowerSS, lower, '-');
    std::getline(lowerSS, upper, '-');
    ranges[0] = std::stoi(lower);
    ranges[1] = std::stoi(upper);

    std::stringstream upperSS(second);
    std::getline(upperSS, lower, '-');
    std::getline(upperSS, upper, '-');
    ranges[2] = std::stoi(lower);
    ranges[3] = std::stoi(upper);

    return ranges;
}

bool isFullyContained(std::array<int, 4> const& ranges)
{
    int first_lower  = ranges[0];
    int first_upper  = ranges[1];
    int second_lower = ranges[2];
    int second_upper = ranges[3];

    // determine which is first
    if (first_lower < second_lower)
    {
        // first starts earlier
        if (second_upper <= first_upper)
        {
            // second fully contained in first
            return true;
        }
    }
    else if (second_lower < first_lower)
    {
        // second starts before first
        if (first_upper <= second_upper)
        {
            // first fully contained in second
            return true;
        }
    }
    else  // first and second start at the same position
    {
        if (second_upper <= first_upper)
        {
            // first fully contained in second
            return true;
        }

        if (first_upper <= second_upper)
        {
            return true;
        }
    }
    return false;
}

bool noOverlap(std::array<int, 4> ranges)
{
    int first_lower  = ranges[0];
    int first_upper  = ranges[1];
    int second_lower = ranges[2];
    int second_upper = ranges[3];

    // check which starts first
    if (first_lower < second_lower)
    {
        // check that first upper ends before second lower starts
        if (first_upper < second_lower)
        {
            return true;
        }
    }
    if (second_lower < first_lower)
    {
        // check that second upper ends before first lower
        if (second_upper < first_lower)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::ifstream input("input.txt");

    std::string line;
    int         sum      = 0;
    int         overlaps = 0;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            break;
        }
        auto ranges = split(line);
        if (isFullyContained(ranges))
        {
            sum++;
        }
        if (!noOverlap(ranges))
        {
            overlaps++;
        }
    }

    std::cout << "Total sum part 1: " << sum << std::endl;
    std::cout << "Total sum part 2: " << overlaps << std::endl;

    return 0;
}