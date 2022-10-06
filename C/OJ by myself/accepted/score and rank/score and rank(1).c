#include <stdio.h>

int main()
{
    int score = 0;
    printf("请输入百分制分数(示例:90):>");
    while (scanf("%d", &score) != EOF)
    {
        if (score > 100 || score < 0)
        {
            printf("分数不合理,请输入一个0-100之间的数字\n");
        }
        else
        {
            if (score >= 90 && score <= 100)
            {
                printf("成绩为:%d,等级为:%c\n", score, 'A');
            }
            else if (score >= 80 && score <= 89)
            {
                printf("成绩为:%d,等级为:%c\n", score, 'B');
            }
            else if (score >= 70 && score <= 79)
            {
                printf("成绩为:%d,等级为:%c\n", score, 'C');
            }
            else if (score >= 60 && score <= 69)
            {
                printf("成绩为:%d,等级为:%c\n", score, 'D');
            }
            else
            {
                printf("成绩为:%d,等级为:%c\n", score, 'E');
            }
        }
    }
    return 0;
}