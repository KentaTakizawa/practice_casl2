#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

CL cl[]={
    {"NOP",1,"00","XX"},
    {"LD",3,"14","10"},
    {"ST",2,"XX","11"},
    {"LAD",2,"XX","12"},
    {"ADDA",3,"24","20"},
    {"SUBA",3,"25","21"},
    {"ADDL",3,"26","22"},
    {"SUBL",3,"27","23"},
    {"AND",3,"34","30"},
    {"OP",3,"35","31"},
    {"XOR",3,"36","32"},
    {"CPA",3,"44","40"},
    {"CPL",3,"45","41"},
    {"SLA",2,"XX","50"},
    {"SRA",2,"XX","51"},
    {"SLL",2,"XX","52"},
    {"SRL",2,"XX","53"},
    {"JMI",2,"XX","61"},
    {"JNZ",2,"XX","62"},
    {"JZE",2,"XX","63"},
    {"JUMP",2,"XX","64"},
    {"JPL",2,"XX","65"},
    {"JOV",2,"XX","66"},
    {"PUSH",2,"XX","70"},
    {"POP",1,"71","XX"},
    {"CALL",2,"XX","80"},
    {"RET",1,"81","XX"},
    {"SVC",2,"XX","F0"},
};


GR gr[8]={
    {"GR0","0"},
    {"GR1","1"},
    {"GR2","2"},
    {"GR3","3"},
    {"GR4","4"},
    {"GR5","5"},
    {"GR6","6"},
    {"GR7","7"},
};