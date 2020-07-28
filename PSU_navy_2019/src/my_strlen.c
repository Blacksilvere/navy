/*
** EPITECH PROJECT, 2019
** my_swap
** File description:
** pool
*/

#include "../include/my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}
