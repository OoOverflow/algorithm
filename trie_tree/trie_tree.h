/*************************************************************************
	> File Name: trie_tree.h
	> Author:sean 
	> Mail:seanzhao0xff@gmail.com 
	> Created Time: Sat 10 Mar 2018 10:41:15 PM CST
 ************************************************************************/

#ifndef __TRIE_TREE_H_
#define __TRIE_TREE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_CHARACTER_NUMBER    62
#define MAX_STR_BUF_LENGTH      255

//#define OP_DEBUG
#ifdef OP_DEBUG
#define LOG_DEBUG(format,argv...)       \
                printf("[DEBUG][%s][%d] : "format,__func__,__LINE__,##argv);
#else
#define LOG_DEBUG(format,argv...)
#endif

#define LOG_ERROR(format,argv...)       \
                fprintf(stderr,"[ERROR][%s][%d] : "format,__func__,__LINE__,##argv);
#define LOG_WARN(format,argv...)       \
                printf("[WARN][%s][%d] : "format,__func__,__LINE__,##argv);

struct trie_tree_leaf {
        struct trie_tree_leaf *cp[MAX_CHARACTER_NUMBER];
        int is_end_times;
};
typedef struct trie_tree_leaf tt_leaf;

struct trie_tree_root {
        struct trie_tree_leaf *cp[MAX_CHARACTER_NUMBER];
};
typedef struct trie_tree_root tt_root;

typedef void (*walk_all_cb)(char *str,int size,int info);

#endif
