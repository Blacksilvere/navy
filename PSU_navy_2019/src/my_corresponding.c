/*
** EPITECH PROJECT, 2019
** main
** File description:
** c
*/

#include "../include/my.h"

int cor(char c, char *string)
{
    int i = 0;
    while (string[i] != '\0'){
        if (c == string[i])
            return (1);
        i++;
    }
    return (0);
}
