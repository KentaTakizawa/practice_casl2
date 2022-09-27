#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"


//16進数に変換
char *convert_hexadecimal(int address){
    char hexadecimal[16] = "0123456789ABCDEF";
    char hexadecimal_list[5];
    if(address<0){
        address=address+8*16*16*16*16;
    }
    int j=0;
    //上位ビットから格納
    for(int i=3;i>=0;i--){
        j = address % 16;
        address = address / 16;
        hexadecimal_list[i] = hexadecimal[j];
    }
    hexadecimal_list[4] = '\0';

    //保存アドレス
    char *address_number = NULL;
    address_number = (char*)malloc(sizeof(char) * 5);
    if (address_number == NULL) {
        printf("配列作成失敗\n");
    }
    strcpy(address_number, hexadecimal_list);
    
    return address_number;
}