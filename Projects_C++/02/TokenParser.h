#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>

using namespace std;

class TokenParser
{
    public:
        TokenParser() = default;
        void (*startCallback)() = nullptr, (*endCallback)() = nullptr;
        void (*digitTokenCallback)(string) = nullptr, (*lineTokenCallback)(string) = nullptr;

        // Устанавливаем callback-функцию перед стартом парсинга.
        void SetStartCallback(void func());

        // Устанавливаем callback-функцию после окончания парсинга.
        void SetEndCallback(void func());

        // Устанавливаем callback функцию для обработки чисел.
        void SetDigitTokenCallback(void func(string));

        // Устанавливаем callback функцию для обработки строк.
        void SetLineTokenCallback(void func(string));

        bool isNumber(string s);
        void parse(string s);
};