#include <iostream>
#include <vector>

std::vector<int> oldSchoolGenerator(int start, int end, int step = 1)
{
    std::vector<int> result;
    for (int j = start; j < end; j += step) {
        result.push_back(j);
    }
    return result;
}

int main() {

    const auto res = oldSchoolGenerator(10, 45);
    
    for (auto x : res) std::cout << x << " ";
    
}