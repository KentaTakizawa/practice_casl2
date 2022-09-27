#ifndef DATA_H //二重でincludeされることを防ぐ
#define DATA_H

#define CL_NUMBER 28
#define GR_NUMBER 8

typedef struct comand_list{
    char *command;
    int command_length; //1語長のみ:1，2語長のみ:2，両方:3，アセンブラ命令・マクロ命令:0
    char *length1;
    char *length2;
}CL;

typedef struct general_register{
    char *grname; //汎用レジスタ名
    char num[1]; //対応するビットの値
}GR;

typedef struct PTR_FILE{
    int address;
    char *label;
    char *command;
    char *operand1;
    char *operand2;
    char *operand3;
    struct PTR_FILE *next;
}ptr_file;
#endif