#include <iostream>
#include <functional>

std::function<int()> createCounter() {
    int count = 0;
    
    // capture by value
    auto counterByValue = [count]() mutable -> int {
        return ++count;  // Modifies the copy
    };
    
    // capture by reference
    auto counterByRef = [&count]() -> int {
        return ++count;  // modifies original (potetially unsafe)
    };
    
    // return the closure that captures by value (SAFE)
    return counterByValue;
    // returning counterByRef would be undefined behavior
}

std::function<void()> demonstrateCaptures() {
    int x = 10;
    int y = 20;
    
    auto closure = [x, &y](){ // x by value, y by reference
        std::cout << "x (by value): " << x << std::endl;
        std::cout << "y (by reference): " << y << std::endl;
        // x++; // error: x is const by default
        y++; // modifies original y
    };
    
    x = 100; // does not affect x in closure
    y = 200; // does affect y in closure
    
    return closure;
}

int main() {
    // capture by value
    auto counter = createCounter();
    std::cout << "Counter: " << counter() << std::endl; // 1
    std::cout << "Counter: " << counter() << std::endl; // 2
    
    // capture both by reference and by value
    auto demo = demonstrateCaptures();
    demo(); // should print x: 10, y: 200
    
    // capture everything
    int a = 5, b = 10;
    auto captureAll = [=]() { // capture all by value
        std::cout << "a=" << a << ", b=" << b << std::endl;
    };
    
    auto captureAllByRef = [&]() { // capture all by reference
        std::cout << "a=" << a << ", b=" << b << std::endl;
        a++; b++; // modifies originals
    };
    
    captureAll();       // a=5, b=10
    captureAllByRef();  // a=5, b=10, then increments them
    captureAllByRef();  // a=6, b=11
    
    return 0;
}