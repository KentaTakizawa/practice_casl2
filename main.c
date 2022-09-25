#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"

#define SIZE 256 
#define FALSE 1
#define TRUE 0
#define LIST_NUMBER ((sizeof list)/(sizeof(ptr_file)))

typedef struct PTR_FILE{
    int address;
    char *label;
    char *command;
    char *operand1;
    char *operand2;
    char *operand3;
    struct PTR_FILE *next;
}ptr_file;
//文字列からスペースを消す関数
void removeSpace(char *arr, int n);
void addlist(ptr_file *list,int address,char *label,char *command,char *operand1,char *operand2,char *operand3);
void searchLabel(ptr_file *list);
void init_list(ptr_file *list);
void freememory(ptr_file *list);
int command_literal(ptr_file *list,int address);
int word_length_judge(char *operand1,char *operand2,char *operand3);
char *address_converting_1_word_length(char *command,char *operand1,char *operand2);
char* address_converting_2_word_length(ptr_file *list,char *command,char *operand1,char *operand2,char *operand3);
char *convert_hexadecimal(int address);

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

            removeSpace(ptr[k], strlen(ptr[k]));
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
            if((strcmp(command,"START")!=0)&&(strcmp(command,"END")!=0)){
                addlist(&list,address,label,command,operand1,operand2,operand3);
                len++;
                address++;
            }
            else if(strcmp(command,"START")==0){
                addlist(&list,address,label,command,operand1,operand2,operand3);
                len++;
            }
            else if(strcmp(command,"END")==0){
                address--;
                addlist(&list,address,label,command,operand1,operand2,operand3);
                len++;
                address++;
            }
        }
        else{
            addlist(&list,address,label,command,operand1,operand2,operand3);
            len++;
            address++;
        }
        i++;
    }
    //命令がリテラルの場合
    address =  command_literal(&list,address);

    //命令とコマンドの検索
    searchLabel(&list);
    fclose(fp);
    // メモリの開放
    freememory(&list);

    return TRUE;
}


//文字列からスペースを消す関数
void removeSpace(char *arr, int n)
{
    int space = 0;
    int k = 0;
    //文字列の文字を繰り返し処理
    for (int i = 0; i < n; i++)
    {
        if(space==2){
            arr[i]=' ';
            continue;
        }
        //文字列の先頭のスペースを処理
        while (k == 0 && i < n && arr[i] == ' ') {
            i++;
        }
        //現在の文字がスペースの場合
        if (arr[i] == ' ')
        {
            //フラグが以前に0だった場合、つまり、
            //単語の後のスペース
            if (!space)
            {
                //現在のchar(空白)を次の空きインデックスにコピー
                //そしてフラグを設定します
                arr[k++] = arr[i];
                space = 1;
            }
        }
        //現在の文字が句読点の場合
        else if (ispunct(arr[i]))
        {
            //最後に割り当てられた文字がスペースの場合は、上書き
            //現在の文字で
            if (k > 0 && arr[k-1] == ' ') {
                arr[k-1] = arr[i];
            }
            else {
                //次の空きインデックスで現在の文字をコピー
                arr[k++] = arr[i];
            }
            space = 0;
        }
        //現在の文字が;の場合
        else if(arr[i]==';'){
            arr[i]=' ';
            space=2;
        }
        else {
            //次の空きインデックスで現在の文字をコピー
            arr[k++] = arr[i];
            space = 0;
        }
    }
    arr[k] = '\0';
}

//構造体にデータを格納
void addlist(ptr_file *list,int address,char *label,char *command,char *operand1,char *operand2,char *operand3){
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

//構造体の初期化
void init_list(ptr_file *list){
    list->next = NULL;
}

//リテラルをラベル名として構造体に登録する
int command_literal(ptr_file *list,int address){
    while(list->next != NULL) {
        list = list->next;
        char *command;
        command = list->command;
        if (command[0]=='='){
            //文字列の長さを取得する 
            int len,num;
            char *str;
            len = strlen(command);
            //１文字ずつ数字であるかどうかを判断していく
            int j = 0;
            for (int i = 1; i < len; i++) {
                //command[i]がアスキーコード的に'0'〜'9'の文字であるかを判断
                //イコールの次に小数点がある場合
                if (command[1]=='0'){
                    printf("指定された文字列に数字以外含まれています！\n");
                    return -1;
                }
                if (command[i] < '0' || command[i] > '9') {
                    
                    str[j] = command[i];
                    j++;
                }
                else{
                    str[j] = command[i];
                    j++;
                }
            }
            str[j] = '\0';
            // printf("%s\n",str);
            addlist(list,address,command,"DC",str,NULL,NULL);
            address++;
            
        }
    }
    return address;
}

//命令の検索
void searchLabel(ptr_file *list) {
    while(list->next != NULL) {
        list = list->next;
        char *txt_command;
        // printf("%d %s %s %s %s %s\n" ,list->address,list->label,list->command,list->operand1,list->operand2,list->operand3);
        for(int m = 0;m < CL_NUMBER;m++){
            //ラベル名と対応する構造体を検索
            if(strcmp(list->command,cl[m].command)==0){
                // printf("\n%d %s %s %s %s %s\n" ,list->address,list->label,list->command,list->operand1,list->operand2,list->operand3);
                if(cl[m].command_length==0){
                    printf("アセンブラ命令・マクロ命令です\n");
                }
                else if(cl[m].command_length==1){
                    // printf("1語長の命令です %s\n",cl[m].length1);
                    txt_command = address_converting_1_word_length(list->command,list->operand1,list->operand2);
                    printf("%s",txt_command);
                }
                else if(cl[m].command_length==2){
                    // printf("2語長の命令です %s\n",cl[m].length2);
                    txt_command = address_converting_2_word_length(list,list->command,list->operand1,list->operand2,list->operand3);
                    printf("%s",txt_command);
                }
                else if(cl[m].command_length==3){
                    if(word_length_judge(list->operand1,list->operand2,list->operand3)==1){
                        // printf("1語長の命令です! %s\n",cl[m].length1);
                        txt_command = address_converting_1_word_length(list->command,list->operand1,list->operand2);
                        printf("%s",txt_command);
                    }
                    else if(word_length_judge(list->operand1,list->operand2,list->operand3)==2){
                        // printf("2語長の命令です! %s\n",cl[m].length2);
                        txt_command = address_converting_2_word_length(list,list->command,list->operand1,list->operand2,list->operand3);
                        printf("%s",txt_command);
                    }
                    else{
                        printf("判別エラーです\n");
                    }
                }
                else{
                    printf("定義外の命令です\n");
                }
                // printf("%s %d %s %s\n",cl[m].command,cl[m].command_length,cl[m].length1,cl[m].length2);
            }
        }
    }  
}


// メモリ解放用関数
void freememory(ptr_file *list){
  ptr_file * tmp;

  list = list->next;
  while(list->next != NULL) {
    tmp = list;
    list = tmp->next;

    free(tmp);
  }
}

//1語長か2語長か判別
int word_length_judge(char *operand1,char *operand2,char *operand3){
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

//1語長のアドレス変換
char *address_converting_1_word_length(char *command,char *operand1,char *operand2){
    char address1[2];
    char address2[2];
    char address3[2];
    char address4[2];
    //上位2ビットの決定
    for(int j = 0;j < CL_NUMBER;j++){
        if(strcmp(command,cl[j].command)==0){
            char *cllength = cl[j].length1;
            address1[0] = cllength[0];
            address2[0] = cllength[1];
        }
    }
    //下位2ビットの決定
    int flag = 0;
    for(int k = 0;k < GR_NUMBER;k++){
        if((operand1!=NULL)&&(operand2!=NULL)){
            if(strcmp(operand1,gr[k].grname)==0){
                char *grname1;
                grname1 = gr[k].num;
                address3[0] = grname1[0];
                flag = flag + 1;
            }
            if(strcmp(operand2,gr[k].grname)==0){
                char *grname2;
                grname2 = gr[k].num;
                address4[0] = grname2[0];
                flag = flag + 2;
            }
        }
    }
    //汎用レジスタが2つない場合　命令がRETやPOPの時など
    if(flag == 0){
        address3[0] = '0'; 
        address4[0] = '0'; 
    }
    else if(flag == 1){
        address4[0] = '0'; 
    }
    else if(flag == 2){
        address3[0] = '0';  
    }
    //文字列の最後を決める
    address1[1]='\0';
    address2[1]='\0';
    address3[1]='\0';
    address4[1]='\0';
    //各ビットを結合する
    char address[10];
    strcat(address, address1);
    strcat(address, address2);
    strcat(address, address3);
    strcat(address, address4);
    strcat(address, "\n");
    //受け渡すポインタの作成
    char *address_number = NULL;
    address_number = (char*)malloc(sizeof(char) * 20);
    if (address_number == NULL) {
        printf("配列作成失敗\n");
    }
    strcpy(address_number, address);
    
    return address_number;
}

//2語長のアドレス変換
char* address_converting_2_word_length(ptr_file *list,char *command,char *operand1,char *operand2,char *operand3){
    char address1[2];
    char address2[2];
    char address3[2];
    char address4[2];
    //上位2ビットの決定
    for(int j = 0;j < CL_NUMBER;j++){
        if(strcmp(command,cl[j].command)==0){
            char *cllength = cl[j].length2;
            address1[0] = cllength[0];
            address2[0] = cllength[1];
        }
    }
    //下位2ビットの決定
    int flag = 0;
    int label_flag = 0; //オペランド1がアドレスの時：0 or 2，オペランド2がアドレスの時：1，オペランド3の時にアドレスはないので考慮しない
    for(int k = 0;k < GR_NUMBER;k++){
        if((operand1!=NULL)&&(strcmp(operand1,gr[k].grname)==0)){
            char *grname1;
            grname1 = gr[k].num;
            address3[0] = grname1[0];
            flag = flag + 1;
            label_flag = label_flag + 1;
        }
        if((operand2!=NULL)&&(strcmp(operand2,gr[k].grname)==0)){
            char *grname2;
            grname2 = gr[k].num;
            if(flag==1){
                address4[0] = grname2[0];
                flag = flag + 2;
                label_flag = label_flag + 2;
            }
        }
        if((operand3!=NULL)&&(strcmp(operand3,gr[k].grname)==0)){
            char *grname3;
            grname3 = gr[k].num;
            if(flag==1){
                address4[0] = grname3[0];
                flag = flag + 2;
            }
        }
    }
    //汎用レジスタが2つない場合　命令がRETやPOPの時など
    if(flag == 0){
        address3[0] = '0'; 
        address4[0] = '0'; 
    }
    else if(flag == 1){
        address4[0] = '0'; 
    }
    else if(flag == 2){
        address3[0] = '0';  
    }
    //文字列の最後を決める
    address1[1]='\0';
    address2[1]='\0';
    address3[1]='\0';
    address4[1]='\0';
    //各ビットを結合する
    char address[10];
    strcat(address, address1);
    strcat(address, address2);
    strcat(address, address3);
    strcat(address, address4);
    strcat(address, "\n");
    //受け渡すポインタの作成
    char *address_number = NULL;
    address_number = (char*)malloc(sizeof(char) * 20);
    if (address_number == NULL) {
        printf("配列作成失敗\n");
    }
    strcpy(address_number, address);

    //2行目のアドレスを決定
    char *address_name;
    if ((label_flag==0) || (label_flag==2)){
        address_name=operand1;
    }
    else{
        address_name=operand2;
    }
    //オペランド名が数字の時
    int num;
    char *end;
    num = strtol(address_name, &end, 10);
    if(*end == '\0'){
        address_name = convert_hexadecimal(num);
        address_name[4] ='\0';
        strcat(address_number, address_name);
        strcat(address_number,"\n");
    }
    //オペランド名がラベル名の時
    else{
         while(list->next != NULL) {
            list = list->next;
            if((list->label!=NULL)&&(strcmp(address_name,list->label)==0)){
                printf("\n%s %d\n\n",list->label,list->address);
            }
        }
    }
    return address_number;
}

//16進数に変換
char *convert_hexadecimal(int address){
    char hexadecimal[16] = "0123456789ABCDEF";
    char hexadecimal_list[5];
    int j=0;
    //上位ビットから格納
    for(int i=3;i>=0;i--){
        j = address % 16;
        address = address / 16;
        hexadecimal_list[i] = hexadecimal[j];
    }
    hexadecimal_list[4] = '\0';

    //保存アドレス
    char *address_number = NULL;
    address_number = (char*)malloc(sizeof(char) * 5);
    if (address_number == NULL) {
        printf("配列作成失敗\n");
    }
    strcpy(address_number, hexadecimal_list);
    
    return address_number;
}


