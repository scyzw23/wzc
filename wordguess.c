#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>  // 包含 isalpha

// 判断一个字符串是否只包含字母
int is_valid_word(const char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalpha(word[i])) {  // 如果不是字母
            return 0;  // 返回 false
        }
    }
    return 1;  // 如果所有字符都是字母，返回 true
}

int main(){
    int flag[10];
    int choice;
    int live,sit=0;
    int sum;//记录猜对了几个数
    char guess[10],chosen[10];
    char arr[100][10];
    int length;

    FILE *file = fopen("/usr/share/dict/words", "r");
    int wordnumber=0;
    char word[50];
    if (file == NULL) {
        printf("错误：无法打开字典文件。\n");
        return 1;
    }
    while(fgets(word,50,file)){
        word[strcspn(word, "\n")] = 0; // 去掉换行符
        if (strlen(word)<10||is_valid_word(word)){
            strcpy(arr[wordnumber],word);
            wordnumber++;
        }
        if (wordnumber>=100){
            break;
        }
    }
    fclose(file);

    srand(time(NULL));

    initial:
    live=10;
    choice=rand()%100; //choice=0-99
    sum=0;
    strcpy(chosen,arr[choice]);//猜的词放在chosen
    length=strlen(chosen); //选中的词的长度
    for (int i=0;i<length;i++){
        flag[i]=0;
    }
    
    while (live!=0){
        printf("Word: ");
        for (int i=0; i<length;i++){
            if (flag[i]!=1){
                printf("_ ");
            }
            else {
                printf("%c",chosen[i]);
            }
        }
        printf("\n");
        printf("Guess (%d lives): \n",live);
            scanf("%s",guess);//输入猜的字符或单词
        if (strlen(guess)==1){  //输入一个字符
            for (int i=0; i<length;i++){
                if (guess[0]==chosen[i]){//找到对应的字符
                    if (flag[i]==0){
                        flag[i]=1;
                        sum++;                   
                        sit=1; //有找到对应字符
                    }
                }
            }           
        }
        else{            //输入字符串
            if (!strcmp(guess,chosen)){
                sit=1;
                sum=length;
            }
        }
        if (sit==0){//一个对应的字符或整个字符串没找到
                live--;
            }
        if (sum==length){
            printf("succeed  %s\n\n",chosen);
            sit=0;
            goto initial;
        }
        sit=0;

    }
    printf("unsuccessful\n");
    printf("answer is %s\n\n",chosen);
    goto initial;

    return 0;
}