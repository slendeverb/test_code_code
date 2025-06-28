#if !defined(__LDR__)
#define __LDR__

#include "lcd.h"

sbit CS = P1 ^ 1;
sbit CLK = P1 ^ 2;
sbit DI = P1 ^ 3;
sbit DO = P1 ^ 4;

uchar light_intensity;  // 用于接收光照强度数据

void ADC_read() {
    uchar i;

    light_intensity = 0;

    CS = 0;  // 使能ADC
    CLK = 0;

    // 发送配置位：起始位(1) + 单端模式(1) + 通道0(0)
    DI = 1, CLK = 1, CLK = 0;  // 起始位
    DI = 1, CLK = 1, CLK = 0;  // SGL=1（单端模式）
    DI = 0, CLK = 1, CLK = 0;  // ODD=0（选择CH0）

    // 读取8位数据（高位在前）
    for (i = 0; i < 8; i++) {
        CLK = 1;
        CLK = 0;                // 下降沿读取数据
        light_intensity <<= 1;  // 左移一位
        if (DO) {
            light_intensity |= 0x01;  // 读取DO值
        }
    }

    CS = 1;  // 禁用ADC
}

#endif  // __LDR__
