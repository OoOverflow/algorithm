/*************************************************************************
	> File Name: test_bt.c
	> Author: sean
	> Mail: sean.zhao@sctech.com.cn
	> Created Time: Thu 17 Mar 2016 01:47:05 AM HKT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"binary_tree_op.h"

int main()
{
        int bt_index;
        int pos;
        int flag;
        int ret;
        int res;

        int expr[13] = {
                '+','*',7,'+',
                6,'*',5,4,
                '+','*',3,2,1,
        };

        bt_index = bt_create(expr[0],1);

        for (pos = 1;pos < 13;pos++) {
                switch(expr[pos]){
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                                flag = 1;
                                break;
                        default:
                                flag = 0;
                                break;
                }

                printf("exer[%d]:%d\n",pos,expr[pos]);
                ret = bt_insert(bt_index,expr[pos],flag);
        }

        bt_read_all_unit(bt_index);

        bt_read_all(bt_index,&res);
        printf("res:%d\n",res);

        return 0;


}
