//
//  NB.hpp
//  NB
//
//  Created by Nastya Bekesheva on 25.12.2023.
//

#ifndef NB_hpp
#define NB_hpp

#include "FieldElement.hpp"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

class NBGaluaField
{
private:
    unsigned int _extension = 173;
    std::vector<std::vector<uint64_t>> _mul_matrix;
    
public:
    NBGaluaField() = default;
    FieldElement add(FieldElement &a, FieldElement &b);
    FieldElement mul(FieldElement &a, FieldElement &b);
    FieldElement pow(FieldElement &a, FieldElement &b);
    FieldElement square(FieldElement &a);
    FieldElement inverse(FieldElement &a);
    FieldElement trace(FieldElement &a);
    FieldElement neu_add();
    FieldElement neu_mul();
    
    FieldElement cycle_shift_one(FieldElement &a);
    FieldElement cycle_shift_left(FieldElement &a);
    std::size_t bit_length(FieldElement &a);
    std::string to_bin(FieldElement &a);
    
private:
    std::vector<std::vector<uint64_t>> make_multiplicative_matrix();
    uint64_t mul_one(FieldElement &a, FieldElement &b);
    uint64_t check_ij(int i, int j);
    uint64_t pow2(uint64_t i);
};

#endif /* NB_hpp */
