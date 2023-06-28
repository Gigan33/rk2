#include "lines.h"

void MakeFields(cJSON *head,FILE *f) //Рекурсивный проход структуры JSON и запись полей в файл, разделенных запятой
{
    int flag = 0;
    if(head->child !=NULL)
    {
        flag = 1;
        MakeFields(head->child,f);
    }
    if(head->next!=NULL)
        MakeFields(head->next,f);
    if(!flag)
        fprintf(f,"%s,",head->string);
}

void MakeCsv(cJSON *head,FILE *f) // Рекурсивный проход JSON записываются ЗНАЧЕНИЯ полей в файл,разделенные запятой
{
    int flag = 0;
    if(head->child !=NULL)
    {
        flag = 1;
        MakeCsv(head->child,f);
    }
    if(head->next!=NULL)
        MakeCsv(head->next,f);
    if(!flag)
    {
        if(head->type == cJSON_String)
            fprintf(f,"%s,",head->valuestring);
        else if(head->type == cJSON_Number)
            fprintf(f,"%g,",head->valuedouble);
    }
}

int main()
{
    puts("Enter filename:");
    char *s = ReadLine();

    FILE *f = fopen(s,"r");
    free(s);
    if(f == NULL)
    {
        puts("File is not founded!");
        return 0;
    }

    char c;
    char *fileStr = (char *)calloc(1,sizeof(char));
    while ((c = fgetc(f)) != EOF)
        PushLine(&fileStr,c);
    fclose(f);
    cJSON *json = cJSON_Parse(fileStr);

    if(json == NULL)
    {
        puts("Parce panic!");
        return 0;
    }

    if(!cJSON_IsArray(json))
    {
        puts("Error! JSON is incorrect!");
        return 0;
    }

    int size = cJSON_GetArraySize(json);
    cJSON **data = (cJSON **) malloc(size * sizeof(cJSON*));
    cJSON *buffer;
    for (int i = 0; i < size; i++)
    {
        buffer = cJSON_GetArrayItem(json, i);
        data[i] = buffer;
    }

    f = fopen("C:\\Users\\dzhik\\CLionProjects\\rk_2\\output.csv","w");

    MakeFields(data[0]->child,f);

    fputc('\n',f);

    for(int i =0;i<size;i++)
    {
        MakeCsv(data[i]->child,f);
        fputc('\n',f);
    }

    fclose(f);
    puts("Complete!");
    return 0;
