#ifndef DATA_H //二重でincludeされることを防ぐ
#define DATA_H

#define WL_NUMBER ((sizeof wl)/(sizeof(WL)))


typedef struct word_length{
    char *command;
    int command_length; //1語長のみ:1，2語長のみ:2，両方:3
    int length1;
    int length2;
}WL;

WL wl[8]={
    {"LD",3,1400,1000},
    {"ST",2,0,1100},
    {"LAD",2,0,1200},
    {"ADDA",3,2400,2000},
    {"SUBA",3,2100,2500},
    {"ADDL",3,2200,2600},
    {"SUBL",3,2300,2700},
    {"RET",1,81,0},
};

#endif