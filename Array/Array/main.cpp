#include <iostream> 
#include <conio.h> 
#include "Array.h" 

int main() {

    int n;
    std::cout << "Enter number of array values: ";
    std::cin >> n;
    Array arr(n);

    std::cout << "Enter array values:\n";
    arr.input();
    std::cout << "Array: ";
    arr.output();

    Array arr1(arr);
    std::cout << "Copied array: ";
    arr1.output();

    arr.sort();
    std::cout << "Sorted array: ";
    arr.output();

    int valueInsert;
    std::cout << "Value you want to add: ";
    std::cin >> valueInsert;
    int indexInsert;
    std::cout << "Index by which to add the value: ";
    std::cin >> indexInsert;
    arr.insertByIndex(indexInsert, valueInsert);
    std::cout << "Array after insert: ";
    arr.output();

    int valueToFind;
    std::cout << "Value you want to find: ";
    std::cin >> valueToFind;
    int index = arr.findValue(valueToFind);

    if (index != -1) {
        std::cout << "Value " << valueToFind << " found on the index: " << index << '\n';
    }
    else {
        std::cout << "Value " << valueToFind << " not found\n";
    }

    int valueToDelete;
    std::cout << "Index of value you want to delete: ";
    std::cin >> valueToDelete;
    arr.deleteByIndex(valueToDelete);
    std::cout << "Array after delete value: ";
    arr.output();

    int value;
    std::cout << "Value you want to delete: ";
    std::cin >> value;
    arr.deleteByValue(value);
    std::cout << "Array after delete value: ";
    arr.output();

    int allValue;
    std::cout << "Value you want to delete all occurrences of: ";
    std::cin >> allValue;
    arr.deleteAll(allValue);
    std::cout << "Array after delete all occurrences: ";
    arr.output();

    std::cout << "Max value: " << arr.max() << '\n';
    std::cout << "Min value: " << arr.min() << '\n';

    std::cout << "Compare arrays: ";
    if (arr != arr1) {
        std::cout << "Arrays are not equal\n";
    }
    else {
        std::cout << "Arrays are equal\n";
    }

    std::cout << "Array size: " << arr.size() << '\n';

    auto first = arr.begin();
    auto last = arr.end();
    int valueIterator;

    std::cout << "Value you want to add before the iterator: ";
    std::cin >> valueIterator;

    int iterator;
    std::cout << "Iterator: ";
    std::cin >> iterator;

    first += iterator;
    arr.insertBefore(first, valueIterator);
    arr.output();

    int iterator1, iterator2;

    std::cout << "Start index for delete range: ";
    std::cin >> iterator1;

    std::cout << "End index to delete range: ";
    std::cin >> iterator2;

    first = arr.begin() + iterator1;
    last = arr.begin() + iterator2;

    std::cout << "Delete range by iterators:\n";
    arr.deleteRange(first, last);
    arr.output();

    return 0;
}