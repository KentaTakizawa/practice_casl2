#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//構造体の初期化
void init_list(ptr_file *list){
    list->next = NULL;
}