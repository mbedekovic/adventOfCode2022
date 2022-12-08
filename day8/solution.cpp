#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using Forest = std::vector<std::vector<int>>;

Forest parseInput(std::ifstream& input)
{
    Forest      forest;
    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            return forest;
        }

        forest.emplace_back();
        for (auto ch : line)
        {
            forest.back().push_back(static_cast<int>(ch - '0'));
        }
    }
    return forest;
}

std::pair<bool, int> checkUp(Forest& forest, int i, int j)
{
    int visibility = 0;
    int cur        = forest[i][j];
    i--;
    while (i >= 0)
    {
        if (cur <= forest[i][j])
        {
            return {false, ++visibility};
        }
        visibility++;
        i--;
    }
    return {true, visibility};
}

std::pair<bool, int> checkDown(Forest& forest, int i, int j)
{
    int visibility = 0;
    int cur        = forest[i][j];
    i++;
    while (i < forest.size())
    {
        if (cur <= forest[i][j])
        {
            return {false, ++visibility};
        }
        visibility++;
        i++;
    }
    return {true, visibility};
}

std::pair<bool, int> checkLeft(Forest& forest, int i, int j)
{
    int visiblity = 0;
    int cur       = forest[i][j];
    j--;
    while (j >= 0)
    {
        if (cur <= forest[i][j])
        {
            return {false, ++visiblity};
        }
        j--;
        visiblity++;
    }
    return {true, visiblity};
}

std::pair<bool, int> checkRight(Forest& forest, int i, int j)
{
    int visiblity = 0;
    int cur       = forest[i][j];
    j++;
    while (j < forest.front().size())
    {
        if (cur <= forest[i][j])
        {
            return {false, ++visiblity};
        }
        visiblity++;
        j++;
    }
    return {true, visiblity};
}

int findVisibleTrees(Forest& forest)
{
    int const hight        = forest.size();
    int const width        = forest.front().size();
    int       visibleTrees = 2 * (hight + width) - 4;  // 4 corners are duplicated

    for (int i = 1; i < (hight - 1); i++)
    {
        for (int j = 1; j < (width - 1); j++)
        {
            if (checkLeft(forest, i, j).first || checkRight(forest, i, j).first || checkUp(forest, i, j).first
                || checkDown(forest, i, j).first)
            {
                visibleTrees++;
            }
        }
    }
    return visibleTrees;
}

int highestVisiblityScore(Forest& forest)
{
    int const hight        = forest.size();
    int const width        = forest.front().size();
    int       highestScore = 0;

    // This is ray tracing, isn't it?
    for (int i = 0; i < (hight); i++)
    {
        for (int j = 0; j < (width); j++)
        {
            int score = checkLeft(forest, i, j).second * checkRight(forest, i, j).second * checkUp(forest, i, j).second
                        * checkDown(forest, i, j).second;
            highestScore = std::max(score, highestScore);
        }
    }
    return highestScore;
}

int main()
{
    std::ifstream input("input.txt");

    Forest forest = parseInput(input);

    std::cout << "Total visible trees from the edge (part 1): " << findVisibleTrees(forest) << std::endl;
    std::cout << "Highest visiblity score (part 2): " << highestVisiblityScore(forest) << std::endl;

    return 0;
}