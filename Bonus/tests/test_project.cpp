/*
** EPITECH PROJECT, 2024
** unit_test
** File description:
** unit test
*/

#include <criterion/criterion.h>
#include "../src/Error.hpp"
#include <string>

Test(testint, file)
{
    std::string str = "Open_my_fail";
    std::string st = "9901";

    bool i = is_Convert(str.c_str());
    bool p = is_Convert(st.c_str());

    cr_assert_eq(i, 0);
    cr_assert_neq(i, 1);

    cr_assert_eq(p, 1);
    cr_assert_neq(p, 0);
}

Test(testchar, verificate)
{
    std::string str = "Cmt boss";
    std::string st = "////";
    std::string tsr = "0459";

    bool a = is_Alpha(str.c_str());
    bool b = is_Alpha(st.c_str());
    bool c = is_Alpha(tsr.c_str());

    cr_assert_eq(a, 0);
    cr_assert_eq(b, 0);
    cr_assert_eq(c, 0);

    cr_assert_neq(a, 1);
    cr_assert_neq(b, 1);
    cr_assert_neq(c, 1);

}

Test(test_invalide_song, verificate)
{
    std::string song = "tests/sine440.wav";
    std::string song1 = "tests/tests/stone_analysis-tests_invalid_file.wav";
    int sample_rate;
    std::vector<int16_t> samples;

    bool a = read_wav(song, sample_rate, samples);
    bool b = read_wav(song1, sample_rate, samples);

    cr_assert_eq(a, 1);
    cr_assert_eq(b, 0);
    cr_assert_neq(a, 0);
    cr_assert_neq(b, 1);
}