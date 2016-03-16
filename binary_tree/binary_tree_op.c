/*************************************************************************
	> File Name: binary_tree_op.c
	> Author: sean
	> Mail: freeflyzx@126.com
	> Created Time: Thu 17 Mar 2016 12:29:09 AM HKT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include"binary_tree_op.h"

enum {
        SEARCH_LEFT = 0,
        SEARCH_RIGHT,
};

static struct binary_tree_elem *bt_array[MAX_BT_NUM];

static int find_usable_position()
{
        int pos;

        for (pos = 0;pos < MAX_BT_NUM;pos++) {
                if(bt_array[pos] == 0){
                        return pos;
                }
        }

        return -ENOMEM;
}

int bt_create(int root_data)
{
        int index;
        struct binary_tree_elem *root;

        index = find_usable_position();
        if (index < 0) {
                return -ENOMEM;
        }

        root = malloc(sizeof(struct binary_tree_elem));
        if (root == NULL) {
                return -ENOMEM;
        }

        memset(root,0,sizeof(struct binary_tree_elem));
        root->bt_data = root_data;
        bt_array[index] = root;

        return index;
}

static struct binary_tree_elem *bt_deep_find(struct binary_tree_elem *root,const int f_data)
{
        struct binary_tree_elem *bt_parent;
        struct binary_tree_elem *bt_child;
        struct binary_tree_elem *find_res;

        if (root == NULL) {
                return NULL;
        }

        bt_parent = root;
        bt_child = root->left;
        if (bt_parent->bt_data == f_data) {
                return bt_parent;
        }

        while(1){
                find_res = bt_deep_find(bt_child,f_data);
                if (find_res != NULL) {
                        return find_res;
                }

                if (bt_child == bt_parent->right) {
                        return NULL;
                }else{
                        bt_child = bt_parent->right;
                }
        }
}

int bt_find(const int bt_index,const int f_data)
{
        struct binary_tree_elem *root;
        struct binary_tree_elem *bt_tmp;

        if (bt_array[bt_index] == NULL) {
                return -EINVAL;
        }

        root = bt_array[bt_index];
        bt_tmp = bt_deep_find(root,f_data);
        if (bt_tmp != NULL) {
                return 1;
        }

        return 0;
}

int bt_insert(const int bt_index,int parent_data,int ins_data)
{
        struct binary_tree_elem *root;
        struct binary_tree_elem *parent;
        struct binary_tree_elem *new_elem;

        if (bt_array[bt_index] == NULL) {
                return -EINVAL;
        }

        root = bt_array[bt_index];
        parent = bt_deep_find(root,parent_data);
        if (parent == NULL) {
                return 0;
        }

        if (parent->left == NULL) {
                new_elem = malloc(sizeof(struct binary_tree_elem));
                if (new_elem == NULL) {
                        return -ENOMEM;
                }

                memset(new_elem,0,sizeof(struct binary_tree_elem));
                new_elem->bt_data = ins_data;
                parent->left = new_elem;

                return 1;
        }else if (parent->right == NULL) {
                new_elem = malloc(sizeof(struct binary_tree_elem));
                if (new_elem == NULL) {
                        return -ENOMEM;
                }

                memset(new_elem,0,sizeof(struct binary_tree_elem));
                new_elem->bt_data = ins_data;
                parent->right = new_elem;

                return 1;
        }else{
                return 0;
        }
}


