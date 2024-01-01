//
//  FieldElement.cpp
//  NB
//
//  Created by Nastya Bekesheva on 25.12.2023.
//

#include "FieldElement.hpp"

FieldElement::FieldElement()
{
    _coeffs = {0, 0, 0};
}

FieldElement::FieldElement(std::vector<uint64_t> c)
{
    if (c.size() != 3)
        throw "((((((";
    _coeffs = c;
}

FieldElement::FieldElement(std::string bin)
{
    _coeffs = {0, 0, 0};
    for (int i = 0; i < bin.size(); ++i)
    {
        if (bin[i] == '1')
            setbit(1, i);
    }
}

void FieldElement::setbit(uint64_t value, std::size_t i)
{
    uint64_t i_1 = i / 64;
    uint64_t i_2 = i % 64;
    
    //std::cout << " initial " << _coeffs[i_1] << std::endl;
    _coeffs[i_1] = (_coeffs[i_1]) & ~((uint64_t)1 << i_2);
    //std::cout << " mid " << _coeffs[i_1] << std::endl;
    _coeffs[i_1] = (_coeffs[i_1]) | (value << i_2);
    //std::cout << " final " << _coeffs[i_1] << std::endl;
}

uint64_t FieldElement::getbit(std::size_t i)
{
    uint64_t i_1 = i / 64;
    uint64_t i_2 = i % 64;
    
    return ((_coeffs[i_1] >> i_2) & 1);
}


std::vector<uint64_t> FieldElement::get_coeffs()
{
    return _coeffs;
}

std::size_t FieldElement::size()
{
    return _coeffs.size();
}

void FieldElement::push_back(uint64_t value)
{
    _coeffs.push_back(value);
}

uint64_t FieldElement::operator[](std::size_t i)
{
    return _coeffs[i];
}

void FieldElement::set(uint64_t value, std::size_t i)
{
    _coeffs[i] = value;
}

FieldElement::FieldElement(const FieldElement &other)
{
    _coeffs = other._coeffs;
}

