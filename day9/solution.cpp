#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

enum class Direction : int
{
    up    = 1,
    down  = -1,
    left  = -2,
    right = 2
};

std::pair<Direction, int> parseCommand(std::string const& str)
{
    std::stringstream ss(str);
    std::string       chunk;
    std::getline(ss, chunk, ' ');
    Direction dir;
    if (chunk == "U")
    {
        dir = Direction::up;
    }
    else if (chunk == "D")
    {
        dir = Direction::down;
    }
    else if (chunk == "R")
    {
        dir = Direction::right;
    }
    else
    {
        dir = Direction::left;
    }
    std::getline(ss, chunk, ' ');
    return {dir, std::stoi(chunk)};
}

std::pair<int, int> vec(std::pair<int, int> head, std::pair<int, int> tail)
{
    return {head.first - tail.first, head.second - tail.second};
}

size_t normalize(std::pair<int, int>& v)
{
    size_t len = std::abs(v.first) + std::abs(v.second);  // manhattan distance
    v.first    = (v.first != 0) ? v.first / (std::abs(v.first)) : 0;
    v.second   = (v.second != 0) ? v.second / (std::abs(v.second)) : 0;
    return len;
}

size_t dist(std::pair<int, int> head, std::pair<int, int> tail)
{
    // calculate manhattan distance
    return std::abs(head.first - tail.first) + std::abs(head.second - tail.second);
}

bool isOrthogonal(std::pair<int, int> const& vec)
{
    return (vec.first == 0) || (vec.second == 0);
}

size_t simulate(std::ifstream& input, size_t ropeLength)
{
    std::set<std::pair<int, int>>    visited;
    std::string                      line;
    std::vector<std::pair<int, int>> rope(ropeLength, {0, 0});
    auto&                            head = rope.front();
    auto&                            tail = rope.back();
    visited.insert(tail);  // start position
    while (std::getline(input, line))
    {
        Direction dir;
        size_t    stepCnt;
        std::tie(dir, stepCnt) = parseCommand(line);
        while (stepCnt-- > 0)
        {
            // move head
            if ((dir == Direction::left) || (dir == Direction::right))
            {
                head.first += static_cast<int>(dir) / 2;
            }
            else
            {
                head.second += static_cast<int>(dir);
            }

            // simulate movements of all knots
            for (auto knot = rope.begin() + 1; knot != rope.end(); knot++)
            {
                auto   v   = vec(*(knot - 1), *knot);
                size_t len = normalize(v);
                // move next knot if required
                if ((isOrthogonal(v) && len > 1) || (!isOrthogonal(v) && len > 2))
                {
                    // move next knot in direction of normalized vector
                    knot->first += v.first;
                    knot->second += v.second;
                }
            }
            // add tail position to set
            visited.insert(tail);
        }
    }
    return visited.size();
}

int main()
{
    {
        std::ifstream input("input.txt");
        std::cout << "Tail visited count part 1: " << simulate(input, 2) << std::endl;
    }
    {
        std::ifstream input("input.txt");
        std::cout << "Tail visited count part 2: " << simulate(input, 10) << std::endl;
    }

    return 0;
}