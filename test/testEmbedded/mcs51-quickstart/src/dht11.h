#if !defined(__DHT11__)
#define __DHT11__

#include "lcd.h"

#define MAX_LENGTH 21
sbit HT = P1 ^ 0;           // 定义数据线
uchar rec_dat[MAX_LENGTH];  // 用于显示的接收数据数组
uchar RH, TH;               // 用于接收湿度和温度数据

void DHT11_delay_us(uchar us) {
    while (--us)
        ;
}

void DHT11_delay_ms(uint ms) {
    uchar j;
    while (--ms) {
        for (j = 110; j > 0; j--)
            ;
    }
}

void DHT11_delay_1s_after_start() {
    delay_ms(1000);
}

void DHT11_start() {
    HT = 1;
    DHT11_delay_us(2);
    HT = 0;
    DHT11_delay_ms(30);  // 延时18ms以上
    HT = 1;
    DHT11_delay_us(30);
}

uchar DHT11_rec_byte()  // 接收一个字节
{
    uchar i, dat = 0;
    for (i = 0; i < 8; i++)  // 从高到低依次接收8位数据
    {
        while (!HT)
            ;               // 等待50us低电平过去
        DHT11_delay_us(8);  // 延时60us，如果还为高则数据为1，否则为0
        dat <<= 1;          // 移位使正确接收8位数据，数据为0时直接移位
        if (HT == 1) {      // 数据为1时，使dat加1来接收数据1
            dat += 1;
        }
        while (HT)
            ;  // 等待数据线拉低
    }
    return dat;
}

void DHT11_receive()  // 接收40位的数据
{
    uchar R_H, R_L, T_H, T_L, RL, TL, revise;
    DHT11_start();
    if (HT == 0) {
        while (HT == 0)
            ;                       // 等待拉高
        DHT11_delay_us(40);         // 拉高后延时80us
        R_H = DHT11_rec_byte();     // 接收湿度高八位
        R_L = DHT11_rec_byte();     // 接收湿度低八位
        T_H = DHT11_rec_byte();     // 接收温度高八位
        T_L = DHT11_rec_byte();     // 接收温度低八位
        revise = DHT11_rec_byte();  // 接收校正位

        DHT11_delay_us(25);  // 结束

        if ((R_H + R_L + T_H + T_L) == revise)  // 校正
        {
            RH = R_H;
            RL = R_L;
            TH = T_H;
            TL = T_L;
        }
    }
}

#endif  // __DHT11__
