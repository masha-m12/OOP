#include <iostream>
#include <conio.h> 
#include "BoolMatrix.h"
#include "../../BoolVector/BoolVector/BoolVector.h" 

int main() {
    
    BoolMatrix matrix(3, 3, false);

    matrix.set(0, 0, true);
    matrix.set(0, 1, false);
    matrix.set(0, 2, true);

    matrix.set(1, 0, false);
    matrix.set(1, 1, true);
    matrix.set(1, 2, false);

    matrix.set(2, 0, true);
    matrix.set(2, 1, true);
    matrix.set(2, 2, false);

    std::cout << "Matrix:\n" << matrix << "\n";

    matrix.inversion(1, 2);
    std::cout << "Matrix after inversion (1, 2):\n" << matrix << "\n";

    int weightRow1 = matrix.rowWeight(1);
    std::cout << "Weight 1 row: " << weightRow1 << "\n";
    std::cout << "\n";

    BoolVector conjunctionResult = matrix.conjunctionAllRows();
    std::cout << "Conjunction result: " << conjunctionResult << "\n";

    BoolVector disjunctionResult = matrix.disjunctionAllRows();
    std::cout << "Disjunction result: " << disjunctionResult << "\n";
    std::cout << "\n";

    BoolMatrix matrix2(3, 3, true);
    std::cout << "Matrix2:\n" << matrix2 << "\n";

    BoolMatrix andResult = matrix & matrix2;
    std::cout << "matrix & matrix2 result:\n" << andResult << "\n";

    BoolMatrix orResult = matrix | matrix2;
    std::cout << "matrix | matrix2 result:\n" << orResult << "\n";

    BoolMatrix xorResult = matrix ^ matrix2;
    std::cout << "matrix ^ matrix2 result:\n" << xorResult << "\n";

    return 0;
}