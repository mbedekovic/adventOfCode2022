#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

constexpr size_t step      = 4;
constexpr size_t stack_cnt = 9;
constexpr size_t width     = step * stack_cnt - 1;

std::array<std::deque<char>, stack_cnt> parseInitialStack(std::vector<std::string> input)
{
    std::array<std::deque<char>, stack_cnt> stacks;
    for (auto const& line : input)
    {
        size_t idx = 0;
        for (size_t i = 1; i < width; i += step)
        {
            if (line[i] != ' ')
            {
                stacks[idx].push_back(line[i]);
            }
            idx++;
        }
    }
    return stacks;
}

constexpr size_t                command_cnt = 3;
std::array<size_t, command_cnt> parseCommand(std::string const& command)
{
    std::array<size_t, command_cnt> values;
    std::stringstream               ss(command);
    std::string                     chunk;
    std::getline(ss, chunk, ' ');  // ignore keyword 'move'
    std::getline(ss, chunk, ' ');
    values[0] = std::stoi(chunk);
    std::getline(ss, chunk, ' ');  // ignore keyword 'from'
    std::getline(ss, chunk, ' ');
    values[1] = std::stoi(chunk) - 1;
    std::getline(ss, chunk, ' ');  // ignore keyword 'to'
    std::getline(ss, chunk, ' ');
    values[2] = std::stoi(chunk) - 1;
    return values;
}

void executeCommand(std::array<std::deque<char>, stack_cnt>& stacks, std::array<size_t, 3> command, bool reverse = true)
{
    size_t pop_cnt  = command[0];
    size_t from_idx = command[1];
    size_t to_idx   = command[2];

    if (pop_cnt > stacks[from_idx].size())
    {
        pop_cnt = stacks[from_idx].size();
    }

    std::vector<char> containers(stacks[from_idx].begin(), stacks[from_idx].begin() + pop_cnt);
    if (!reverse)
    {
        stacks[to_idx].insert(stacks[to_idx].begin(), containers.begin(), containers.end());
    }
    else
    {
        stacks[to_idx].insert(stacks[to_idx].begin(), containers.rbegin(), containers.rend());
    }
    stacks[from_idx].erase(stacks[from_idx].begin(), stacks[from_idx].begin() + pop_cnt);
}

int main()
{
    std::ifstream input("input.txt");

    std::string                             line;
    bool                                    parsingInitialStack = true;
    std::vector<std::string>                inputStack;
    std::array<std::deque<char>, stack_cnt> stacks;
    std::array<std::deque<char>, stack_cnt> stacks_part2;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            parsingInitialStack = false;
            // remove last parsed line from input (numbers)
            inputStack.pop_back();
            stacks       = parseInitialStack(inputStack);
            stacks_part2 = stacks;
        }
        else
        {
            if (parsingInitialStack)
            {
                inputStack.push_back(std::move(line));
            }
            else
            {
                // parse command, execute command
                auto command = parseCommand(line);
                executeCommand(stacks, command, true);
                executeCommand(stacks_part2, command, false);
            }
        }
    }

    // print out the tops of stacks
    std::cout << "Tops of stacks part 1 : ";
    for (auto const stack : stacks)
    {
        if (!stack.empty())
        {
            std::cout << stack.front();
        }
    }
    std::cout << std::endl;

    std::cout << "Tops of stacks part 2 : ";
    for (auto const stack : stacks_part2)
    {
        if (!stack.empty())
        {
            std::cout << stack.front();
        }
    }
    std::cout << std::endl;

    return 0;
}