#include "header.h"

int main() {
    std::string file_path{"C:/Users/slendeverb/Downloads/MAA-v4.24.0-win-x64/debug/gui.log"};
    std::ifstream in{file_path};
    if(!in.is_open()){
        std::cerr<<"cannot open log\n";
        return -1;
    }

    std::map<std::string,int> event_appear_times;
    std::string line;
    std::string event_regex{"事件: "};
    std::vector<std::string> first_floor_event_list{"解惑","高空坠物","在故事结束之后","虫卡兹！","相遇","似是而非","阴魂不散"};

    while(std::getline(in,line)){
        size_t start_pos{line.find(event_regex)};
        if(start_pos==std::string::npos){
            continue;
        }
        start_pos+=event_regex.size();
        size_t end_pos=line.size();
        std::string event_name{line.substr(start_pos,end_pos-start_pos)};
        while(event_name.back()=='\r' || event_name.back()=='\n'){
            event_name.pop_back();
        }
        bool in_list{false};
        for(const auto& event:first_floor_event_list){
            if(event_name==event){
                in_list=true;
                break;
            }
        }
        if(!in_list){
            continue;
        }
        event_appear_times[event_name]++;
    }
    in.close();

    std::vector<std::string> keys;
    std::vector<int> times;
    std::vector<double> probability;
    for(const auto& [key,value]:event_appear_times){
        keys.push_back(key);
        times.push_back(value);
    }
    size_t total_times=std::reduce(times.cbegin(),times.cend(),0);
    std::transform(times.cbegin(),times.cend(),std::back_inserter(probability),[&total_times](int time){
        double probability=static_cast<double>(time)/total_times*100;
        return probability;
    });

    std::ofstream out;
    out.open("data.dat");
    if(!out.is_open()){
        std::cerr<<"cannot open data.dat\n";
        return -1;
    }
    for(size_t i=0;i<keys.size();i++){
        out<<keys[i]<<" "<<times[i]<<" "<<probability[i]<<"\n";
    }
    out.close();

    out.open("plot.gp");
    if(!out.is_open()){
        std::cerr<<"cannot open plot.gp\n";
        return -1;
    }
    out<<"set terminal wxt size 800,600 enhanced font 'Microsoft YaHei'\n";
    out<<"set title '萨卡兹肉鸽一层不期而遇概率'\n";
    out<<"set xlabel '不期而遇'\n";
    out<<"set ylabel '出现次数'\n";
    out<<"set style fill solid\n";
    out<<"set boxwidth 0.7 relative\n";
    out<<"plot 'data.dat' using 0:2:xtic(1) with boxes lc rgb '#1e90ff' notitle, "\
    "'' using 0:($2+10):(sprintf(\"%.1f%%\",$3)) with labels center font ',11' tc 'black' notitle\n";
    out.close();

    std::system("gnuplot --persist plot.gp");
}