/*
** EPITECH PROJECT, 2024
** G-CNA-400-COT-4-1-stoneanalysis-kevin.nouhouayi
** File description:
** dft.cpp
*/

#include "dft.hpp"

extern char header[44];
extern int numbers_of_samples;
extern int32_t data_size;
int numbers_of_samples;
int32_t data_size;


extern std::vector<int16_t> c_samples;
std::vector<int16_t> c_samples;

// Un fichier .wav commence toujours par un en-tête de 44 octets qui contient :
// Le format (RIFF, WAVE),
// Le nombre de canaux,
// Le taux d’échantillonnage,
// La résolution (bits par échantillon),
// La taille des données audio.
// On vérifie que les 4 premiers octets sont "RIFF" et que les octets 8 à 11 sont "WAVE".
// Cela garantit que le fichier est bien un fichier audio WAV standard.

// Offset | Taille | Contenu
// -------|--------|--------------------------
// 0      | 4      | "RIFF" (identifiant)
// 4      | 4      | Taille totale du fichier - 8
// 8      | 4      | "WAVE" (format)
// 12     | 4      | "fmt " (sous-bloc format)
// 16     | 4      | Taille du sous-bloc (16 pour PCM)
// 20     | 2      | Format audio (1 = PCM)
// 22     | 2      | Nombre de canaux (1 = mono, 2 = stéréo)
// 24     | 4      | Taux d’échantillonnage (ex. 48000)
// 28     | 4      | Byte rate = sample_rate * num_channels * bits_per_sample / 8
// 32     | 2      | Alignement des blocs
// 34     | 2      | Bits par échantillon (ex. 16)
// 36     | 4      | "data" (début des données audio)
// 40     | 4      | Taille des données audio (en octets)
// 44     | ...    | Données audio (échantillons)

bool read_wav(const std::string& filename, int& sample_rate, std::vector<int16_t>& samples) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    file.read(header, 44);

    if (std::string(header, header + 4) != "RIFF" || std::string(header + 8, header + 12) != "WAVE"||
        std::string(header+12, header + 16) != "fmt " || std::string(header + 36, header + 40) != "data") {
        std::cerr << "Erreur : format WAV non valide."<< std::endl;
        return false;
    }

    int16_t num_channels = *reinterpret_cast<int16_t*>(header + 22);
    if (num_channels != 1) {
        std::cerr << "Erreur : le fichier doit être mono (1 canal)." << std::endl;
        return false;
    }

    sample_rate = *reinterpret_cast<int32_t*>(header + 24);
    if (sample_rate != 48000) return false;

    int16_t bits_per_sample = *reinterpret_cast<int16_t*>(header + 34);
    if (bits_per_sample != 16) {
        std::cerr << "Erreur : le fichier doit être en 16 bits PCM." << std::endl;
        return false;
    }

    data_size = *reinterpret_cast<int32_t*>(header + 40);

    if (data_size <= 0) {
        std::cerr << "Erreur : data_size vide ou inférieur a 0." << std::endl;
        return false;
    }

    int num_samples = data_size / 2;
    numbers_of_samples = num_samples;

    samples.resize(num_samples);
    file.read(reinterpret_cast<char*>(samples.data()), data_size);

/********************for c_sample */
    std::ifstream file_c(filename, std::ios::binary);
    if (!file_c) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }
    char h[44];
    file_c.read(h, 44);
    c_samples.resize(data_size);
    file_c.read(reinterpret_cast<char*>(c_samples.data()), data_size);
/******************************************************* */

    if (!file|| ! file_c) {
        std::cerr << "Erreur : lecture incomplète des données audio." << std::endl;
        return false;
    }
    if (samples.empty()) {
        std::cerr << "Erreur : samples vide" << std::endl;
        return false;
    }

    return true;
}


void inject_message(std::vector<int16_t>& samples, std::string& message) {
    std::reverse(message.begin(), message.end());
    
    auto bits_creator = [&]() {
        std::vector<std::bitset<8>> bits; 
        for (const auto ch : message) {
            std::bitset<8> bit(ch);
            bits.push_back(bit);
        }
        std::bitset<8> bit(0);
        bits.push_back(bit);
        return bits;
    };
    auto vec_bits = bits_creator();
    size_t total_bits = vec_bits.size() * 8;
    if (samples.size() < total_bits) {
        throw std::runtime_error("Pas assez d'échantillons pour cacher le message.");
    }

    size_t bit_index = 0;
    for (const auto& byte : vec_bits) {
        for (int i = 7; i >= 0; i--) {
            samples[bit_index] &= ~1;
            samples[bit_index] |= byte[i];
            bit_index++;
        }
    }
}


std::string extract_message(const std::vector<int16_t>& samples) {
    std::string message;
    std::bitset<8> current_byte;
    int bit_count = 0;

    for (size_t i = 0; i < samples.size(); ++i) {
        current_byte[7 - bit_count] = samples[i] & 1;
        bit_count++;

        if (bit_count == 8) {
            char ch = static_cast<char>(current_byte.to_ulong());
            if (ch == '\0') break;
            message += ch;
            bit_count = 0;
            current_byte.reset();
        }
    }

    std::reverse(message.begin(), message.end()); // Inverser pour retrouver le message original
    return message;
}



void write_wav(const std::string& filename, std::vector<int16_t>& samples) {

    std::ofstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Can't create the output file");
    file.write(header, 44);

    file.write(reinterpret_cast<const char*>(samples.data()),data_size);
}