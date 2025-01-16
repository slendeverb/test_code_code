#include<stdio.h>
#include<string.h>
#include<ctype.h>

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
    if((p=fopen("C:\\Users\\slendeverb\\Documents\\code_code\\test\\testC\\test2\\src\\test1.txt","rt"))==NULL){
        printf("无法打开test1.txt");
        return 0;
    }
    while((c=getc(p))!=EOF){
        str[i++]=c;
    }
    fclose(p);
    if((p=fopen("C:\\Users\\slendeverb\\Documents\\code_code\\test\\testC\\test2\\src\\test2.txt","w"))==NULL){
        printf("无法打开test2.txt");
        return 0;
    }
    str[i]='\0';
    for(i=0;str[i]!='\0';){
        j=0;
        num=-1;
        if(isalpha(str[i])){
            while(isalnum(str[i])||str[i]=='_'){
                token[j++]=str[i++];
            }
            token[j]='\0';
            for(k=1;k<27;k++){
                if(strcmp(rwtab[k],token)==0){
                    break;
                }
            }
            if(k<25){
                syn=k;
            }else if(k==25){
                syn=39;
            }else if(k==26){
                syn=40;
            }else{
                syn=25;
            }
        }// 关键字和标识符处理
        else if(isdigit(str[i])){
            num=0;
            while(isdigit(str[i])){// 当读到第一个为0~9的数字时接着读之后的数字
                num=num*10+str[i]-'0';
                token[j++]=str[i++];
            }
            if(isalpha(str[i])){
                num=-1;syn=-3;
                while(isalnum(str[i])){
                    token[j++]=str[i++];
                }
            }else {
                syn=26;
            }
        }// 数字在此处理
        else {
            if(str[i]==':' && str[i+1]=='='){
                syn=32;
                token[j++]=str[i];
                token[j++]=str[++i];
                i++;
            }else if(str[i]=='<'&& str[i+1]=='>'){
                syn=34;
                token[j++]=str[i];
                token[j++]=str[++i];
                i++;
            }else if(str[i]=='<'&&str[i+1]=='='){
                syn=35;
                token[j++]=str[i];
                token[j++]=str[++i];
                i++;
            }else if(str[i]=='>'&& str[i+1]=='='){
                syn=36;
                token[j++]=str[i];
                token[j++]=str[++i];
                i++;
            }else if(str[i]==' '){
                i++;
                syn=-2;
            }// 空格处理
            else{
                switch(str[i]){
                    case '+': 
                        syn=27;
                        break;
                    case '-':
                        syn=28;
                        break;
                    case '*':
                        syn=29;
                        break;
                    case '/':
                        syn=30;
                        break;
                    case ':':
                        syn=31;
                        break;
                    case '<':
                        syn=33;
                        break;
                    case '>':
                        syn=36;
                        break;
                    case ';':
                        syn=41;
                        break;
                    case ')':
                        syn=43;
                        break;
                    case '(':
                        syn=42;
                        break;
                    case '#':
                        syn=0;
                        break;
                    case '=':
                        syn=38;
                        break;
                    default:
                        syn=-1;
                        break;
                }
                token[j++]=str[i++];
            }
        }
        token[j]='\0';
        if(num!=-1){
            printf("%d %d\n",num,syn);
        }
        else if(syn!=-1&&syn!=-2&&syn!=-3){
            printf("%s %d\n",token,syn);
        }
        else if(syn==-1){
            printf("%s error\n",token);
        }else if(syn==-3){
            printf("%s error ID\n",token);
        }
    }
    fclose(p);
    return 0;
}