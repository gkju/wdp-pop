#include <cassert>
#include <vector>
#include <iostream>
#include "prev.h"

int main() {
    std::vector<int> seq = {6, 2, 9, 1, 4, 6};
    init(seq);
    assert(prevInRange(5, 7, 10) == 2);
    std::cout << "ASSERTED " << prevInRange(5, 7, 10) << std::endl;
    assert(prevInRange(5, 12, 14) == -1);
    assert(prevInRange(5, 6, 6) == 5);
    assert(prevInRange(0, 3, 7) == 0);
    std::cout << "ASSERTED " << prevInRange(5, 12, 14) << std::endl;
    std::cout << "ASSERTED " << prevInRange(5, 6, 6) << std::endl;
    std::cout << "ASSERTED " << prevInRange(0, 3, 7) << std::endl;
    pushBack(3);
    assert(prevInRange(5, 1, 3) == 3);
    assert(prevInRange(6, 1, 3) == 6);
    std::cout << "ASSERTED " << prevInRange(5, 1, 3) << std::endl;
    std::cout << "ASSERTED " << prevInRange(6, 1, 3) << std::endl;
    std::cout << "ASSERTED";
    pushBack(6);
    done();
}
