/*
** EPITECH PROJECT, 2024
** G-CNA-400-COT-4-1-stoneanalysis-kevin.nouhouayi
** File description:
** dft.hpp
*/

#ifndef _DFT_HPP_
    #define _DFT_HPP_

#include <math.h>
#include <complex>
#include <vector>
#include <iostream>
#include <iostream>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <map>
#include <bitset>

std::vector <std::complex<double>> dft(std::vector<double>&  signal);
std::vector<double> idft(const std::vector<std::complex<double>>& spectrum);
void fft(std::vector<std::complex<double>>& a);
void ifft(std::vector<std::complex<double>>& a);
bool read_wav(const std::string& filename, int& sample_rate, std::vector<int16_t>& samples);
void analyze(const std::vector<int16_t>& samples, int sample_rate, int top_n);
void inject_message(std::vector<int16_t>& samples, std::string& message);
void write_wav(const std::string& filename, std::vector<int16_t>& samples);
std::string extract_message(const std::vector<int16_t>& samples);
extern int numbers_of_samples;
extern int32_t data_size;


#endif
