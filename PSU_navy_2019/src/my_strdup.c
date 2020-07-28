/*
** EPITECH PROJECT, 2019
** concat_params
** File description:
** concat av
*/

#include "../include/my.h"

int lendup(char *str)
{
    int i = 0;
    for (i = 0; str[i] != '\0'; i++);
    return (i);
}

char *my_strdupcpy(char *dest, char const *src)
{
    int k = 0;
    for (k = 0; src[k] != '\0'; k++)
        dest[k] = src[k];
    dest[k] = '\0';
    return (dest);
}

char *my_strdup(char *str)
{
    int i = 0;
    char *output = malloc(sizeof(char) * lendup(str) + 1);
    output = my_strdupcpy(output, str);
    return (output);
}
