#include "utils.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <Windows.h>
#include <shellapi.h>
#include <wintoastlib.h>
#include <encode_convert.h>

class MyToastHandler:public WinToastLib::IWinToastHandler{
public:
    void toastActivated() const {}
    void toastActivated(int actionIndex) const {}
    void toastActivated(std::wstring response) const {}
 
    void toastDismissed(WinToastDismissalReason state) const {}
    void toastFailed() const {}
};

std::string extract_first_long_number(const std::string& text) {
    size_t pos=text.find("验证码");
    std::string filtered_text;
    if(pos!=std::string::npos){
        filtered_text=text.substr(pos);
    }else{
        filtered_text="验证码: 0000";
    }
    std::regex pattern{R"(\d{4,})"};
    std::smatch match;

    if(std::regex_search(filtered_text,match,pattern)){
        return match.str();
    }
    return "";
}

void show_toast_notification(const std::string& title, const std::string& message) {
    if (!WinToastLib::WinToast::isCompatible()) {
        std::cout<<std::format("Your computer is not support WinToast\n");
        return;
    }
    
    std::wstring wtitle=UTF8ToUnicode(title);
    std::wstring wmessage;
    bool first=true;
    size_t prev=0;
    size_t pos=message.find(R"(\n)",prev);
    while(pos!=std::string::npos){
        if(!first){
            wmessage+=L'\n';
        }
        wmessage+=UTF8ToUnicode(message.substr(prev,pos-prev));
        prev=pos+2;
        pos=pos=message.find(R"(\n)",prev);
        first=false;
    }
    if(!first){
        wmessage+=L'\n';
    }
    wmessage+=UTF8ToUnicode(message.substr(prev));

    WinToastLib::WinToast::instance()->setAppName(L"SMS");
    WinToastLib::WinToast::instance()->setAppUserModelId(L"SMS验证码转发服务");
    static bool initialized = false;
    if (!initialized) {
        WinToastLib::WinToast::instance()->setAppName(L"SMS");
        WinToastLib::WinToast::instance()->setAppUserModelId(L"SMS验证码转发服务");
        if(!WinToastLib::WinToast::instance()->initialize()){
            std::cout<<std::format("WinToast initialize failed\n");
            return;
        }
        initialized = true;
    }
    WinToastLib::WinToastTemplate toast(WinToastLib::WinToastTemplate::Text02);
    toast.setTextField(wtitle,WinToastLib::WinToastTemplate::FirstLine);
    toast.setTextField(wmessage,WinToastLib::WinToastTemplate::SecondLine);

    WinToastLib::WinToast::instance()->showToast(toast,new MyToastHandler{});
}

std::string copy_verification_code(const std::string& text) {
    std::string number=extract_first_long_number(text);

    if(!number.empty()){
        if(OpenClipboard(NULL)){
            EmptyClipboard();

            HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,number.size()+1);
            if(hGlobal!=NULL){
                char* pGlobal=(char*)GlobalLock(hGlobal);
                std::strcpy(pGlobal,number.c_str());
                GlobalUnlock(hGlobal);

                SetClipboardData(CF_TEXT,hGlobal);
            }
            CloseClipboard();
        }
        std::cout<<std::format("已复制到剪贴板: {}\n",number);

        // 显示通知
        std::string notification_msg=std::format("验证码: {}",number);
        if(text.size()>3){
            notification_msg=text.substr(1,text.size()-3);
        }
        show_toast_notification("复制成功",notification_msg);
        
        return number;
    }else{
        std::cout<<std::format("未找到符合条件的数字字符串\n");
        show_toast_notification("复制失败","请检查短信验证码");
        return "";
    }
}
