#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//命令の検索
char *search_label(ptr_file *list) {
    extern CL cl[28];
    extern GR gr[8];
    char *txt_list=NULL;
    txt_list= (char*)malloc(sizeof(char) * 500);
    if (txt_list == NULL) {
        printf("配列作成失敗\n");
    }
    else{
        while(list->next != NULL) {
            list = list->next;
            char *txt_command;
            for(int m = 0;m < CL_NUMBER;m++){
                //ラベル名と対応する構造体を検索
                if(strcmp(list->command,cl[m].command)==0){
                    if(cl[m].command_length==0){
                        // printf("アセンブラ命令・マクロ命令です\n");
                    }
                    else if(cl[m].command_length==1){
                        txt_command = address_converting_1_word_length(list->command,list->operand1,list->operand2);
                        strcat(txt_list, txt_command);
                    }
                    else if(cl[m].command_length==2){
                        txt_command = address_converting_2_word_length(list,list->command,list->operand1,list->operand2,list->operand3);
                        strcat(txt_list, txt_command);
                    }
                    else if(cl[m].command_length==3){
                        if(word_length_judge(list->operand1,list->operand2,list->operand3)==1){
                            txt_command = address_converting_1_word_length(list->command,list->operand1,list->operand2);
                            strcat(txt_list, txt_command);
                        }
                        else if(word_length_judge(list->operand1,list->operand2,list->operand3)==2){
                            txt_command = address_converting_2_word_length(list,list->command,list->operand1,list->operand2,list->operand3);
                            strcat(txt_list, txt_command);
                        }
                        else{
                            printf("判別エラーです\n");
                        }
                    }
                    else{
                        printf("定義外の命令です\n");
                    }
                }
            }
        }
    }
    return txt_list;
}