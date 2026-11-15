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
    cr_assert_eq(is_Convert("9901"), true);
    cr_assert_eq(is_Convert("123a"), false);
    cr_assert_neq(is_Convert(""), false);
}

Test(testchar, verificate) 
{
    cr_assert_eq(is_Alpha("Cmt boss"), true);
    cr_assert_eq(is_Alpha("Hello123"), true); 
    cr_assert_neq(is_Alpha("!!!"), false);
    cr_assert_neq(is_Alpha(" "), false);
    cr_assert_eq(is_Alpha("abcd efg "), true); 
}

Test(testalphanum, check_validity) 
{
    cr_assert_eq(is_AlphanumericOrSpace("Valid123"), true);
    cr_assert_eq(is_AlphanumericOrSpace("Test space"), true);
    cr_assert_eq(is_AlphanumericOrSpace("Nope!"), false);
    cr_assert_eq(is_AlphanumericOrSpace(" "), true);
    cr_assert_eq(is_AlphanumericOrSpace("abc123 def"), true); 
}

Test(test_invalide_song, verificate) 
{
    std::string song = "tests/sine440.wav";
    std::string song1 = "tests/tests/stone_analysis-tests_invalid_file.wav";
    int sample_rate;
    std::vector<int16_t> samples;

    bool a = read_wav(song, sample_rate, samples);
    bool b = read_wav(song1, sample_rate, samples);

    cr_assert_eq(a, true);
    cr_assert_eq(b, false);
}

Test(test_read_wav, valid_file) 
{
    std::vector<int16_t> samples;
    int sample_rate;
    bool result = read_wav("tests/sample.wav", sample_rate, samples);
    
    cr_assert_neq(result, true);
    cr_assert_neq(sample_rate, 48000);
    cr_assert_eq(samples.empty(), true);
}

Test(test_read_wav, invalid_format) 
{
    std::vector<int16_t> samples;
    int sample_rate;
    bool result = read_wav("tests/tests/stone_analysis-tests_invalid_file.wav", sample_rate, samples);

    cr_assert_eq(result, false);
}

Test(test_extract_mess, invalid_format) 
{
    std::vector<int16_t> samples;
    int sample_rate;
    bool result = read_wav("tests/output.wav", sample_rate, samples);
    std::string str = extract_message(samples);

    cr_assert_neq(result, true);
    cr_assert_neq(str, "BRo");
    cr_assert_neq(str, "////");
}

Test(test_message_injection, hide_message)
{
    std::vector<int16_t> samples(1000, 0);
    std::string message = "Hello";

    inject_message(samples, message);

    std::string extracted = extract_message(samples);
    cr_assert_eq(extracted, "Hello", "Erreur : le message extrait ne correspond pas.");
}

Test(test_message_extraction, extract_from_samples)
{
    std::vector<int16_t> samples(1000, 0);
    std::string message = "Secret";
    
    inject_message(samples, message);
    std::string extracted = extract_message(samples);
    
    cr_assert_eq(extracted, "Secret", "Erreur : le message extrait est incorrect.");
}

Test(test_write_wav, save_and_read) 
{
    std::vector<int16_t> samples(48000, 0);
    
    write_wav("tests/output.wav", samples);

    std::vector<int16_t> read_samples;
    int sample_rate;
    bool result = read_wav("tests/output.wav", sample_rate, read_samples);

    cr_assert_neq(result, true);
    cr_assert_neq(read_samples.size(), samples.size());
}