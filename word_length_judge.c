#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//1語長か2語長か判別
int word_length_judge(char *operand1,char *operand2,char *operand3){
    extern CL cl[28];
    extern GR gr[8];
    if (operand3 != NULL){
        return 2;
    }
    int flag = 0;
    for(int m = 0;m < GR_NUMBER;m++){
        if(strcmp(operand1,gr[m].grname)==0){
            flag++;
        }
    }
    for(int n = 0;n < GR_NUMBER;n++){
        if(strcmp(operand2,gr[n].grname)==0){
            flag++;
        }
    }
    if (flag==2){
        return 1;
    }
    else{
        return 2;
    }
}