#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define SIZE 256 
#define FALSE 1
#define TRUE 0
#define LIST_NUMBER ((sizeof g)/(sizeof(ptr_file)))

typedef struct PTR_FILE{
    int address;
    char *label;
    char *operand1;
    char *operand2;
    char *operand3;
}ptr_file;

typedef struct LABEL_ADDRESS{
    int address;
    char *label;
}label_address;

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
    ptr_file g[count];
    int i = 0;
    int len=0;
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
        while((ptr[k]=strtok(NULL," "))!=NULL){
            k++;
            num++;
        }

        //構造体にデータを格納
        int address;
        char *label;
        char *operand1;
        char *operand2;
        char *operand3;
        address = len;
        label = ptr[0];
        operand1 = ptr[1];
        operand2 = ptr[2];
        operand3 = ptr[3];
        //オペランド1が START,ENDではないとき，構造体に登録
        if (operand1!=NULL){
            if((strcmp(operand1,"START")!=0)&&(strcmp(operand1,"END")!=0)){
                ptr_file  add = {address,label,operand1,operand2,operand3};
                g[len] = add;
                len++;
            }
        }
        else{
            ptr_file  add = {address,label,operand1,operand2,operand3};
            g[len] = add;
            len++;
        }
        i++;
    }
    ptr_file *p = g;

    //ラベル名とアドレスの構造体を作成する
    label_address la[count];
    int num = 0;
    for (int l = 0; l < len; l++) {
        if(p->label!=NULL){
            label_address add = {p->address,p->label};
            la[num] = add;
            num++;
        }
        p++;
    }
    label_address *pla = la;
    for(int l = 0; l < num;l++){
        printf("%04X %s\n",pla->address,pla->label);
        pla++;
    }

    fclose(fp);
    return TRUE;
}