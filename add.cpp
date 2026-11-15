#include <fstream>
#include <cmath>
#include <cstdint>
#include <vector>

void write_wav(const std::string& filename, int sample_rate, int duration_sec, double freq) {
    int num_samples = sample_rate * duration_sec;
    std::vector<int16_t> samples(num_samples);

    for (int i = 0; i < num_samples; ++i) {
        double t = static_cast<double>(i) / sample_rate;
        samples[i] = static_cast<int16_t>(32767.0 * std::sin(2.0 * M_PI * freq * t));
    }

    std::ofstream file(filename, std::ios::binary);
    file.write("RIFF", 4);
    int file_size = 36 + num_samples * 2;
    file.write(reinterpret_cast<const char*>(&file_size), 4);
    file.write("WAVEfmt ", 8);
    int subchunk1_size = 16;
    int16_t audio_format = 1;
    int16_t num_channels = 1;
    int byte_rate = sample_rate * num_channels * 2;
    int16_t block_align = num_channels * 2;
    int16_t bits_per_sample = 16;

    file.write(reinterpret_cast<const char*>(&subchunk1_size), 4);
    file.write(reinterpret_cast<const char*>(&audio_format), 2);
    file.write(reinterpret_cast<const char*>(&num_channels), 2);
    file.write(reinterpret_cast<const char*>(&sample_rate), 4);
    file.write(reinterpret_cast<const char*>(&byte_rate), 4);
    file.write(reinterpret_cast<const char*>(&block_align), 2);
    file.write(reinterpret_cast<const char*>(&bits_per_sample), 2);

    file.write("data", 4);
    int data_chunk_size = num_samples * 2;
    file.write(reinterpret_cast<const char*>(&data_chunk_size), 4);
    file.write(reinterpret_cast<const char*>(samples.data()), data_chunk_size);
}

int main() {
    write_wav("sine440.wav", 48000, 2, 440.0); // 2 secondes, 440 Hz
    return 0;
}