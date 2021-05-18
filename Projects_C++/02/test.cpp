#include "test.h"

void function_d(string s)
{
    //std::cout << "In call function for digit " << s << "\n";
    *(&ans_digit) += std::stoi(s);
}

void function_s(string s)
{
    //std::cout << "In call function for string " << s << "\n";
    *(&ans_line) += s.length();
}

void function_b()
{
    *(&ans_begin) = 10;
}

void function_e()
{
    *(&ans_end) = 10;
}

int main(void)
{
    TokenParser tk;
    string s;
    s = "as 1844674";
    tk.SetStartCallback(function_b);
    tk.SetEndCallback(function_e);
    tk.SetDigitTokenCallback(function_d);
    tk.SetLineTokenCallback(function_s);
    tk.parse(s);
    std::cout << ans_begin << "\n";
    std::cout << ans_end << "\n";
    std::cout << ans_line << "\n";
    std::cout << ans_digit << "\n";
}