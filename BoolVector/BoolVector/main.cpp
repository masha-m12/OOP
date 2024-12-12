#include "BoolVector.h" 
#include <iostream> 
#include <conio.h> 

int main() {

    const char* array1 = "11101000";
    BoolVector bv1(array1);
    std::cout << "BoolVector1: " << bv1 << "\n";

    bv1.setBit(3, true);
    std::cout << "BoolVector1 after set bit 3 -> true: " << bv1 << "\n";

    bv1.inversionBit(7);
    std::cout << "BoolVector1 after inversion bit 7: " << bv1 << "\n";

    bv1.setBits(2, 4, false);
    std::cout << "BoolVector1 after set bits 2-4 -> false: " << bv1 << "\n";

    std::cout << "Weight BoolVector1: " << bv1.weight() << "\n";

    BoolVector bv2(8);
    bv2.setAll(true);
    std::cout << "BoolVector2: " << bv2 << "\n";

    BoolVector andResult = bv1 & bv2;
    std::cout << "bv1&bv2 result: " << andResult << "\n";

    BoolVector orResult = bv1 | bv2;
    std::cout << "bv1|bv2 result: " << orResult << "\n";

    BoolVector xorResult = bv1 ^ bv2;
    std::cout << "bv1^bv2 result: " << xorResult << "\n";

    BoolVector leftShift = bv1 << 1;
    std::cout << "Left shift result BoolVector1: " << leftShift << "\n";

    BoolVector rightShift = bv1 >> 1;
    std::cout << "Right shift result BoolVector1: " << rightShift << "\n";

}