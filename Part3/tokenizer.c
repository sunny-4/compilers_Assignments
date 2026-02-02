#include<stdio.h>
#include<string.h>
int isDigit(char ch){
    if(ch>='0' && ch<='9') return 1;
    return 0;
}
int islandnum(char ch){
    if((ch>='0' && ch<='9') || (ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) return 1;
    return 0;
}
int main(){
    FILE *file=stdin;
    char ch;
    while((ch=fgetc(file))!=EOF){
        if(ch==' '|| ch=='\n'|| ch=='\t'){
            continue;
        }else if(ch=='+'|| ch=='-'|| ch=='*'||ch=='/'||ch=='='){
            printf("<OPERATOR, %c>\n",ch);
        }else if(ch=='('|| ch==')'|| ch=='{'||ch=='}'||ch==';'||ch==','){
            printf("<PUNCTUATION, %c>\n",ch);
        }else if(isDigit(ch)){
            char num[256];
            int i=0;
            while(isDigit(ch)){
                num[i++]=ch;
                ch=fgetc(file);
            }
            num[i]='\0';
            printf("<NUMBER, %s>\n",num);
            ungetc(ch,file);
        }else if(islandnum(ch)){
            char id[256];
            int i=0;
            while(islandnum(ch) || ch=='_'){
                id[i++]=ch;
                ch=fgetc(file);
            }
            id[i]='\0';
            int isKeyword = 0;
            int len = strlen(id);

            if (len == 3 &&
                id[0]=='i' && id[1]=='n' && id[2]=='t') {
                isKeyword = 1;
            }

            else if (len == 6 &&
                id[0]=='r' && id[1]=='e' && id[2]=='t' &&
                id[3]=='u' && id[4]=='r' && id[5]=='n') {
                isKeyword = 1;
            }

            else if (len == 2 &&
                id[0]=='i' && id[1]=='f') {
                isKeyword = 1;
            }


            else if (len == 4 &&
                id[0]=='e' && id[1]=='l' && id[2]=='s' && id[3]=='e') {
                isKeyword = 1;
            }

            else if (len == 5 &&
                id[0]=='w' && id[1]=='h' && id[2]=='i' &&
                id[3]=='l' && id[4]=='e') {
                isKeyword = 1;
            }
            else if (len == 5 &&
                id[0]=='f' && id[1]=='l' && id[2]=='o' &&
                id[3]=='a' && id[4]=='t') {
                isKeyword = 1;
            }

            
            else if (len == 4 &&
                id[0]=='c' && id[1]=='h' && id[2]=='a' && id[3]=='r') {
                isKeyword = 1;
            }

            if (isKeyword) {
                printf("<KEYWORD, %s>\n", id);
            }
            else{
                printf("<IDENTIFIER, %s>\n",id);
            }
            ungetc(ch,file);
        }
        else{
            printf("<UNKNOWN, %c>\n",ch);
        }
    }
    return 0;
}