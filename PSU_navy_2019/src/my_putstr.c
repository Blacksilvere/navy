/*
** EPITECH PROJECT, 2018
** my_putstr
** File description:
** Display char string per string
*/
#include "../include/my.h"

void my_putstr(char const *str)
{
    int i = 0;
    while (str[i]!='\0')
	i = i + 1;
    write(1, str, i);
}
