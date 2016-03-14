/*************************************************************************
	> File Name: stack_op.h
	> Author: sean
	> Mail: freeflyzx@gmail.com
	> Created Time: Mon 14 Mar 2016 11:08:23 PM CST
 ************************************************************************/

#ifndef _STACK_OP_H
#define _STACK_OP_H

#define MAX_STACK_NUM   5


int stack_init(void);
int push(int stack_index,int data);
int pop(int stack_index,int *data);
int stack_destroy(int stack_index);

#endif
