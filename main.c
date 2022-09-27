#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

#define LIST_NUMBER ((sizeof list)/(sizeof(ptr_file)))

int main(void){
    //ファイルの読み込み
    FILE *fp;
    //ファイル名の入力
    // char filename[SIZE];
    // printf("File>");
    // fgets(filename,SIZE,stdin);
    char *filename;
    filename = "sample.cas";
    //改行文字の削除
    strtok(filename,"\n");
    //ファイルを開く
    fp = fopen(filename,"r+");
    if(fp == NULL){
    printf("%sのファイルは見つかりませんでした",filename);
    return FALSE;
    }
    //行数を読み込む
    int count;
    char len_str[SIZE];
    while(fgets(len_str,SIZE,fp) != NULL){
        count++;
    }
    fclose(fp);

    fp = fopen(filename,"r");
    char str[100][SIZE];
    ptr_file list;
    init_list(&list);
    int i = 0;
    int len=0;
    int address = 0;
    while(fgets(str[i],SIZE,fp)!=NULL){
        int j = 0;
        int num = 0;
        
        //保存データの初期化
        char *ptr[SIZE];
        ptr[0] = NULL;
        ptr[1] = NULL;
        ptr[2] = NULL;
        ptr[3] = NULL;
        ptr[4] = NULL;
        ptr[5] = NULL;
        int k = 0;

        //空行だったら次へ
        if(strcmp(str[i],"\n")==0){
            continue;
        }
        //1文字目が空白か確認する
        if (str[i][j]==' '){
            k++;
            num++;
        }
        //改行文字の削除
        strtok(str[i],"\n");

        //スペースで分割する
        ptr[k] = strtok(str[i]," ");
        k++;
        num++;
        while(1){
            if(k<2){
                if((ptr[k]=strtok(NULL," "))==NULL){
                    break;
                }
            }
            else{
                if((ptr[k]=strtok(NULL,","))==NULL){
                    break;
                }
            }

            remove_space(ptr[k], strlen(ptr[k]));
            if(ptr[k][0]==';'){
                ptr[k]=NULL;
                break;
            }
            k++;
            num++;
        }
        
        //構造体にデータを格納
        char *label;
        char *command;
        char *operand1;
        char *operand2;
        char *operand3;
    
        label = ptr[0];
        command = ptr[1];
        operand1 = ptr[2];
        operand2 = ptr[3];
        operand3 = ptr[4];
        //コメントを削除
        strtok(label,";");
        strtok(command,";");
        strtok(operand1,";");
        strtok(operand2,";");
        strtok(operand3,";");
        //オペランド1が START,ENDではないとき，構造体に登録
        if (command!=NULL){
            if((strcmp(command,"START")!=0)&&(strcmp(command,"END")!=0)&&(strcmp(command,"DC")!=0)){
                add_list(&list,address,label,command,operand1,operand2,operand3);
                len++;
                address++;
            }
            else if(strcmp(command,"START")==0){
                if(operand1==NULL){
                    add_list(&list,address,label,command,operand1,operand2,operand3);
                    len++;
                }
                else{
                    add_list(&list,address,label,command,operand1,operand2,operand3);
                    len++;
                    address++;
                }              
            }
            else if(strcmp(command,"END")==0){
                address--;
                add_list(&list,address,label,command,operand1,operand2,operand3);
                len++;
                address++;
            }
            else if(strcmp(command,"DC")==0){
                int DC_num;
                char *end;
                DC_num = strtol(operand1,&end,10);
                if(*end == '\0'){
                    int dc_num=0;
                    while(1){
                        if(dc_num < DC_num){
                            address++;
                            dc_num++;
                        }
                        else{
                            break;
                        }
                    }
                }
                else{
                    printf("数値を記入してください\n");
                }
            }
        }
        else{
            add_list(&list,address,label,command,operand1,operand2,operand3);
            len++;
            address++;
        }
        i++;
    }
    //命令がリテラルの場合
    literal(&list,address);

    //命令とコマンドの検索
    char *txt_list;
    txt_list = search_label(&list);
    printf("%s",txt_list);
    fclose(fp);
    // メモリの開放
    free_memory(&list);

    return TRUE;
}



