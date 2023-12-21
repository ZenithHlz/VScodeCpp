#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> numbers = {1, 2, 3};

    // Sorting the numbers in ascending order before generating permutations
    std::sort(numbers.begin(), numbers.end());

    // Generating and printing permutations
    do
    {
        for (const auto &number : numbers)
        {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    return 0;
}
