/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "Error.hpp"
#include <signal.h>

extern std::vector<int16_t> c_samples;

void myhandler(int a) {
    (void)a;
    std::cerr<< "A special error occured; let's just stop\n";
    exit(84);
}

int main(int ac, char **av)
{
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

        bool invalid_analyze = (ac == 4 && (strcmp(av[1], "--analyze") != 0 || !is_Convert(av[3])));
        bool invalid_cypher = (ac == 5 && (strcmp(av[1], "--cypher") != 0 || is_AlphanumericOrSpace(av[4]) == false));
        bool invalid_decypher = (ac == 3 && (strcmp(av[1], "--decypher") != 0));

        if (invalid_analyze || invalid_cypher || invalid_decypher) {
            throw Error("Arguments invalides !!");
        }
    } catch (const Error &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
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

