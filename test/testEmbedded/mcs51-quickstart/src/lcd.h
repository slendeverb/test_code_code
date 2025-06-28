#if !defined(__LCD__)
#define __LCD__

#include "REG51.H"
#include "STDIO.H"
#include "STRING.H"

#define uchar unsigned char
#define uint unsigned int

sbit RS = P1 ^ 5;  // 数据/命令, 高电平数据, 低电平命令
sbit RW = P1 ^ 6;  // 读写, 高电平读, 低电平写
sbit E = P1 ^ 7;   // 使能, 高电平有效

void delay_ms(uchar ms) {
    uchar i, j;
    for (i = ms; i > 0; i--) {
        for (j = 110; j > 0; j--)
            ;
    }
}

void delay_s(uchar s) {
    uchar i;
    while (s--) {
        for (i = 0; i < 10; i++) {
            delay_ms(100);
        }
    }
}

int LCD_write_com(uchar com)  // 写命令
{
    RS = 0;
    RW = 0;
    P2 = com;
    delay_ms(5);
    E = 1;
    delay_ms(5);
    E = 0;
    return 0;
}

int LCD_write_data(uchar data1)  // 写数据
{
    RS = 1;
    RW = 0;
    P2 = data1;
    delay_ms(5);
    E = 1;
    delay_ms(5);
    E = 0;
    return 0;
}

int LCD_init()  // 初始化
{
    E = 0;
    LCD_write_com(0X38);  // 设置16*2显示，5*7点阵，8位数据接口
    LCD_write_com(0X0C);  // 设置开显示，不显示光标
    LCD_write_com(0X06);  // 写一个字符时，整屏右移
    LCD_write_com(0X01);  // 显示清零
    return 0;
}

void LCD_send(uchar i, uchar j, uchar str[], uchar n) {
    // 输入：显示行数i,列数j，输出字符，输出字符长度n
    uchar x = 0;
    if (i == 0) {
        LCD_write_com(0x80 + j);
    } else {
        LCD_write_com(0x80 + 0x40 + j);
    }
    for (x = 0; x < n && str[x]; x++) {
        LCD_write_data(str[x]);
    }
}

void LCD_clear(uchar i, uchar n) {
    uchar x;
    if (i == 0) {
        LCD_write_com(0x80);
    } else {
        LCD_write_com(0x80 + 0x40);
    }
    for (x = 0; x < n; x++) {
        LCD_write_data(' ');
    }
}

#endif  // __LCD__
