#include <vector>
 
struct element
{
    int weight;
    int value;
};
 
struct problem
{
    int capacity;
    std::vector<element> elements;
};