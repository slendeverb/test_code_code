#include "header.h"
using namespace std;

int main() {
    std::stringstream ssm{R"(boost:x64-windows: REMOVED: 12.7 ms
boost-mysql:x64-windows: REMOVED: 64.5 ms
boost-parameter-python:x64-windows: REMOVED: 12.8 ms
boost-python:x64-windows: REMOVED: 77.4 ms
ffmpeg:x64-windows: REMOVED: 91.2 ms
qt5:x64-windows: REMOVED: 37.3 ms
qt5-quickcontrols2:x64-windows: REMOVED: 285 ms
qt5-quickcontrols:x64-windows: REMOVED: 218 ms
qt5-graphicaleffects:x64-windows: REMOVED: 37.3 ms
qt5-charts:x64-windows: REMOVED: 112 ms
qt5-translations:x64-windows: REMOVED: 185 ms
qt5-tools:x64-windows: REMOVED: 416 ms
qt5-multimedia:x64-windows: REMOVED: 94.7 ms
qt5-websockets:x64-windows: REMOVED: 27.2 ms
qt5-declarative:x64-windows: REMOVED: 327 ms
qt5-imageformats:x64-windows: REMOVED: 22.8 ms
qt5-activeqt:x64-windows: REMOVED: 46.3 ms
qt5-networkauth:x64-windows: REMOVED: 25.4 ms
qt5-svg:x64-windows: REMOVED: 25.7 ms
qt5-base:x64-windows: REMOVED: 1.2 s
harfbuzz:x64-windows: REMOVED: 29.3 ms
sfml:x64-windows: REMOVED: 68.1 ms
freetype:x64-windows: REMOVED: 37.2 ms
python3:x64-windows: REMOVED: 690 ms
libffi:x64-windows: REMOVED: 17.4 ms
libflac:x64-windows: REMOVED: 22.3 ms
libvorbis:x64-windows: REMOVED: 20.4 ms
libogg:x64-windows: REMOVED: 16.6 ms
opencv:x64-windows: REMOVED: 11.3 ms
opencv4:x64-windows: REMOVED: 133 ms
libpng:x64-windows: REMOVED: 26.6 ms
onnx-optimizer:x64-windows: REMOVED: 30 ms
onnx:x64-windows: REMOVED: 40.4 ms
openvdb:x64-windows: REMOVED: 53.6 ms
openexr:x64-windows: REMOVED: 53 ms
openssl:x64-windows: REMOVED: 51 ms
physx:x64-windows: REMOVED: 116 ms
vcpkg-msbuild:x64-windows: REMOVED: 13.1 ms
vcpkg-pkgconfig-get-modules:x64-windows: REMOVED: 12.2 ms
pkgconf:x64-windows: REMOVED: 18.2 ms
protobuf:x64-windows: REMOVED: 91.5 ms
vcpkg-tool-meson:x64-windows: REMOVED: 11.3 ms
vcpkg-cmake-get-vars:x64-windows: REMOVED: 10.7 ms
vulkan:x64-windows: REMOVED: 10.2 ms
vulkan-loader:x64-windows: REMOVED: 13.7 ms
vulkan-headers:x64-windows: REMOVED: 25.6 ms
vcpkg-cmake-get-vars:x64-windows: SUCCEEDED: 2.3 s
openssl:x64-windows: SUCCEEDED: 5 min
boost-mysql:x64-windows: SUCCEEDED: 6.7 s
vcpkg-make:x64-windows: SUCCEEDED: 11 s
libffi:x64-windows: SUCCEEDED: 4.3 min
vcpkg-tool-meson:x64-windows: SUCCEEDED: 296 ms
pkgconf:x64-windows: SUCCEEDED: 15 s
vcpkg-pkgconfig-get-modules:x64-windows: SUCCEEDED: 134 ms
vcpkg-msbuild:x64-windows: SUCCEEDED: 120 ms
python3:x64-windows: SUCCEEDED: 3.7 min
boost-python:x64-windows: SUCCEEDED: 27 s
boost-parameter-python:x64-windows: SUCCEEDED: 3.8 s
boost:x64-windows: SUCCEEDED: 138 ms
ffmpeg:x64-windows: SUCCEEDED: 14 min
libpng:x64-windows: SUCCEEDED: 12 s
freetype:x64-windows: SUCCEEDED: 13 s
harfbuzz:x64-windows: SUCCEEDED: 1.7 min
libogg:x64-windows: SUCCEEDED: 15 s
libflac:x64-windows: SUCCEEDED: 18 s
libvorbis:x64-windows: SUCCEEDED: 8.4 s
protobuf:x64-windows: SUCCEEDED: 5.2 min
onnx:x64-windows: SUCCEEDED: 1.8 min
onnx-optimizer:x64-windows: SUCCEEDED: 26 s
opencv4:x64-windows: SUCCEEDED: 8.4 min
opencv:x64-windows: SUCCEEDED: 217 ms
openexr:x64-windows: SUCCEEDED: 47 s
openvdb:x64-windows: SUCCEEDED: 1.3 min
physx:x64-windows: SUCCEEDED: 3.1 min
qt5-base:x64-windows: SUCCEEDED: 15 min
qt5-activeqt:x64-windows: SUCCEEDED: 1.2 min
qt5-imageformats:x64-windows: SUCCEEDED: 14 s
qt5-svg:x64-windows: SUCCEEDED: 23 s
qt5-declarative:x64-windows: SUCCEEDED: 22 min
qt5-multimedia:x64-windows: SUCCEEDED: 2.7 min
qt5-networkauth:x64-windows: SUCCEEDED: 14 s
qt5-graphicaleffects:x64-windows: SUCCEEDED: 15 s
qt5-quickcontrols:x64-windows: SUCCEEDED: 1.3 min
qt5-quickcontrols2:x64-windows: SUCCEEDED: 3.2 min
qt5-tools:x64-windows: SUCCEEDED: 4.7 min
qt5-translations:x64-windows: SUCCEEDED: 29 s
qt5-websockets:x64-windows: SUCCEEDED: 23 s
qt5:x64-windows: SUCCEEDED: 178 ms
qt5-charts:x64-windows: SUCCEEDED: 1.5 min
sfml:x64-windows: SUCCEEDED: 42 s
vulkan-headers:x64-windows: SUCCEEDED: 6.3 s
vulkan-loader:x64-windows: SUCCEEDED: 11 s
vulkan:x64-windows: SUCCEEDED: 2.1 s)"};

    std::string line;
    std::vector<std::pair<std::string,double>> time_usage;
    while(std::getline(ssm,line)){
        if(line.find("REMOVED")!=std::string::npos){
            continue;
        }
        size_t first_colon=line.find_first_of(':');
        size_t second_colon=line.find_first_of(':',first_colon+1);
        size_t third_colon=line.find_first_of(':',second_colon+1);

        std::string package{line.substr(0,first_colon)};
        std::string arch{line.substr(first_colon+1,second_colon-(first_colon+1))};
        std::string time_str{line.substr(third_colon+std::string{": "}.size())};
        size_t space=time_str.find(' ');
        std::string unit{time_str.substr(space+1)};
        double time=std::stod(time_str.substr(0,space));
        if(unit=="min"){
            time*=60*1000;
        }else if(unit=="s"){
            time*=1000;
        }
        time_usage.push_back({package,time});
    }

    std::sort(time_usage.begin(),time_usage.end(),[](std::pair<std::string,double>& a,std::pair<std::string,double>& b){
        return a.second>b.second;
    });

    std::ofstream out{"data.dat"};
    for(const auto& [k,v]:time_usage){
        out<<std::format("{} {}\n",k,v);
    }
    out.close();

    out.open("plot.gp");
    out<<"set terminal wxt size 1500,800 enhanced font 'Microsoft YaHei'\n";
    out<<"set title 'time usage'\n";
    out<<"set xlabel 'package'\n";
    out<<"set ylabel 'time'\n";
    out<<"set style fill solid\n";
    out<<"set boxwidth 0.7 relative\n";
    out<<"set xtics rotate by -90\n";
    out<<"plot 'data.dat' using 0:2:xtic(1) with boxes lc rgb '#1e90ff' notitle\n";
    out.close();

    std::system("gnuplot --persist plot.gp");
}