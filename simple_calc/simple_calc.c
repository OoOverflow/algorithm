/*************************************************************************
	> File Name: simple_calc.c
	> Author: sean
	> Mail: sean.zhao@sctech.com.cn
	> Created Time: Tue 15 Mar 2016 11:14:48 PM CST
 ************************************************************************/
/*
 * simple_calc.c
 *
 * This file make a simple calculator
 *
 * we use two stack ,one named argu-stack,another named 
 * op-stack.
 *  
 * At first,we use a loop to push the argument in the 
 * expression to the argu-stack.In the loop,if we find
 * an operator,check the op-stack,pop the top one 
 * if has a higher priority to the argu-stack,then push the 
 * new operator to op-stack.
 *
 * End of the loop, we changed the infix-expression to a 
 * suffix-expression.
 * 
 * Next,we pop the argu-stack and build a expression-tree.
 *
 * At last,we read the expression-tree and calculate the 
 * result
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"stack_op.h"

#define MAX_EXPR_LENGTH         512

int char2int(char *start,int length)
{
        int pos;
        int sum;

        for (pos = 0,sum = 0;pos < length;pos++) {
                sum *= 10;
                sum += start[pos] - '0';
        }

        return sum;
}

int op_level_judge(char op)
{
        switch(op){
                case '+':
                case '-':
                return 0;
                case '*':
                case '/':
                return 1;
                default:
                return -1;
        } 
}

int compare_op(const char cur_op,const char previou_op)
{
        int cur_level;
        int previou_level;

        printf("cur op:%c\tprev op:%c\n",cur_op,previou_op);

        cur_level = op_level_judge(cur_op);
        previou_level = op_level_judge(previou_op);

        if (cur_level > previou_level) {
                return 1;
        }else if (cur_level < previou_level) {
                return -1;
        }else{
                return 0;
        }
}

int str2intarry(char *str,int argu_stack,int op_stack)
{
        int pos;
        char *start_pos = NULL;
        int changed_pos = 0;
        int res;
        int ret;
        int previou_op = 1;
        int str_len;

        str_len = strlen(str);

        for (pos = 0;pos < str_len;pos++) {
                if (!(str[pos] > ('0' - 1)) && (str[pos] < ('9' + 1))) {
                        if (start_pos) {
                                push(argu_stack,char2int(start_pos,(pos - changed_pos)));
                                start_pos = NULL;
                                changed_pos = 0;
                        }

                        if (previou_op == 1) {
                                printf("------\n");
                                previou_op = str[pos];
                                push(op_stack,previou_op);
                                printf("------\n");
                                continue;
                        }

                        if (str[pos] == 40) {
                                printf("********cur pos:%c\n",str[pos]);
                                push(op_stack,str[pos]);
                                previou_op = 1;
                                printf("******************\n");
                                continue;
                        }

                        if (str[pos] == 41) {
                                printf("********cur pos:%c\n",str[pos]);
                                while(previou_op != 40){
                                        pop(op_stack,&previou_op);
                                        push(argu_stack,previou_op);
                                        ret = pop(op_stack,&previou_op);
                                        if (ret < 0) {
                                                printf("empty stack\n");
                                                break;
                                        }
                                }
                                pop(op_stack,&previou_op);
                                push(op_stack,previou_op);
                                printf("******************\n");
                                continue;
                        }

                        ret = 0;
                        while(ret != 1){
                                ret = compare_op(str[pos],previou_op);
                                printf("compare ret:%d\n",ret);
                                switch(ret){
                                        case 1:
                                        push(op_stack,str[pos]);
                                        previou_op = str[pos];
                                        break;

                                        case 0:
                                        pop(op_stack,&previou_op);
                                        push(argu_stack,previou_op);
                                        push(op_stack,str[pos]);
                                        previou_op = str[pos];
                                        ret = 1;
                                        break;
                                        case -1:
                                        pop(op_stack,&previou_op);
                                        push(argu_stack,previou_op);
                                        if (pop(op_stack,&previou_op) < 0) {
                                                ret = 1;
                                        }
                                        if (previou_op == 40) {
                                                push(op_stack,previou_op);
                                                push(op_stack,str[pos]);
                                                previou_op = str[pos];
                                                ret = 1;
                                        }
                                        break;

                                        default:
                                        printf("default\n");
                                        break;
                                }
                        }
                        continue;
                }else{
                        if (start_pos == NULL) {
                                start_pos = &str[pos];
                                changed_pos = pos;
                        }
                }
        }

        if (start_pos != NULL) {
                push(argu_stack,char2int(start_pos,(str_len - changed_pos)));
                while(previou_op){
                        ret = pop(op_stack,&previou_op);

                        if (ret < 0) {
                                printf("empty stack\n");
                                break;
                        }
                        if (previou_op == 40){
                                continue;
                        }

                        push(argu_stack,previou_op);
                }
        }

}

int main()
{
        char expr[] = "1+2*3+(4*5+6)*7";

        int pos;
        int res = 0;
        int bt_index;
        int data;

        int argu_stack;
        int op_stack;

        argu_stack = stack_init();
        op_stack = stack_init();

        printf("%s\n",expr);

        str2intarry(expr,argu_stack,op_stack);

        res = pop(argu_stack,&data);
        if (res < 0){
                return -1;
        }

        if (op_level_judge(data) < 0) {
                bt_index = bt_create(data,0);
        }else{
                bt_index = bt_create(data,1);
        }

        while(!(res < 0)){
                res = pop(argu_stack,&data);
                if (op_level_judge(data) < 0) {
                        ret = bt_insert(bt_index,data,0);
                }else{
                        ret = bt_insert(bt_index,data,1);
                }
        }

        bt_read_all_unit(bt_index);

        bt_read_all(bt_index,&res);
        printf("res:%d\n",res);


        return 0;



}



