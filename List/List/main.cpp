#include "List.h"
#include <iostream>
#include <algorithm>

int main() {
    int array[] = {-6, 5, 3, 0, 8, -4, 1, 2 };
    List<int> list(array, 8);

    std::cout << "List: " << list << "\n";
    std::cout << "Size: " << list.size() << "\n";

    std::cout << "Min value: " << list.min() << "\n";
    std::cout << "Max value: " << list.max() << "\n";

    list.sort();
    std::cout << "Sorted list: " << list << "\n";

    list.deleteFromHead();
    list.deleteFromTail();
    std::cout << "List after delete head and tail: " << list << "\n";

    list.addToHead(10);
    list.addToTail(-10);
    std::cout << "List after add values: " << list << "\n";

    auto it = list.findValue(3);
    if (it != list.end()) {
        std::cout << "Value 3 found" << "\n";
    }
    else {
        std::cout << "Value 3 not found" << "\n";
    }

    list.deleteByKey(5);
    std::cout << "After delete value 5: " << list << "\n";

    list.clear();
    std::cout << "List after clear: ";
    std::cout << list << "\n";

    return 0;
}