#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"


//1語長のアドレス変換
char *address_converting_1_word_length(char *command,char *operand1,char *operand2){
    char address1[2];
    char address2[2];
    char address3[2];
    char address4[2];
    extern CL cl[28];
    extern GR gr[8];
    //上位2ビットの決定
    for(int j = 0;j < CL_NUMBER;j++){
        if(strcmp(command,cl[j].command)==0){
            char *cllength = cl[j].length1;
            address1[0] = cllength[0];
            address2[0] = cllength[1];
        }
    }
    //下位2ビットの決定
    int flag = 0;
    for(int k = 0;k < GR_NUMBER;k++){
        if((operand1!=NULL)&&(operand2!=NULL)){
            if(strcmp(operand1,gr[k].grname)==0){
                char *grname1;
                grname1 = gr[k].num;
                address3[0] = grname1[0];
                flag = flag + 1;
            }
            if(strcmp(operand2,gr[k].grname)==0){
                char *grname2;
                grname2 = gr[k].num;
                address4[0] = grname2[0];
                flag = flag + 2;
            }
        }
    }
    //汎用レジスタが2つない場合　命令がRETやPOPの時など
    if(flag == 0){
        address3[0] = '0'; 
        address4[0] = '0'; 
    }
    else if(flag == 1){
        address4[0] = '0'; 
    }
    else if(flag == 2){
        address3[0] = '0';  
    }
    //文字列の最後を決める
    address1[1]='\0';
    address2[1]='\0';
    address3[1]='\0';
    address4[1]='\0';
    //各ビットを結合する
    char address[10];
    strcat(address, address1);
    strcat(address, address2);
    strcat(address, address3);
    strcat(address, address4);
    strcat(address, "\n");
    //受け渡すポインタの作成
    char *address_number = NULL;
    address_number = (char*)malloc(sizeof(char) * 20);
    if (address_number == NULL) {
        printf("配列作成失敗\n");
    }
    strcpy(address_number, address);
    
    return address_number;
}