/*
** EPITECH PROJECT, 2024
** G-CNA-400-COT-4-1-stoneanalysis-kevin.nouhouayi
** File description:
** dft.cpp
*/

#include "dft.hpp"

std::vector <std::complex<double>> dft(std::vector<double>&  signal) {
    
    int N = signal.size();
    std::vector<std::complex<double>> result(N);

    for (int k = 0; k < N; k++) {
        std::complex<double> sum(0.0, 0.0);
        for (int n = 0; n < N; n++) {
            double angle = -2 * M_PI * k * n / N;
            sum += std::polar(signal[n], angle);
        }
        result[k] = sum;
    }

    return result;

}


std::vector<double> idft(const std::vector<std::complex<double>>& spectrum) {
    int N = spectrum.size();
    std::vector<double> signal(N);

    for (int n = 0; n < N; n++) {
        std::complex<double> sum(0.0, 0.0);
        for (int k = 0; k < N; k++) {
            double angle = 2 * M_PI * k * n / N;
            sum += spectrum[k] * std::exp(std::complex<double>(0, angle));
    }
        signal[n] = sum.real() / N;
    }

    return signal;
}


// (Cooley-Tukey)
void fft(std::vector<std::complex<double>>& a) {
    int N = a.size();
    if (N <= 1) return;

    std::vector<std::complex<double>> even(N / 2);
    std::vector<std::complex<double>> odd(N / 2);

    for (int i = 0; i < N / 2; ++i) {
        even[i] = a[i * 2];
        odd[i] = a[i * 2 + 1];
    }

    fft(even);
    fft(odd);

    for (int k = 0; k < N / 2; k++) {
        std::complex<double> t = std::polar(1.0, -2 * M_PI * k / N) * odd[k];
        a[k] = even[k] + t;
        a[k + N / 2] = even[k] - t;
    }
}

void ifft(std::vector<std::complex<double>>& a) {
    int N = a.size();

    for (int i = 0; i < N; i++) {
        a[i] = std::conj(a[i]);
    }

    fft(a);

    for (int i = 0; i < N; i++) {
        a[i] = std::conj(a[i]) / static_cast<double>(N);
    }
}

void analyze(const std::vector<int16_t>& samples, int sample_rate, int top_n) {
    int N = samples.size();
    std::vector<std::complex<double>> signal(N);

    if (samples.size() %2 != 0) signal.push_back(std::complex<double>(0.0,0.0));
    
    for (int i = 0; i < N; i++) {
        signal[i] = std::complex<double>(samples[i], 0.0);
    }

    fft(signal);

    std::vector<std::pair<double, double>> freq_mags; // (magnitude, fréquence)
    for (int k = 0; k < N / 2; k++) {
        double magnitude = std::abs(signal[k]);
        double frequency = static_cast<double>(k) * sample_rate / N;
        freq_mags.push_back(std::make_pair(magnitude, frequency));
    }

    std::sort(freq_mags.begin(), freq_mags.end(),
               [](std::pair<double, double>a, std::pair<double, double>b) {
                  return a.first > b.first;
                });

    std::cout << "Top " << top_n << " frequencies:\n";
    for (int i = 0; i < top_n && i < freq_mags.size(); ++i) {
        std::cout << freq_mags[i].second << " Hz\n";
    }
}



// int main() {
//     // Exemple : onde sinusoïdale de 440 Hz échantillonnée à 48 kHz pendant 0.01s
//     int sampling_rate = 48000;
//     double frequency = 440.0;
//     double duration = 0.01;
//     int N = static_cast<int>(sampling_rate * duration);

//     std::vector<double> signal(N);
//     for (int n = 0; n < N; ++n) {
//         signal[n] = 0.5 * sin(2 * M_PI * frequency * n / sampling_rate);
//     }

//     auto spectrum = dft(signal);

//     // Affichage des amplitudes
//     for (int k = 0; k < spectrum.size(); ++k) {
//     double magnitude = std::abs(spectrum[k]);
//     std::cout << "Fréquence " << k * sampling_rate / N << " Hz : Amplitude = " << magnitude << std::endl;
//     }

//     return 0;
// }
