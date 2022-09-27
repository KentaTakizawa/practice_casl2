#ifndef FUNCTION_LIST_H //二重でincludeされることを防ぐ
#define FUNCTION_LIST_H

void remove_space(char *arr, int n);
void add_list(ptr_file *list,int address,char *label,char *command,char *operand1,char *operand2,char *operand3);
char *search_label(ptr_file *list);
void init_list(ptr_file *list);
void literal(ptr_file *list,int address);
int word_length_judge(char *operand1,char *operand2,char *operand3);
char *address_converting_1_word_length(char *command,char *operand1,char *operand2);
char *address_converting_2_word_length(ptr_file *list,char *command,char *operand1,char *operand2,char *operand3);
void free_memory(ptr_file *list);
char *literal_str(char *literal);

#endif