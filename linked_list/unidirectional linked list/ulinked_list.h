/*************************************************************************
	> File Name: ulinked_list.h
	> Author: 
	> Mail: 
 ************************************************************************/

#ifndef _ULINKED_LIST_H
#define _ULINKED_LIST_H

struct Element{
        int a;
};
typedef struct Element element_t;

struct ull_node{
        /* this member must be first */
        struct ull_node *next;
        element_t e;
};

struct ull_head{
        /* this member must be first */
        struct ull_node *next;
        struct ull_node *tail;
};
typedef struct ull_head *LIST;

#endif
