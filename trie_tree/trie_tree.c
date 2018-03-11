/*************************************************************************
	> File Name: trie_tree.c
	> Author:sean 
	> Mail:seanzhao0xff@gmail.com 
	> Created Time: Sat 10 Mar 2018 10:41:15 PM CST
 ************************************************************************/

#include"trie_tree.h"

tt_root *trie_tree_init(void)
{
        tt_root *tt_root_node;

        tt_root_node = malloc(sizeof(tt_root));
        if (tt_root_node == NULL) {
                LOG_ERROR("malloc root\n");
                return NULL;
        }

        memset(tt_root_node,0,sizeof(tt_root));
        return tt_root_node;
}

tt_leaf *trie_tree_leaf_insert(tt_leaf *lp,int abs_pos)
{
        tt_leaf *tmp = NULL;

        tmp = lp->cp[abs_pos];
        if (tmp == NULL) {
                tmp = malloc(sizeof(tt_leaf));
                if (tmp == NULL) {
                        LOG_ERROR("malloc leaf\n");
                        return NULL;
                }
                memset(tmp,0,sizeof(tt_leaf));
                lp->cp[abs_pos] = tmp;
        }

        return lp->cp[abs_pos];
}

int trie_tree_insert(tt_root *rp,char *string,int size)
{
        int i;
        tt_leaf *lp = (tt_leaf *)rp;
        int abs_pos;
        char *tmp;

        if (size == 0) {
                return -1;
        }

        tmp = string;
        for (i = 0;i < size;i++) {
                if (isdigit(*tmp)) {
                        abs_pos = *tmp - '0';
                } else if (islower(*tmp)) {
                        abs_pos = *tmp - 'a' + 10;
                } else if (isupper(*tmp)) {
                        abs_pos = *tmp - 'A' + 10 + 26;
                }

                LOG_DEBUG("character : %c,abs pos : %d\n",*tmp,abs_pos);
                lp = trie_tree_leaf_insert(lp,abs_pos);
                if (lp == NULL) {
                        LOG_ERROR("insert leaf\n");
                        return -1;
                }
                tmp++;
        }

        lp->is_end_times++;
        LOG_DEBUG("times : %d\n",lp->is_end_times);
        return lp->is_end_times;
}

int trie_tree_walk_comp(tt_root *rp,char *str,int size)
{
        int i;
        tt_leaf *lp = (tt_leaf *)rp;
        int abs_pos;
        char *tmp;

        tmp = str;
        for (i = 0;i < size;i++) {
                if (isdigit(*tmp)) {
                        abs_pos = *tmp - '0';
                } else if (islower(*tmp)) {
                        abs_pos = *tmp - 'a' + 10;
                } else if (isupper(*tmp)) {
                        abs_pos = *tmp - 'A' + 10 + 26;
                } else {
                        return -1;
                }

                lp = lp->cp[abs_pos];
                if (lp == NULL) {
                        LOG_ERROR("walk\n");
                        return -1;
                }
                tmp++;
        }

        return lp->is_end_times;
}

void printf_times(char *str,int size,int info)
{
        char *ptr;
        char *startp;
        int p;
        
        startp = malloc(MAX_STR_BUF_LENGTH);
        if (startp == NULL) {
                return ;
        }

        ptr = startp;
        for (p = 0;p < size;p++,ptr++,str++) {
                *ptr = *str;
                if (*ptr < 10) {
                        *ptr += '0';
                } else if (*ptr < 36) {
                        *ptr += 'a' - 10;
                } else if (*ptr < 62) {
                        *ptr += 'A' - 10 - 26;
                }
        }

        printf("%s : %d\n",startp,info);
        free(startp);
}

int trie_tree_walk_all(tt_root *rp,walk_all_cb printf_times)
{       
        char i;
        tt_leaf *lp = (tt_leaf *)rp;
        tt_leaf *lp_nl;
        static char str[MAX_STR_BUF_LENGTH];
        static char *tmp = str;

        for (i = 0;i < MAX_CHARACTER_NUMBER;i++) {
                if (lp->cp[i]) {
                        lp_nl = lp->cp[i];
                        *tmp = i;
                        tmp++;

                        if (lp_nl->is_end_times) {
                                printf_times(str,tmp - str,lp_nl->is_end_times);
                        }

                        trie_tree_walk_all((tt_root *)lp_nl,printf_times);
                }
        }

        *(tmp--) = '\0';
        return 0;
}

int trie_tree_free(tt_root *rp)
{       
        char i;
        tt_leaf *lp = (tt_leaf *)rp;
        tt_leaf *lp_nl;

        for (i = 0;i < MAX_CHARACTER_NUMBER;i++) {
                if (lp->cp[i]) {
                        lp_nl = lp->cp[i];

                        trie_tree_free((tt_root *)lp_nl);
                }
        }
        free(lp);

        return 0;
}

int calc_string_appeared_times(tt_root *rp,char *string)
{
        int i,res;
        char *startp;
        char *curp;

        startp = string;
        curp = string;
        for (;*curp != '\0';) {
                if (*curp == '.') {
                        res = trie_tree_insert(rp,startp,curp - startp);
                        if (res < 0) {
                                return -1;
                        }
                        startp = curp + 1;
                }
                curp++;
        }
        res = trie_tree_insert(rp,startp,curp - startp);
        if (res < 0) {
                return -1;
        }

        return 0;
}

#define MAX_TEST_URL_NUM        10
int main()
{
        tt_root *rp;
        int i;

        char test_url[MAX_TEST_URL_NUM][255] = {
                "126.com",
                "163.com",
                "qq.com",
                "google.com",
                "126.cn",
                "126.com.cn",
                "google.cn",
                "163.126.com.cn",
                "ALDS.Com",
                "126.ALds.Com.CN",
        };

        rp = trie_tree_init();
        if (rp == NULL) {
                LOG_ERROR("init tree\n");
                return -1;
        }

        for (i = 0;i < MAX_TEST_URL_NUM;i++) {
                calc_string_appeared_times(rp,test_url[i]);
        }

        trie_tree_walk_all(rp,printf_times);

        i = trie_tree_walk_comp(rp,"126",3);
        LOG_DEBUG("126 : %d\n",i);

        trie_tree_free(rp);
}

