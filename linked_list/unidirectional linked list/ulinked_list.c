/*************************************************************************
	> File Name: ulinked_list.c
	> Author: 
	> Mail: 
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ulinked_list.h"

#define DEBUG_TEST

LIST ul_list_init()
{
        LIST l;

        l = malloc(sizeof(struct ull_head));
        if (l == NULL) {
                return NULL;
        }

        l->next = NULL;
        l->tail = (struct ull_node *)l;

        return l;
}

int ul_list_add(LIST l,element_t *e)
{
        struct ull_node *node;

        node = malloc(sizeof(struct ull_node));
        if (node == NULL) {
                return -1;
        }

        node->next = NULL;
        memcpy(&(node->e),e,sizeof(element_t));

        l->tail->next = node;
        l->tail = node;

        return 0;
}

int ul_list_get_first_elem(LIST l,element_t *e)
{
        if (l->next) {
                memcpy(e,&(l->next->e),sizeof(element_t));
                l->next = l->next->next;
                if (l->next == NULL) {
                        l->tail = (struct ull_node *)l;
                }
        }
}

struct ull_node *ul_list_find_elem(LIST l,element_t *e)
{
        struct ull_node *node;

        node = (struct ull_node *)l;

        while (node->next) {
                if (!memcmp(&(node->next->e),e,sizeof(element_t))) {
                        return node;
                } else {
                        node = node->next;
                }
        }

        return NULL;
}

int ul_list_insert(LIST l,element_t *e,element_t *in_e)
{
        struct ull_node *node;
        struct ull_node *element;

        node = ul_list_find_elem(l,e);
        if (node == NULL) {
                return -1;
        }
        node = node->next;

        element = malloc(sizeof(struct ull_node));
        if (element == NULL) {
                return -1;
        }
        element->next = node->next;
        memcpy(&(element->e),in_e,sizeof(element_t));
        node->next = element;
        if (!element->next) {
                l->tail = element;
        }

        return 0;
}

int ul_list_delete(LIST l,element_t *e)
{
        struct ull_node *node;
        struct ull_node *pos;

        node = ul_list_find_elem(l,e);
        if (node == NULL) {
                return -1;
        }

        pos = node->next;
        node->next = pos->next;
        if (!(pos->next)) {
                l->tail = node;
        }
        free(pos);

        return 0;
}

void ul_list_make_empty(LIST l)
{
        struct ull_node *node;
        struct ull_node *pos;

        pos = l->next;

        while (pos) {
                node = pos;
                pos = pos->next;
                free(node);
        }
        
        l->next = NULL;
        l->tail = (struct ull_node *)l;
}

void ul_list_destroy(LIST *l)
{
        ul_list_make_empty(*l);

        free(*l);
        *l =NULL;

}

#ifdef DEBUG_TEST
void print_linked_list(LIST l)
{
        struct ull_node *pos;

        pos = l->next;

        while (pos) {
                printf("%d\n",pos->e.a);
                pos = pos->next;
        }
       
}

int main()
{
        LIST l;
        element_t i;
        element_t e;
        int pos = 16;
        int ret;

        l = ul_list_init();
        if (l == NULL) {
                printf("init linked list error\n");
                return -1;
        }

        while (pos--) {
                i.a = pos;
                ret = ul_list_add(l,&i);
                if (ret == -1) {
                        printf("add elment to linked list eror\n");
                        goto DEBUG_TEST_END;
                }
        }
        print_linked_list(l);

        i.a = 0;
        printf("delete element : %d\n",i.a);
        ret = ul_list_delete(l,&i);
        if (ret == -1) {
                printf("delete elment from linked list eror\n");
                goto DEBUG_TEST_END;
        }

        i.a = 15;
        printf("delete element : %d\n",i.a);
        ret = ul_list_delete(l,&i);
        if (ret == -1) {
                printf("delete elment from linked list eror\n");
                goto DEBUG_TEST_END;
        }
     
        print_linked_list(l);

        e.a = 0;
        i.a = 2;
        printf("insert element : %d\n",i.a);
        ret = ul_list_insert(l,&i,&e);
        if (ret == -1) {
                printf("insert elment from linked list eror\n");
                goto DEBUG_TEST_END;
        }
        print_linked_list(l);
        
        i.a = 15;
        ret = ul_list_add(l,&i);
        if (ret == -1) {
                printf("add elment to linked list eror\n");
                goto DEBUG_TEST_END;
        }
        print_linked_list(l);

        pos = 16;
        while (pos--) {
                ret = ul_list_get_first_elem(l,&i);
                if (ret == -1) {
                        printf("add elment to linked list eror\n");
                        goto DEBUG_TEST_END;
                }
                printf("i.a : %d\n",i.a);
        }

        i.a = 15;
        ret = ul_list_add(l,&i);
        if (ret == -1) {
                printf("add elment to linked list eror\n");
                goto DEBUG_TEST_END;
        }
        print_linked_list(l);


DEBUG_TEST_END:
        ul_list_destroy(&l);
        return ret;

}
#endif

