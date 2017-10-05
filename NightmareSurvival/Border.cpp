// Border.cpp
#include "Border.h"

void Border::Draw() const
{
    std::cout << m_border;
}

char Border::GetChar()
{
    return m_border;
}

