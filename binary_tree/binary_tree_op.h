/*************************************************************************
	> File Name: binary_tree_op.h
	> Author: sean
	> Mail: freeflyzx@126.com
	> Created Time: Thu 17 Mar 2016 12:29:28 AM HKT
 ************************************************************************/

#ifndef _BINARY_TREE_OP_H
#define _BINARY_TREE_OP_H

#define MAX_BT_NUM      5

struct binary_tree_elem{
        int bt_data;
        int bt_flag;
        struct binary_tree_elem *left;
        struct binary_tree_elem *right;
};

typedef struct binary_tree_elem bt_elem_t;

int bt_create(int root_data);
int bt_find(const int bt_index,const int f_data);
int bt_insert(const int bt_index,int parent_data,int ins_data);

#endif
