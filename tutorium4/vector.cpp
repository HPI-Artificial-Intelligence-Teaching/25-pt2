#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    numbers.push_back(6);
    numbers.push_back(7);
    numbers[0] = 2;
    
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Size: " << numbers.size() << std::endl;
    
    std::cout << "All elements: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    numbers.pop_back();
    
    return 0;
}