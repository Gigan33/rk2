#include "cJSON.h"
#include "lines.h"
#include <stdio.h>


int main()
{
    puts("Enter fileName:");
    char *s = ReadLine();
    FILE *f = fopen(s,"r");
    free(s);

    if(f == NULL)
    {
        puts("File is not founded!");
        return 0;
    }

    char c;
    char *bufferStr = (char *)calloc(1,sizeof(char));
    char fileStr[1024];
    int size = 0;

    while((c = fgetc(f)) != '\n')
    {
        if(c == ',')
            size++;
        PushLine(&bufferStr,c);
    }


    FILE *f1 = fopen("C:\\Users\\dzhik\\CLionProjects\\rk2.1\\output.json","w");

    char **Fields = (char **)calloc(size,sizeof(char*));
    char *buffer = strtok(bufferStr,",");

    for(int i =0;i<size;i++)
    {
        Fields[i] = buffer;
        buffer = strtok(NULL,",");
    }


    fputs("[\n\t", f1);
    int counter = 0;
    int trigger = 1;
    while(fgets(fileStr, 1024, f) != NULL)
    {
        if(!trigger)
        {
            fputs("},", f1);
        }
        fputs("\n{\n",f1);
        buffer = strtok(fileStr, ",");
        while(buffer != NULL)
        {
            if(counter<size && buffer != NULL)
                fprintf(f1,"\"%s\": \"%s\"",Fields[counter++],buffer);
            buffer = strtok(NULL, ",");

            if(counter <size)
                fputc(',',f1);
            fputc('\n',f1);
        }
        counter = 0;
        trigger = 0;
    }

    fputs("}\n]\n\t", f1);

    fclose(f);
    fclose(f1);
    puts("Complete!");
    return 0;
}
