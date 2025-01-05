#include<stdio.h>
#include<string.h>

int main(){
    FILE* p;
    int flag=0,len,i=0,j=0;
    char* rwtab[27]={"","main","if","then","while","do",
                    "static","int","double","struct","break","else","long",
                    "switch","case","typedef","char","return","const","float",
                    "short","continue","for","void","sizeof","default","do"};// 26个
    char str[1000],str1[1000],c;
    int syn,num;
    int k;
    char token[200];
    if((p=fopen("./test1.txt","rt"))==NULL){
        
    }
}