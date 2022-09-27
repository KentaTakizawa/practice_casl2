#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//リテラルをラベル名として構造体に登録する
void literal(ptr_file *list,int address){
    while(list->next != NULL) {
        list = list->next;
        char *command;
        char *operand1;
        char *operand2;
        char *operand3;
        command = list->command;
        operand1 = list->operand1;
        operand2 = list->operand2;
        operand3 = list->operand3;
        char *str;
        if (command[0]=='='){
            str = literal_str(command);
            addlist(list,address,command,"DC",str,NULL,NULL);
            address++;           
        }
        else if (operand1[0]=='='){
            str = literal_str(operand1);
            addlist(list,address,operand1,"DC",str,NULL,NULL);
            address++; 
        }
        else if (operand2[0]=='='){
            str = literal_str(operand2);
            addlist(list,address,operand2,"DC",str,NULL,NULL);
            address++; 
        }
        else if (operand3[0]=='='){
            str = literal_str(operand3);
            addlist(list,address,operand3,"DC",str,NULL,NULL);
            address++; 
        }
    }
}