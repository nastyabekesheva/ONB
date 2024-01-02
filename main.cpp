//
//  main.cpp
//  NB
//
//  Created by Nastya Bekesheva on 24.12.2023.
//

#include <iostream>
#include <chrono>
#include <numeric>

#include "NB.hpp"

void test(NBGaluaField &gf, FieldElement &a, FieldElement &b, FieldElement &n) {
    std::vector<double> addition_times, multiplication_times, square_times, power_times, inverse_times, trace_times, total_times;

    for (int i = 0; i < 10; ++i)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // Addition
        auto addition_start = std::chrono::high_resolution_clock::now();
        FieldElement addition_result = gf.add(a, b);
        auto addition_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> addition_duration = addition_end - addition_start;
        addition_times.push_back(addition_duration.count());
        std::cout << "Addition Result: " << gf.to_bin(addition_result) << std::endl;
        std::cout << "Addition Execution Time: " << addition_duration.count() << " seconds" << std::endl;


        // Multiplication
        auto multiplication_start = std::chrono::high_resolution_clock::now();
        FieldElement multiplication_result = gf.mul(a, b);
        auto multiplication_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> multiplication_duration = multiplication_end - multiplication_start;
        multiplication_times.push_back(multiplication_duration.count());
        std::cout << "Multiplication Result: " << gf.to_bin(multiplication_result) << std::endl;
        std::cout << "Multiplication Execution Time: " << multiplication_duration.count() << " seconds" << std::endl;

        // Square
        auto square_start = std::chrono::high_resolution_clock::now();
        FieldElement square_result = gf.square(a);
        auto square_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> square_duration = square_end - square_start;
        square_times.push_back(square_duration.count());
        std::cout << "Square Result: " << gf.to_bin(square_result) << std::endl;
        std::cout << "Square Execution Time: " << square_duration.count() << " seconds" << std::endl;

        // Power
        auto power_start = std::chrono::high_resolution_clock::now();
        FieldElement power_result = gf.pow(a, n);
        auto power_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> power_duration = power_end - power_start;
        power_times.push_back(power_duration.count());
        std::cout << "Power Result: " << gf.to_bin(power_result) << std::endl;
        std::cout << "Power Execution Time: " << power_duration.count() << " seconds" << std::endl;
        
        // Inverse
        auto inverse_start = std::chrono::high_resolution_clock::now();
        FieldElement inverse_result = gf.inverse(a);
        auto inverse_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> inverse_duration = inverse_end - inverse_start;
        inverse_times.push_back(inverse_duration.count());
        std::cout << "Inverse Result: " << gf.to_bin(inverse_result) << std::endl;
        std::cout << "Inverse Execution Time: " << inverse_duration.count() << " seconds" << std::endl;
        
        // Trace
        auto trace_start = std::chrono::high_resolution_clock::now();
        FieldElement trace_result = gf.trace(a);
        auto trace_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> trace_duration = trace_end - trace_start;
        trace_times.push_back(trace_duration.count());
        std::cout << "Trace Result: " << gf.to_bin(trace_result) << std::endl;
        std::cout << "Trace Execution Time: " << trace_duration.count() << " seconds" << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        total_times.push_back(duration.count());
        std::cout << "Total Execution Time for All Operations: " << duration.count() << " seconds" << std::endl;
    }
    
    auto min_addition_time = *std::min_element(addition_times.begin(), addition_times.end());
    auto max_addition_time = *std::max_element(addition_times.begin(), addition_times.end());
    auto avg_addition_time = std::accumulate(addition_times.begin(), addition_times.end(), 0.0) / addition_times.size();

    auto min_multiplication_time = *std::min_element(multiplication_times.begin(), multiplication_times.end());
    auto max_multiplication_time = *std::max_element(multiplication_times.begin(), multiplication_times.end());
    auto avg_multiplication_time = std::accumulate(multiplication_times.begin(), multiplication_times.end(), 0.0) / multiplication_times.size();

    auto min_square_time = *std::min_element(square_times.begin(), square_times.end());
    auto max_square_time = *std::max_element(square_times.begin(), square_times.end());
    auto avg_square_time = std::accumulate(square_times.begin(), square_times.end(), 0.0) / square_times.size();

    auto min_power_time = *std::min_element(power_times.begin(), power_times.end());
    auto max_power_time = *std::max_element(power_times.begin(), power_times.end());
    auto avg_power_time = std::accumulate(power_times.begin(), power_times.end(), 0.0) / power_times.size();
    
    auto min_inverse_time = *std::min_element(inverse_times.begin(), inverse_times.end());
    auto max_inverse_time = *std::max_element(inverse_times.begin(), inverse_times.end());
    auto avg_inverse_time = std::accumulate(inverse_times.begin(), inverse_times.end(), 0.0) / inverse_times.size();
    
    auto min_trace_time = *std::min_element(trace_times.begin(), trace_times.end());
    auto max_trace_time = *std::max_element(trace_times.begin(), trace_times.end());
    auto avg_trace_time = std::accumulate(trace_times.begin(), trace_times.end(), 0.0) / trace_times.size();

    // Output results for each operation
    std::cout << "Addition - Min: " << min_addition_time * 1000 << "ms Max: " << max_addition_time * 1000 << "ms Avg: " << avg_addition_time * 1000 << "ms" << std::endl;
    std::cout << "Multiplication - Min: " << min_multiplication_time * 1000 << "ms Max: " << max_multiplication_time * 1000 << "ms Avg: " << avg_multiplication_time * 1000 << "ms" << std::endl;
    std::cout << "Square - Min: " << min_square_time * 1000 << "ms Max: " << max_square_time * 1000 << "ms Avg: " << avg_square_time * 1000 << "ms" << std::endl;
    std::cout << "Power - Min: " << min_power_time * 1000 << "ms Max: " << max_power_time * 1000 << "ms Avg: " << avg_power_time * 1000 << "ms" << std::endl;
    std::cout << "Inverse - Min: " << min_inverse_time * 1000 << "ms Max: " << max_inverse_time * 1000 << "ms Avg: " << avg_inverse_time * 1000 << "ms" << std::endl;
    std::cout << "Trace - Min: " << min_trace_time * 1000 << "ms Max: " << max_trace_time * 1000 << "ms Avg: " << avg_trace_time * 1000 << "ms" << std::endl;

    // Output results for other operations...
}

int main(int argc, const char * argv[]) {
    FieldElement a("11000001110100010110010110100011001100000100110111101011011101011011110111000000110100001011111110010011011000110001001011011001100000001001101111100010010110110001011001000");
    FieldElement b("00110101111101001111110010100111000011101000110100010010101000101001100101110011100011100001100000000101001010010100000000001001001111010010010111111001111101011111010011101");
    
    std::string tmp = "00001110000000010100011110010000111111011000000011100011001000000010101001001011000100000101011001001011110110110000100110110110101101011010000001111111101010010110101011110";
    std::reverse(tmp.rbegin(), tmp.rend());
    std::cout << tmp << std::endl;
    FieldElement n(tmp);

    NBGaluaField nb;
    FieldElement c = nb.inverse(a);
    FieldElement d = nb.square(a);
    //std::cout <<  nb.to_bin(a) << std::endl;
    //std::cout << std::endl <<  nb.to_bin(c) << std::endl;
    test(nb, a, b, n);
    return 0;
}
