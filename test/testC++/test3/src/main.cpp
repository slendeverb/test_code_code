#include "header.h"
#include <bits/stdc++.h>

class BookMyShow{
public:
    BookMyShow(int n,int m){

    }

    std::vector<int> gather(int k,int maxRow){

    }

    bool scatter(int k,int maxRow){

    }
};

int main(int argc,char** argv){
    cv::Mat img=cv::imread("C:\\Users\\slendeverb\\Pictures\\Saved Pictures\\117541346_p0_master1200.jpg");
    cv::imshow("show",img);
    cv::waitKey(3000);

    torch::Tensor tensor=torch::rand({10,10});
    if(torch::cuda::is_available()){
        std::cout<<"CUDA is available! Training on GPU!\n";
        auto tensor_cuda=tensor.cuda();
        std::cout<<tensor_cuda<<"\n";
    }
    else{
        std::cout<<"CUDA is not available! Traning on CPU!\n";
        std::cout<<tensor<<"\n";
    }
}