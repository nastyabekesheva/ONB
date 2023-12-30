//
//  FieldElement.hpp
//  NB
//
//  Created by Nastya Bekesheva on 25.12.2023.
//

#ifndef FieldElement_hpp
#define FieldElement_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

class FieldElement
{
private:
    std::vector<uint64_t> _coeffs;
    int comp(FieldElement &other) const;
    //void remove_zeros();
public:
    FieldElement();
    FieldElement(const FieldElement &other);
    FieldElement(std::vector<uint64_t> c);
    FieldElement(std::string bin);
    
    uint64_t getbit(std::size_t i);
    void setbit(uint64_t value, std::size_t i);
    std::vector<uint64_t> get_coeffs();
    std::size_t size();
    void push_back(uint64_t value);
    uint64_t operator[](std::size_t i);
    void set(uint64_t value, std::size_t i);
    FieldElement& operator=(const FieldElement &other) = default;
    
    
};

#endif /* FieldElement_hpp */
