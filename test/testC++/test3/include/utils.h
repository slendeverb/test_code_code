#pragma once

#include <string>

// 提取第一个长度大于等于4的数字
std::string extract_first_long_number(const std::string& text);

// 显示windows通知
void show_toast_notification(const std::string& title,const std::string& message);

// 复制验证码到剪贴板并显示通知
std::string copy_verification_code(const std::string& text);