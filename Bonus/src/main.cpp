/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/


#include <vector>
#include <signal.h>
#include "Error.hpp"
#include <SFML/Graphics.hpp>

extern std::vector<int16_t> c_samples;

std::vector<float> extractFrequencies(const std::vector<int16_t>& samples, int sample_rate)
{
    int N = samples.size();
    std::vector<std::complex<double>> signal(N);

    for (int i = 0; i < N; i++) {
        signal[i] = std::complex<double>(samples[i], 0.0);
    }
    fft(signal);
    std::vector<float> frequencies;
    for (int k = 0; k < N / 2; k++) {
        float magnitude = std::abs(signal[k]);
        frequencies.push_back(magnitude);
    }

    return frequencies;
}

void displayFrequencies(const std::vector<float>& frequencies)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "stone analyze");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        if (frequencies.empty()) {
            std::cerr << "Error\n";
            return;
        }
        float maxValue = *std::max_element(frequencies.begin(), frequencies.end());
        if (maxValue == 0) maxValue = 1;
        float barHeight = static_cast<float>(window.getSize().y) / frequencies.size(); 
        for (size_t i = 0; i < frequencies.size(); i++) {
            float barWidth = (frequencies[i] / maxValue) * window.getSize().x;
            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setPosition(0, i * barHeight);
            bar.setFillColor(sf::Color(100 + (i % 155), 200, 50));
            window.draw(bar);
        }
        window.display();
    }
}

void myhandler(int a) {
    (void)a;
    std::cerr<< "A special error occured; let's just stop\n";
    exit(84);
}

int main(int ac, char **av)
{
    if (strcmp(av[1], "--graph") == 0) {

        int sample_rate;
        std::vector<int16_t> samples;
        read_wav(av[2], sample_rate, samples);
        std::vector<float> Frequencies = extractFrequencies(samples, sample_rate);
        displayFrequencies(Frequencies); 
    } else {
        signal(SIGSEGV,&myhandler);
        std::string present_flag;
        try {
            if (ac != 3 && ac != 4 && ac != 5)
            throw Error(" arguments !!");
        } catch (const Error &e) {
            std::cerr << "Invalide" << e.what() << std::endl;
            exit(84);
        }
        try {
            present_flag = av[1];
            if ((ac == 4 && (strcmp(av[1], "--analyze")!= 0 || !is_Convert(av[3]))) || 
            (ac == 5 && (strcmp(av[1], "--cypher")!= 0 )) ||
            (ac == 3 && (strcmp(av[1], "--decypher") != 0)))
            throw Error(" arguments !!");
        } catch (const Error &e) {
            std::cerr << "Invalide" << e.what() << std::endl;
            exit(84);
        }

    //---------------  ANALYSE ---------------------------------- 
        try {
            char header[44] = {0};
            if (present_flag == "--analyze"){
                std::string filename = av[2];
                int sample_rate;
                std::vector<int16_t> samples;

                if (read_wav(filename, sample_rate, samples)) {
                    analyze(samples, sample_rate,  std::stoi(av[3]) );
                } else {
                    throw Error("A problem occured when reading the file");
                }
                return 0;
            }
            if (present_flag == "--cypher") {
                std::string filename = av[2];
                std::string message = av[4];
                int sample_rate;
                std::vector<int16_t> samples;

                if (read_wav(filename, sample_rate, samples)) {
                    inject_message(c_samples, message);
                    write_wav(std::string(av[3]), c_samples);
                } else {
                    throw Error("A problem occured when reading the file");
                }
                return 0;
            }
            if (present_flag == "--decypher") {
                std::string filename = av[2];
                int sample_rate;
                std::vector<int16_t> samples;
                if (read_wav(filename, sample_rate, samples)) {
                    std::string message = extract_message(c_samples);
                    std::cout << message <<std::endl;
                } else {
                    throw Error("A problem occured when reading the file");
                }
                return 0;
            }

        } catch (const Error &e) {
            std::cerr << "Invalide" << e.what() << std::endl;
            exit(84);
        }
    }
}