#include <iostream>
#include <array>
#include <algorithm>

int main() {
    std::array<int, 5> numbers = {3, 1, 4, 1, 5};
    
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Size: " << numbers.size() << std::endl;
    
    std::sort(numbers.begin(), numbers.end());
    
    std::cout << "Sorted: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}