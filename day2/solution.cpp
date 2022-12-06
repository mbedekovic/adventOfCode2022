#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

std::pair<std::string, std::string> split(std::string const& s, std::string delimiter)
{
    std::pair<std::string, std::string> result;
    size_t                              pos_start = 0, pos_end, delimiter_len = delimiter.length();
    pos_end       = s.find(delimiter, pos_start);
    result.first  = s.substr(pos_start, pos_end - pos_start);
    pos_start     = pos_end + delimiter_len;
    result.second = s.substr(pos_start);

    return result;
}

static std::map<std::string, std::string> const encryption =
    {{"A", "Rock"}, {"B", "Paper"}, {"C", "Scissors"}, {"X", "Rock"}, {"Y", "Paper"}, {"Z", "Scissors"}};

static std::map<std::string, std::string> const encryption_part2 =
    {{"A", "Rock"}, {"B", "Paper"}, {"C", "Scissors"}, {"X", "Lose"}, {"Y", "Draw"}, {"Z", "Win"}};

int main()
{
    std::ifstream input("input.txt");

    int         myTotalScore      = 0;
    int         myTotalScorePart2 = 0;
    std::string line;
    while (std::getline(input, line))
    {
        if (!line.empty())
        {
            std::string opponentCode, meCode;
            std::tie(opponentCode, meCode) = split(line, " ");

            std::string const& opponent = encryption.at(opponentCode);
            std::string const& me       = encryption.at(meCode);
            std::string const& outcome  = encryption_part2.at(meCode);

            int myScore = 0;
            if (opponent == "Rock")
            {
                if (me == "Rock")
                {
                    myScore += 3 + 1;
                }
                else if (me == "Paper")
                {
                    myScore += 6 + 2;
                }
                else
                {
                    myScore += 0 + 3;
                }
            }
            else if (opponent == "Paper")
            {
                if (me == "Rock")
                {
                    myScore += 0 + 1;
                }
                else if (me == "Paper")
                {
                    myScore += 3 + 2;
                }
                else
                {
                    myScore += 6 + 3;
                }
            }
            else  // scissors
            {
                if (me == "Rock")
                {
                    myScore += 6 + 1;
                }
                else if (me == "Paper")
                {
                    myScore += 0 + 2;
                }
                else
                {
                    myScore += 3 + 3;
                }
            }
            myTotalScore += myScore;

            myScore = 0;
            if (opponent == "Rock")
            {
                if (outcome == "Draw")
                {
                    myScore += 3 + 1;
                }
                else if (outcome == "Win")
                {
                    myScore += 6 + 2;
                }
                else  // Lose
                {
                    myScore += 0 + 3;
                }
            }
            else if (opponent == "Paper")
            {
                if (outcome == "Lose")
                {
                    myScore += 0 + 1;
                }
                else if (outcome == "Draw")
                {
                    myScore += 3 + 2;
                }
                else  // win
                {
                    myScore += 6 + 3;
                }
            }
            else  // scissors
            {
                if (outcome == "Win")
                {
                    myScore += 6 + 1;
                }
                else if (outcome == "Lose")
                {
                    myScore += 0 + 2;
                }
                else  // draw
                {
                    myScore += 3 + 3;
                }
            }
            myTotalScorePart2 += myScore;
        }
    }

    std::cout << "Total score Part 1" << myTotalScore << std::endl;
    std::cout << "Total score Part 2 " << myTotalScorePart2 << std::endl;

    return 0;
}