#include "lines.h"


void PushLine(char **s, char value) //Добавление символа в строку
{
    int len = strlen(*s);
    char *buffer = (char *)malloc((len + 2) * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        buffer[i] = (*s)[i];
    }
    buffer[len] = value;
    buffer[len + 1] = '\0';
    free(*s);
    *s = buffer;
}


char * ReadLine() //Считывание строки произвольной длины из консоли
{
    char c;
    char *str = (char*)calloc(1,sizeof(char));
    while((c = getchar()) != '\n')
        PushLine(&str,c);
    return str;
}