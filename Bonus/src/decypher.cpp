/*
** EPITECH PROJECT, 2025
** c++
** File description:
** c++
*/

#include "Error.hpp"

int get_dominant_frequency(const std::vector<std::complex<double>>& fft_result, int sample_rate) {
    double max_magnitude = 0.0;
    int dominant_index = 0;

    for (int i = 0; i < fft_result.size(); ++i) {
        double magnitude = std::abs(fft_result[i]);
        if (magnitude > max_magnitude) {
            max_magnitude = magnitude;
            dominant_index = i;
        }
    }
    double freq = dominant_index * (sample_rate / fft_result.size());
    return static_cast<int>(freq);
}
