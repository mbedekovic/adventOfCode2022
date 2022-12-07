#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct File;

using FilePtr = std::unique_ptr<File>;

struct File
{
    std::string          name;
    size_t               size;
    File*                parent;
    std::vector<FilePtr> children;
};

File* parseCommand(File* currentNode, std::string const& command)
{
    std::string       chunk;
    std::stringstream ss(command);
    std::getline(ss, chunk, ' ');
    if (chunk == "$")
    {
        // command
        std::getline(ss, chunk, ' ');
        if (chunk == "cd")
        {
            // traverse tree
            std::getline(ss, chunk, ' ');
            if (chunk == "..")
            {
                return currentNode->parent;
            }

            auto itr = std::find_if(
                currentNode->children.begin(),
                currentNode->children.end(),
                [&chunk](FilePtr const& child) -> bool {
                    if (child == nullptr)
                    {
                        return false;
                    }

                    return (child->name == chunk);
                });
            return itr->get();
        }
    }
    else if (chunk == "dir")
    {
        std::getline(ss, chunk, ' ');  // dir name
        currentNode->children.push_back(std::make_unique<File>(File{chunk, 0, currentNode, {}}));
    }
    else
    {
        // File
        std::string fileName;
        size_t      fileSize = std::stol(chunk);
        std::getline(ss, fileName, ' ');  // file fileName
        currentNode->children.push_back(std::make_unique<File>(File{fileName, fileSize, currentNode, {}}));
    }
    return currentNode;
}

FilePtr parseFileTree(std::ifstream& input)
{
    auto        root = std::make_unique<File>(File{"/", 0, nullptr, {}});
    std::string line;
    std::getline(input, line);  // remove root from output
    File* currentNode = root.get();
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            return root;
        }
        currentNode = parseCommand(currentNode, line);
    }
    return root;
}

std::vector<size_t> sizes;
size_t              findDirsSmallerThan(File* node, size_t maxSize)
{
    if (node->children.empty())
    {
        // last node, return size
        return node->size;
    }

    size_t nodeSize = 0;
    if (node->size == 0)
    {
        // this is a directory, sum all his children
        for (auto& child : node->children)
        {
            nodeSize += findDirsSmallerThan(child.get(), maxSize);
        }
        if (nodeSize <= maxSize)
        {
            sizes.push_back(nodeSize);
        }
    }
    return nodeSize;
}

size_t smallestSize = 70000000;
size_t findClosestDir(File* node, size_t minSize)
{
    if (node->children.empty())
    {
        // last node, return size
        return node->size;
    }

    size_t nodeSize = 0;
    if (node->size == 0)
    {
        // this is a directory, sum all his children
        for (auto& child : node->children)
        {
            nodeSize += findClosestDir(child.get(), minSize);
        }

        if (nodeSize > minSize && nodeSize < smallestSize)
        {
            smallestSize = nodeSize;
        }
    }
    return nodeSize;
}

int main()
{
    std::ifstream input("input.txt");

    auto root = parseFileTree(input);

    size_t totalSize = findDirsSmallerThan(root.get(), 100000);

    size_t spaceAvailable = 70000000 - totalSize;
    size_t spaceRequired  = 30000000 - spaceAvailable;
    findClosestDir(root.get(), spaceRequired);

    std::cout << "Sum of dirs smaller than 100000: " << std::accumulate(sizes.begin(), sizes.end(), 0) << std::endl;
    std::cout << "Smallest dir to delete: " << smallestSize << std::endl;
    return 0;
}