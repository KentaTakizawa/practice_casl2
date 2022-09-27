#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

char *literal_str(char *literal){
    //文字列の長さを取得する 
    int len;
    char *str;
    len = strlen(literal);
    //１文字ずつ数字であるかどうかを判断していく
    int j = 0;
    for (int i = 1; i < len; i++) {
        if (literal[1]=='0'){
            printf("指定された文字列に数字以外含まれています！\n");
            return -1;
        }
        if (literal[i] < '0' || literal[i] > '9') {
            str[j] = literal[i];
            j++;
        }
        else{
            str[j] = literal[i];
            j++;
        }
    }
    str[j] = '\0';
    return str;
}