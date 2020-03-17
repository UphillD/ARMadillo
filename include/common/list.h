#ifndef LIST_H
#define LIST_H

#include "common/types.h"
#include "spinlock.h"

/* Define struct for a nodeType list.
 * Results in a list called nodeType_list_t. */
#define DEFINE_LIST(nodeType)	\
struct nodeType;		\
typedef struct nodeType##list { \
	struct nodeType * head;	\
	struct nodeType * tail;	\
	spinlock_t lock;	\
	uint32_t size;		\
} nodeType##_list_t;

/* Creates pointers and containers for the list. */
#define DEFINE_LINK(nodeType)		\
struct nodeType * next##nodeType;	\
struct nodeType * prev##nodeType;	\
nodeType##_list_t * container;

/* Initializes the list. */
#define INITIALIZE_LIST(list)			\
	list.head = list.tail = (void *)0;	\
	list.size = 0;				\
	spinlock_init(&list.lock);

/* Implements all list related functions. */
#define IMPLEMENT_LIST(nodeType)					\
									\
/* Appends a node to the back of the list. */				\
void append_##nodeType##_list (nodeType##_list_t * list, 		\
	struct nodeType * node)						\
{									\
	spinlock_lock(&list->lock);					\
	list->tail->next##nodeType = node;				\
	node->prev##nodeType = list->tail;				\
	list->tail = node;						\
	node->next##nodeType = NULL;					\
	list->size += 1;						\
	if (list->head == NULL)						\
		list->head = node;					\
	node->container = list;						\
	spinlock_unlock(&list->lock);					\
}									\
									\
/* Pushes a node to the front of the list. */				\
void push_##nodeType##_list (nodeType##_list_t * list, 			\
	struct nodeType * node)						\
{									\
	spinlock_lock(&list->lock);					\
	node->next##nodeType = list->head;				\
	node->prev##nodeType = NULL;					\
	list->head = node;						\
	list->size += 1;						\
	if (list->tail == NULL)						\
		list->tail = node;					\
	node->container = list;						\
	spinlock_unlock(&list->lock);					\
}									\
									\
/* Peeks the first element of the list (without removing it). */	\
struct nodeType * peek_##nodeType##_list (nodeType##_list_t * list)	\
{									\
	return list->head;						\
}									\
									\
/* Pops the first element from the list (removing it). */		\
struct nodeType * pop_##nodeType##_list (nodeType##_list_t * list)	\
{									\
	spinlock_lock(&list->lock);					\
	struct nodeType * res = list->head;				\
	list->head = list->head->next##nodeType;			\
	list->head->prev##nodeType = NULL;				\
	list->size -= 1;						\
	if (list->head == NULL)						\
		list->tail = NULL;					\
	res->container = NULL;						\
	spinlock_unlock(&list->lock);					\
									\
	return res;							\
}									\
									\
/* Returns the number of nodes in the list. */				\
uint32_t size_##nodeType##_list (nodeType##_list_t * list)		\
{									\
	return list->size;						\
}									\
									\
/* Gets the next node in the list. */					\
struct nodeType * next_##nodeType##_list (struct nodeType * node)	\
{									\
	return node->next##nodeType;					\
}									\
									\
/* Removes the given node from the list. */				\
void remove_##nodeType (nodeType##_list_t * list, 			\
	struct nodeType * node)						\
{									\
	spinlock_lock(&list->lock);					\
	if (node->container == list) {					\
		if (node->prev##nodeType == NULL)			\
			list->head = node->next##nodeType;		\
		else							\
			node->prev##nodeType = node->next##nodeType;	\
		if (node->next##nodeType == NULL)			\
			list->tail = node->prev##nodeType;		\
		else							\
			node->next##nodeType = node->prev##nodeType;	\
	}								\
	node->container = NULL;						\
	spinlock_unlock(&list->lock);					\
}									\

#endif
