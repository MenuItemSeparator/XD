#pragma once

#include "SafeAssert.h"
// @Brief: Напишите функцию, удаляющую последовательно дублирующиеся символы в строке:
// ("AAA BBB ААА" -> "A B А")
static void RemoveDups (char *pStr)
{
    m_assert(pStr);
    for (char *dest = pStr, *cur = pStr; (*dest = *cur) != '\0'; (cur[0] != cur[1])? dest++ : dest, cur++);
}
