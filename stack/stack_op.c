/*************************************************************************
	> File Name: stack_op.c
	> Author: sean
	> Mail: freeflyzx@gmail.com
	> Created Time: Mon 14 Mar 2016 11:02:05 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include"stack_op.h"


struct stack{
        int s_data;
        struct stack *below;
};

struct stack_info{
        struct stack *base;
        struct stack *top; 
};
struct stack_info *stack_array[MAX_STACK_NUM];

static int find_usable_position(void)
{
        int pos;

        for (pos = 0;pos < MAX_STACK_NUM;pos++) {
                if (stack_array[pos] == NULL){
                        return pos;
                }
        }

        return -ENOMEM;
}

int stack_init(void)
{
        int index;
        struct stack_info *new_stack_info;

        index = find_usable_position();
        if (index < 0) {
                return -ENOMEM;
        }

        new_stack_info = malloc(sizeof(struct stack_info));
        if (new_stack_info == NULL) {
                return -ENOMEM;
        }
        memset(new_stack_info,0,sizeof(struct stack_info));

        stack_array[index] = new_stack_info;

        return index;
}

int push(int stack_index,int data)
{
        struct stack_info *stack_info_temp;
        struct stack *new_stack_elem;

        if (stack_array[stack_index] == NULL) {
                return -EINVAL;
        }
        stack_info_temp = stack_array[stack_index];

        new_stack_elem = malloc(sizeof(struct stack));
        if (new_stack_elem == NULL) {
                return -ENOMEM;
        }
        new_stack_elem->s_data = data;

        if (stack_info_temp->base == NULL) {
                new_stack_elem->below = NULL;
                stack_info_temp->base = new_stack_elem;
                stack_info_temp->top = new_stack_elem;
        }else{
                new_stack_elem->below = stack_info_temp->top;
                stack_info_temp->top = new_stack_elem;
        }

        return 0;
}

int pop(int stack_index,int *data)
{
        struct stack_info *stack_info_temp;
        struct stack *top_stack_elem;
        int data_tmp;

        if (data == NULL) {
                return -EINVAL;
        }

        if (stack_array[stack_index] == NULL) {
                return -EINVAL;
        }
        stack_info_temp = stack_array[stack_index];

        if (stack_info_temp->top == NULL) {
                return -EINVAL;
        }
        top_stack_elem = stack_info_temp->top;

        if (top_stack_elem->below == NULL) {
                *data = top_stack_elem->s_data;
                free(top_stack_elem);
                stack_info_temp->top = NULL;
                stack_info_temp->base = NULL;
        }else{
                *data = top_stack_elem->s_data;
                stack_info_temp->top = top_stack_elem->below;
                free(top_stack_elem);
        }

        return 0;
}

int stack_destroy(int stack_index)
{
        struct stack_info *stack_info_temp;
        struct stack *top_stack_elem;
        int i;

        if (stack_array[stack_index] == NULL) {
                return -EINVAL;
        }
        stack_info_temp = stack_array[stack_index];

        for (i = 0;;i++) {
                if (stack_info_temp->top == NULL) {
                        free(stack_info_temp);
                        stack_array[stack_index] = NULL;
                        break;
                }else{
                        top_stack_elem = stack_info_temp->top;
                        stack_info_temp->top = top_stack_elem->below;
                        free(top_stack_elem);
                        top_stack_elem = NULL;
                }
        }

        return 0;
}
