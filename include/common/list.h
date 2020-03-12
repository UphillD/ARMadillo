#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define define_list(nodeType) \
typedef struct nodeType##list { \
	struct nodeType * head; \
	struct nodeType * tail; \
	uint32_t size;\
} nodeType##_list_t;

#define define_link(nodeType) \
struct nodeType * next##nodeType;\
struct nodeType * prev##nodeType;

#define init_list(list) \
	list.head = list.tail = (void *)0;\
	list.size = 0;

#define implement_list(nodeType) \
void append_##nodeType##_list(nodeType##_list_t * list, struct nodeType * node) { \
	list->tail->next##nodeType = node;                                        \
	node->prev##nodeType = list->tail;                                        \
	list->tail = node;                                                        \
	node->next##nodeType = NULL;                                              \
	list->size += 1;                                                          \
	if (list->head == NULL) {                                                 \
		list->head = node;                                                \
	}                                                                         \
}                                                                                 \
                                                                                  \
void push_##nodeType##_list(nodeType##_list_t * list, struct nodeType * node) { \
	node->next##nodeType = list->head;                                      \
	node->prev##nodeType = NULL;                                            \
	list->head = node;                                                      \
	list->size += 1;                                                        \
	if (list->tail == NULL) {                                               \
		list->tail = node;                                              \
	}                                                                       \
}                                                                               \
                                                                                \
struct nodeType * peek_##nodeType##_list(nodeType##_list_t * list) {         \
    return list->head;                                                       \
}                                                                            \
                                                                             \
struct nodeType * pop_##nodeType##_list(nodeType##_list_t * list) {          \
    struct nodeType * res = list->head;                                      \
    list->head = list->head->next##nodeType;                                 \
    list->head->prev##nodeType = NULL;                                       \
    list->size -= 1;                                                         \
    if (list->head == NULL) {                                                \
        list->tail = NULL;                                                   \
    }                                                                        \
    return res;                                                              \
}                                                                            \
                                                                             \
uint32_t size_##nodeType##_list(nodeType##_list_t * list) {                  \
	return list->size;                                                   \
}                                                                            \
                                                                             \
struct nodeType * next_##nodeType##_list(struct nodeType * node) {           \
	return node->next##nodeType;                                         \
}                                                                            \

#endif
