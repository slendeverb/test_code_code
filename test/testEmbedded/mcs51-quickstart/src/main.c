#include "adc.h"
#include "dht11.h"

sbit BUZ = P0 ^ 0;             // 蜂鸣器
sbit LED_LOW = P0 ^ 1;         // 过低警示灯
sbit LED_HIGH = P0 ^ 2;        // 过高警示灯
sbit CHANGE_DISPLAY = P0 ^ 4;  // 更换显示
sbit CHANGE_CHOOSE = P0 ^ 5;   // 更换选择上下限
sbit UP = P0 ^ 6;              // 升高
sbit DOWN = P0 ^ 7;            // 下降

#define DISPLAY_MODEL_MAX 4
#define CHANGE_STEP 1

typedef enum DISPLAY_MODEL {
    DISPLAY_ALL,
    DISPLAY_HUM,
    DISPLAY_TEMP,
    DISPLAY_LIGHT_INTENSITY
} DISPLAY_MODEL;

typedef enum LOW_OR_HIGH { LOW, HIGH } LOW_OR_HIGH;

uchar display_model = 0;                 // 设置显示模式
bit low_or_high = 0;                     // 设置选择下限还是上限
uchar hum_low = 48, hum_high = 52;       // 设置湿度上下限
uchar temp_low = 25, temp_high = 29;     // 设置温度上下限
uchar light_low = 98, light_high = 102;  // 设置光照强度上下限

uchar code choose_low[4] = {'<', '-', '-', '\0'};
uchar code choose_high[4] = {'-', '-', '>', '\0'};

void refresh_display();
void buzzer_led_alarm();

void main() {
    EA = 1;   // 允许总中断
    EX0 = 1;  // 允许外部中断0
    EX1 = 1;  // 允许外部中断1
    IT0 = 1;  // 选择外部中断0为跳沿触发方式
    IT1 = 1;  // 选择外部中断1为跳沿触发方式
    PX0 = 0;  // 设置外部中断0为低优先级
    PX1 = 0;  // 设置外部中断1为低优先级

    BUZ = 0;  // 禁止蜂鸣器

    LCD_init();

    DHT11_delay_1s_after_start();

    while (1) {
        EA = 0;
        refresh_display();  // 在执行结束前关中断
        buzzer_led_alarm();
        EA = 1;
        delay_s(1);
    }
}

void INT0_ISR() interrupt 0 using 0 {
    if (!CHANGE_DISPLAY) {
        display_model = (display_model + 1) % DISPLAY_MODEL_MAX;
        LCD_clear(0, MAX_LENGTH);
        LCD_clear(1, MAX_LENGTH);
    } else if (!CHANGE_CHOOSE) {
        if (display_model == DISPLAY_ALL) {
            return;
        }
        if (low_or_high == LOW) {
            low_or_high = 1;
        } else if (low_or_high == HIGH) {
            low_or_high = 0;
        }
        LCD_clear(1, MAX_LENGTH);
    }
    refresh_display();
}

void INT1_ISR() interrupt 2 using 1 {
    if (display_model == DISPLAY_ALL) {
        return;
    }
    if (!UP) {
        if (low_or_high == LOW) {
            if (display_model == DISPLAY_HUM) {
                hum_low += CHANGE_STEP;
            } else if (display_model == DISPLAY_TEMP) {
                temp_low += CHANGE_STEP;
            } else if (display_model == DISPLAY_LIGHT_INTENSITY) {
                light_low += CHANGE_STEP;
            }
        } else if (low_or_high == HIGH) {
            if (display_model == DISPLAY_HUM) {
                hum_high += CHANGE_STEP;
            } else if (display_model == DISPLAY_TEMP) {
                temp_high += CHANGE_STEP;
            } else if (display_model == DISPLAY_LIGHT_INTENSITY) {
                light_high += CHANGE_STEP;
            }
        }
    } else if (!DOWN) {
        if (low_or_high == LOW) {
            if (display_model == DISPLAY_HUM) {
                hum_low -= CHANGE_STEP;
            } else if (display_model == DISPLAY_TEMP) {
                temp_low -= CHANGE_STEP;
            } else if (display_model == DISPLAY_LIGHT_INTENSITY) {
                light_low -= CHANGE_STEP;
            }
        } else if (low_or_high == HIGH) {
            if (display_model == DISPLAY_HUM) {
                hum_high -= CHANGE_STEP;
            } else if (display_model == DISPLAY_TEMP) {
                temp_high -= CHANGE_STEP;
            } else if (display_model == DISPLAY_LIGHT_INTENSITY) {
                light_high -= CHANGE_STEP;
            }
        }
    }
    LCD_clear(1, MAX_LENGTH);
    refresh_display();
}

void refresh_display() {
    if (display_model == DISPLAY_ALL) {  // 显示湿度, 温度, 光照强度, 不能设置上下限
        memset(rec_dat, 0, sizeof(rec_dat));
        DHT11_receive();
        sprintf(rec_dat, "HUMI:%d%%RH TEMP:%d%cC", (uint)RH, (uint)TH, 0xdf);
        LCD_send(0, 0, rec_dat, MAX_LENGTH);

        memset(rec_dat, 0, sizeof(rec_dat));
        ADC_read();
        sprintf(rec_dat, "LIGHT:%dlux", (uint)light_intensity);
        LCD_send(1, 0, rec_dat, MAX_LENGTH);
    } else if (display_model == DISPLAY_HUM) {  // 显示湿度, 可以设置湿度上下限
        memset(rec_dat, 0, sizeof(rec_dat));
        DHT11_receive();
        sprintf(rec_dat, "HUMI:%d%%RH", (uint)RH);
        LCD_send(0, 0, rec_dat, MAX_LENGTH);

        memset(rec_dat, 0, sizeof(rec_dat));
        if (low_or_high == LOW) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)hum_low, choose_low, (uint)hum_high);
        } else if (low_or_high == HIGH) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)hum_low, choose_high, (uint)hum_high);
        }
        LCD_send(1, 0, rec_dat, MAX_LENGTH);
    } else if (display_model == DISPLAY_TEMP) {  // 显示温度, 可以设置温度上下限
        memset(rec_dat, 0, sizeof(rec_dat));
        DHT11_receive();
        sprintf(rec_dat, "TEMP:%d%cC", (uint)TH, 0xdf);
        LCD_send(0, 0, rec_dat, MAX_LENGTH);

        memset(rec_dat, 0, sizeof(rec_dat));
        if (low_or_high == LOW) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)temp_low, choose_low, (uint)temp_high);
        } else if (low_or_high == HIGH) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)temp_low, choose_high, (uint)temp_high);
        }
        LCD_send(1, 0, rec_dat, MAX_LENGTH);
    } else if (display_model == DISPLAY_LIGHT_INTENSITY) {  // 显示光照强度, 可以设置光照强度上下限
        memset(rec_dat, 0, sizeof(rec_dat));
        ADC_read();
        sprintf(rec_dat, "LIGHT:%dlux", (uint)light_intensity);
        LCD_send(0, 0, rec_dat, MAX_LENGTH);

        memset(rec_dat, 0, sizeof(rec_dat));
        if (low_or_high == LOW) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)light_low, choose_low, (uint)light_high);
        } else if (low_or_high == HIGH) {
            sprintf(rec_dat, "LOW:%d %s HIGH:%d", (uint)light_low, choose_high, (uint)light_high);
        }
        LCD_send(1, 0, rec_dat, MAX_LENGTH);
    }
}

void buzzer_led_alarm() {
    if (RH < hum_low || TH < temp_low || light_intensity < light_low) {
        LED_LOW = 0;
        BUZ = 1;
        delay_s(1);
        LED_LOW = 1;
        BUZ = 0;
        delay_s(1);
    } else if (RH > hum_high || TH > temp_high || light_intensity > light_high) {
        LED_HIGH = 0;
        BUZ = 1;
        delay_s(1);
        LED_HIGH = 1;
        BUZ = 0;
        delay_s(1);
    }
}