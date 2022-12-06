#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main()
{
    std::ifstream input("input.txt");

    using ElfInventory = std::vector<int>;
    using Elfs         = std::vector<ElfInventory>;

    Elfs elfs;
    elfs.push_back(ElfInventory());

    std::string line;
    int         largestInventory = 0;
    int         currentInventory = 0;

    while (std::getline(input, line))
    {
        if (line.empty())
        {
            elfs.push_back(ElfInventory());
            currentInventory = 0;
        }
        else
        {
            int calories = std::stoi(line);
            elfs.back().push_back(calories);
            currentInventory += calories;
        }
        largestInventory = std::max(currentInventory, largestInventory);
    }

    std::cout << "Largest inventory " << largestInventory << std::endl;

    std::sort(elfs.begin(), elfs.end(), [](ElfInventory const& elf1, ElfInventory const& elf2) {
        return std::accumulate(elf1.begin(), elf1.end(), 0) > std::accumulate(elf2.begin(), elf2.end(), 0);
    });

    std::cout << "Sum of first three: "
              << std::accumulate(elfs[0].begin(), elfs[0].end(), 0) + std::accumulate(elfs[1].begin(), elfs[1].end(), 0)
                     + std::accumulate(elfs[2].begin(), elfs[2].end(), 0);

    return 0;
}