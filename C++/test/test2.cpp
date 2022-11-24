#include <stdio.h>

typedef struct Student
{
    int num;
    char name[20];
    double grade;
} S;

void bubble_sort(S s[])
{
    int i = 0, j = 0;
    for (i = 0; i < 10 - 1; i++)
    {
        int count = 0;
        for (j = 0; j < 10 - 1 - i; j++)
        {
            if (s[j].grade < s[j + 1].grade)
            {
                S tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
                count++;
            }
            if (count == 0)
            {
                return;
            }
        }
    }
}

int main()
{
    int i = 0;
    S s[10];
    FILE *pf2 = fopen("file2.txt", "rb");
    FILE *pf3 = fopen("file3.txt", "w");
    FILE *pf4 = fopen("file4.txt", "wb");
    if (pf2 == NULL)
    {
        perror("fopen2");
        return 1;
    }
    if (pf3 == NULL)
    {
        perror("fopen3");
        return 1;
    }
    if (pf4 == NULL)
    {
        perror("fopen4");
        return 1;
    }
    fread(s,sizeof(S),10,pf2);
    bubble_sort(s);
    for (i = 0; i < 10; i++)
    {
        fprintf(pf3, "%d %s %lf", s[i].num, s[i].name, s[i].grade);
    }
    for (i = 0; i < 10; i++)
    {
        fwrite(&s[i], sizeof(S), 1, pf4);
    }
    fclose(pf2);
    fclose(pf3);
    fclose(pf4);
    pf2 = NULL;
    pf3 = NULL;
    pf4 = NULL;
    return 0;
}