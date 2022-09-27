#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "data.h"
#include "function_list.h"
#include "define_data.h"

//文字列からスペースを消す関数
void remove_space(char *arr, int n)
{
    int space = 0;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if(space==2){
            arr[i]=' ';
            continue;
        }
        while (k == 0 && i < n && arr[i] == ' ') {
            i++;
        }
        if (arr[i] == ' ')
        {
            if (!space)
            {
                arr[k++] = arr[i];
                space = 1;
            }
        }
        else if (ispunct(arr[i]))
        {
            if (k > 0 && arr[k-1] == ' ') {
                arr[k-1] = arr[i];
            }
            else {
                arr[k++] = arr[i];
            }
            space = 0;
        }
        else if(arr[i]==';'){
            arr[i]=' ';
            space=2;
        }
        else {
            arr[k++] = arr[i];
            space = 0;
        }
    }
    arr[k] = '\0';
}