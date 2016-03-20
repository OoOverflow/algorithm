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

int bt_create(int root_bt_data,int root_bt_flag)
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
        root->bt_data = root_bt_data;
        root->bt_flag = root_bt_flag;
        bt_array[index] = root;

        return index;
}

static int bt_deep_find(struct binary_tree_elem *root,struct binary_tree_elem **used_leaves_pare)
{
        struct binary_tree_elem *bt_child;
        int ret;

        if (root->bt_flag == 0) {
                return -1;
        }
        if (root->left == NULL) {
                *used_leaves_pare = root;
                return 1;
        }

        if (root->right == NULL) {
                *used_leaves_pare = root;
                return 2;
        }

        bt_child = root->left;
        ret = bt_deep_find(bt_child,used_leaves_pare);
        if (ret < 0) {
                bt_child = root->right;
                ret = bt_deep_find(bt_child,used_leaves_pare);
        }

        return ret;

}

#if 0
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
#endif

int bt_insert(const int bt_index,int ins_data,int ins_flag)
{
        struct binary_tree_elem *root;
        struct binary_tree_elem *parent;
        struct binary_tree_elem *new_elem;
        int ret;

        if (bt_array[bt_index] == NULL) {
                return -EINVAL;
        }

        root = bt_array[bt_index];
        ret = bt_deep_find(root,&parent);
        if (ret == 1) {
                new_elem = malloc(sizeof(struct binary_tree_elem));
                if (new_elem == NULL) {
                        return -ENOMEM;
                }

                memset(new_elem,0,sizeof(struct binary_tree_elem));
                new_elem->bt_data = ins_data;
                new_elem->bt_flag = ins_flag;
                parent->left = new_elem;

                return 0;
        }else if (ret == 2) {
                new_elem = malloc(sizeof(struct binary_tree_elem));
                if (new_elem == NULL) {
                        return -ENOMEM;
                }

                memset(new_elem,0,sizeof(struct binary_tree_elem));
                new_elem->bt_data = ins_data;
                new_elem->bt_flag = ins_flag;
                parent->right = new_elem;

                return 0;
        }else{
                return -1;
        }
}


