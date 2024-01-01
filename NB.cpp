//
//  NB.cpp
//  NB
//
//  Created by Nastya Bekesheva on 25.12.2023.
//

#include "NB.hpp"
#define p 347


FieldElement NBGaluaField::add(FieldElement &a, FieldElement &b)
{
    FieldElement res;
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        res.set((a[i] ^ b[i]), i);
    }
    
    return res;
}

FieldElement NBGaluaField::mul(FieldElement &a, FieldElement &b)
{
    FieldElement res;
    _mul_matrix = make_multiplicative_matrix();

    
    FieldElement ac = a;
    FieldElement bc = b;
    
    for (uint64_t i = 1; i < 173; ++i)
    {
        uint64_t tmp = mul_one(ac, bc);
        res.setbit(tmp, i);
    }
    
    
    return res;
}

std::string NBGaluaField::to_bin(FieldElement &a)
{
    
    std::string result = "";
    for (int i = 0; i < 173; ++i)
    {
        result += std::to_string(a.getbit(i));
    }
    
    return result;
}

FieldElement NBGaluaField::cycle_shift_one(FieldElement &a)
{
    FieldElement result;
    
    result.set((a[0] << (uint64_t)1), 0);

    
    for (int i = 1; i <= 2; ++i)
    {
        result.set(((a[i] << (uint64_t)1) ^ ((a[i-1] >> (uint64_t)63) & (uint64_t)1)), i);
    }
    
    
    
    //result.set(result[0] | a.getbit(0), 0); //fix this
    result.setbit(a.getbit(172), 0);
    return result;
}



FieldElement NBGaluaField::square(FieldElement &a)
{
    
    return cycle_shift_one(a);
}

FieldElement NBGaluaField::trace(FieldElement &a)
{
    FieldElement res;
    int counter = 0;
    for(int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 64; ++j)
        {
            if ((a[i] >> j) % 2 == 1)
            {
                ++counter;
            }
        }
    }
    res.set(counter, 0);
    
    return res;
}

std::vector<std::vector<uint64_t>> NBGaluaField::make_multiplicative_matrix()
{
    std::vector<std::vector<uint64_t>> matrix;
    std::vector<uint64_t> pow2 = {1};
    
    for (int i = 1; i < 173; ++i)
    {
        pow2.push_back((pow2[i-1] * 2) % p);
    }
    
    for (uint64_t i = 0; i < 173; ++i)
    {
        std::vector<uint64_t> tmp;
        for (uint64_t j = 0; j < 173; ++j)
        {
            if (check_ij((int)pow2[i], (int)pow2[j]) == 1)
            {
                tmp.push_back(j);
            }
        }
        matrix.push_back(tmp);
    }
    
    /*for (uint64_t i = 0; i < 173; ++i)
    {
        FieldElement tmp;
        for (uint64_t j = 0; j < 173; ++j)
        {
            tmp.setbit(check_ij((int)pow2[i], (int)pow2[j]), j);
        }
        matrix.push_back(tmp);
    }*/
    
    return matrix;
}

FieldElement NBGaluaField::cycle_shift_left(FieldElement &a)
{
    FieldElement result;
    
    for (int i = 0; i <= a.size()-2; ++i)
    {
        result.set(((a[i] >> (uint64_t)1) ^ ((a[i+1] & 1) << (uint64_t)63)), i);
    }
    result.set((a[a.size()-1] >> (uint64_t)1), a.size()-1);
    //result.set(result[a.size()-1] ^ a.getbit(0), a.size()-1);
    result.setbit(a.getbit(0), 172);
    return result;
}

uint64_t NBGaluaField::mul_one(FieldElement &a, FieldElement &b)
{
    
    a = (cycle_shift_left(a));
    b = (cycle_shift_left(b));
    
    FieldElement al;
    FieldElement alb_i;
    FieldElement result;
    
    
    for (int i = 0; i < 173; ++i)
    {
        uint64_t al_mul_i = 0;
        for (uint64_t j : _mul_matrix[i])
        {
            al_mul_i ^= a.getbit(j);
        }
        al.setbit(al_mul_i, i);
    }
    /*for (int i = 0; i < 173; ++i)
    {
        for (int j = 0; j < 173; ++j)
        {
            al.setbit((al.getbit(j) ^ (_mul_matrix[i].getbit(j) & a.getbit(i))), j);
        }
    }*/
    
    
    /*for (int i = 0; i < 173; ++i)
    {
        if (a.getbit(i) == 1)
        {
            for (auto j: _mul_matrix[172-i])
            {
                al.setbit((al.getbit(j) ^ 1), j);
            }
        }
    }*/
    /*
    for (int i = 0; i < 3; ++i)
    {
        alb_i.set((al[i] ^ b[i]), 0);
        FieldElement tmp = trace(alb_i);
        result = add(result, tmp);
        
    }*/
    
    uint64_t tmp_res = 0;
    for (int i = 0; i < 173; ++i)
    {
        tmp_res ^= al.getbit(i) & b.getbit(i);
    }
    
    return tmp_res;
    
}

FieldElement NBGaluaField::pow(FieldElement &a,  FieldElement &b)
{
    FieldElement result("1");
    for (int i = 0; i < bit_length(b); ++i)
    {
        result = square(result);
        std::cout << to_bin(result) << std::endl <<  b.getbit(i) << std::endl;
        if (b.getbit(i) == 1)
        {
            result = mul(a, result);
        }
    }
    
    return result;
}

std::size_t NBGaluaField::bit_length(FieldElement &a)
{
    int k = a.size() - 1;
    
    while (a[k] == 0 && k >= 0)
    {
        --k;
    }
    
    if (k < 0)
        return 1;
    else
    {
        std::size_t j = 0;
        uint64_t b = a[k];
        
        while (b != 0)
        {
            ++j;
            b = b / 2;
        }
        
        return (j+64*(k));
        //return j;
    }
    
    
}

uint64_t NBGaluaField::check_ij(int i, int j)
{
    
    if ((i + j) % p == 1)
        return 1;
    else if ((p - (i + j) % p) == 1)
        return 1;
    if (i >= j)
    {
        if ((i - j) % p == 1)
            return 1;
    }
    else if ((j - i) % p == 1)
        return 1;
    return 0;
}

/*uint64_t NBGaluaField::pow2(uint64_t i)
{
    uint64_t res = 1;
    uint64_t i_1 = i / 63;
    uint64_t i_2 = i % 63;
    
    for (int j = 0; j < i_1; ++j)
    {
        res = (res << 63) % p;
    }
    res = (res << i_2) % p;
    
    return res;
}*/

FieldElement NBGaluaField::neu_add()
{
    return FieldElement("0");
}

FieldElement NBGaluaField::neu_mul()
{
    return FieldElement("1");
}
