#include "TokenParser.h"

void TokenParser::SetStartCallback(void func())
{
    startCallback = func;
}

void TokenParser::SetEndCallback(void func())
{
    endCallback = func;
}

void TokenParser::SetDigitTokenCallback(void func(string))
{
    digitTokenCallback = func;
}

void TokenParser::SetLineTokenCallback(void func(string))
{
    lineTokenCallback = func;
}

bool TokenParser::isNumber(string s)
{
    if (s.find_first_not_of("0123456789") == string::npos)
    {
        
        return true;
    }
    return false;
}

void TokenParser::parse(string s)
{
    string delim = {"\t\n "}, tmp;
    std::size_t prev = 0, pos;
    if (startCallback)
        startCallback();
    //std::cout << "BEGIN" << "\n";
    while ((pos = s.find_first_of(delim, prev)) != std::string::npos)
    {
        if (pos > prev)
        {
            tmp = s.substr(prev, pos - prev);
            if (isNumber(tmp))
            {
                if (digitTokenCallback)
                    digitTokenCallback(tmp);
            }

            else
            {
                if (lineTokenCallback)
                    lineTokenCallback(tmp);
            }
        }
        prev = pos + 1;
    }
    if (prev < s.length())
    {
        tmp = s.substr(prev, std::string::npos);
        if (isNumber(tmp))
        {
            if (digitTokenCallback)
                digitTokenCallback(tmp);
        }

        else
        {
            if (lineTokenCallback)
                lineTokenCallback(tmp);
        }
    }
    if (endCallback)
        endCallback();
}

