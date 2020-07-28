/*
** EPITECH PROJECT, 2019
** main
** File description:
** c
*/

#include "../include/my.h"

int count_corresponding(char *str, char *string)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0'){
        if (cor(str[i], string) == 1)
            j++;
        i++;
    }
    return (j);
}

char **my_str_to_wordtoken(char *str, char *strin)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **tab = malloc(sizeof(char *) * (count_corresponding(str, strin) + 4));
    tab[0] = malloc(sizeof(char) * (my_strlen(str) + 5));
    while (str[i] != '\0'){
        if (cor(str[i], strin) == 1) {
            tab[j][k] = '\0';
            j++;
            k = 0;
            tab[j] = malloc(sizeof(char) * (my_strlen(str) + 5));
        } else {
            tab[j][k] = str[i];
            k++;
        }
        i++;
    }
    tab[j][k] = '\0';
    if (cor(str[i - 1], strin) == 1)
        tab[j] = NULL;
    else
        tab[j + 1] = NULL;
    //tab[j][k] = '\0';
//    tab[j] = NULL;
    return (tab);
}
