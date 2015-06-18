#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

#define MAX_STRING_LENGTH 512
#define LIST_ERROR -1
#define LIST_SUCCESS 0

typedef struct list_entry_t
{
    char *key;
    address_t value;
    struct list_entry_t *next;
    struct list_entry_t *prev;
} ListEntry;

typedef struct ordered_list_t
{
    ListEntry *head;
    ListEntry *tail;
} OrderedList;

ListEntry *listEntry_init(char *key, address_t value, ListEntry *next,
        ListEntry *prev);

void listEntry_destroy(ListEntry *self);

OrderedList *orderedList_init(void);

void orderedList_destroy(OrderedList *self);

ListEntry *orderedList_getGreaterOrEqual(OrderedList *self, char *key);

ListEntry *orderedList_getNode(OrderedList *self, char *key);

void orderedList_add(OrderedList *self, char *key, address_t value);

int orderedList_get(OrderedList *self, char *key, address_t *out);

void orderedList_test(void);

void orderedList_iteratePrint(OrderedList *self);

#endif
