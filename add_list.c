#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//構造体にデータを格納
void add_list(ptr_file *list,int address,char *label,char *command,char *operand1,char *operand2,char *operand3){
    
    ptr_file *new;
    new = (ptr_file *)malloc(sizeof (ptr_file));

    new->address=address;
    new->label=label;
    new->command=command;
    new->operand1=operand1;
    new->operand2=operand2;
    new->operand3=operand3;

    new->next=NULL;
    while(list->next!=NULL) {
    list = list->next;
  }
  list->next = new;
}