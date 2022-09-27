#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

// メモリ解放用関数
void free_memory(ptr_file *list){
  ptr_file * tmp;

  list = list->next;
  while(list->next != NULL) {
    tmp = list;
    list = tmp->next;

    free(tmp);
  }
}