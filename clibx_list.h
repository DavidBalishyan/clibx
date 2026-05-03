#ifndef CLIBX_LIST_H
#define CLIBX_LIST_H

#include "clibx.h"

/*
 * CLIBX_LIST - Singly Linked List Implementation
 * --------------------------------------
 * Generic, type-agnostic linked list with common operations:
 * - Push/Prepend nodes
 * - Insert at arbitrary positions
 * - Pop/Remove nodes
 * - Search and access
 * - Iteration
 * - Memory cleanup
 * --------------------------------------
 */

//
// Generic Node Structure
//

typedef struct clibx_node {
    void *data;
    struct clibx_node *next;
} clibx_node;

/*
 * clibx_list
 * --------------------------------------
 * A singly-linked list container holding:
 * - head: pointer to first node
 * - tail: pointer to last node (for efficient appending)
 * - count: number of nodes in the list
 * --------------------------------------
 */
typedef struct {
    clibx_node *head;
    clibx_node *tail;
    size_t count;
} clibx_list;

//
// Lifecycle Operations
//

/*
 * list_init
 * --------------------------------------
 * Initialize an empty linked list.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 * 
 * Example:
 *   clibx_list list = list_init();
 * --------------------------------------
 */
static inline clibx_list list_init(void) {
    return (clibx_list){ .head = NULL, .tail = NULL, .count = 0 };
}

/*
 * list_push_back
 * --------------------------------------
 * Append data to the end of the list.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - data: void pointer to data (not copied, just stored)
 *
 * Example:
 *   int *val = NEW(int);
 *   *val = 42;
 *   list_push_back(&list, val);
 * --------------------------------------
 */
static inline void list_push_back(clibx_list *list, void *data) {
    clibx_node *new_node = NEW_ZEROED(clibx_node);
    ASSERT(new_node != NULL, "list_push_back: malloc failed");
    
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->count == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->count++;
}

/*
 * list_push_front
 * --------------------------------------
 * Prepend data to the beginning of the list.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - data: void pointer to data
 *
 * Example:
 *   int *val = NEW(int);
 *   *val = 10;
 *   list_push_front(&list, val);
 * --------------------------------------
 */
static inline void list_push_front(clibx_list *list, void *data) {
    clibx_node *new_node = NEW_ZEROED(clibx_node);
    ASSERT(new_node != NULL, "list_push_front: malloc failed");
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    if (list->count == 0) {
        list->tail = new_node;
    }
    list->count++;
}

//
// Access Operations
//

/*
 * list_get
 * --------------------------------------
 * Get data at a specific index (0-based).
 * Returns NULL if index is out of bounds.
 *
 * Time complexity: O(n) - requires traversal
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - index: 0-based index
 *
 * Example:
 *   void *data = list_get(&list, 2);
 *   if (data) printf("Found: %d\n", *(int*)data);
 * --------------------------------------
 */
static inline void* list_get(clibx_list *list, size_t index) {
    if (index >= list->count) return NULL;
    
    clibx_node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current ? current->data : NULL;
}

/*
 * list_front
 * --------------------------------------
 * Get data at the front of the list.
 * Returns NULL if list is empty.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
static inline void* list_front(clibx_list *list) {
    return list->head ? list->head->data : NULL;
}

/*
 * list_back
 * --------------------------------------
 * Get data at the back of the list.
 * Returns NULL if list is empty.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
static inline void* list_back(clibx_list *list) {
    return list->tail ? list->tail->data : NULL;
}

/*
 * list_contains
 * --------------------------------------
 * Check if a value exists in the list using a comparison function.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - value: value to search for
 *   - cmp: comparison function (return 1 if equal, 0 otherwise)
 *
 * Example:
 *   int target = 42;
 *   int found = list_contains(&list, &target, 
 *                             (int (*)(void*, void*))int_cmp);
 *   
 *   int int_cmp(int *a, int *b) { return *a == *b; }
 * --------------------------------------
 */
static inline int list_contains(clibx_list *list, void *value, 
                                int (*cmp)(void*, void*)) {
    clibx_node *current = list->head;
    while (current != NULL) {
        if (cmp(current->data, value)) return 1;
        current = current->next;
    }
    return 0;
}

//
// Removal Operations
//

/*
 * list_pop_front
 * --------------------------------------
 * Remove and return the first node's data.
 * Returns NULL if list is empty.
 * NOTE: Caller becomes responsible for freeing returned data.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 *
 * Example:
 *   void *data = list_pop_front(&list);
 *   if (data) { printf("Popped: %d\n", *(int*)data); free(data); }
 * --------------------------------------
 */
static inline void* list_pop_front(clibx_list *list) {
    if (list->count == 0) return NULL;
    
    clibx_node *temp = list->head;
    void *data = temp->data;
    
    list->head = list->head->next;
    if (list->count == 1) {
        list->tail = NULL;
    }
    list->count--;
    
    free(temp);
    return data;
}

/*
 * list_remove_at
 * --------------------------------------
 * Remove node at a specific index.
 * Returns the removed data or NULL if index out of bounds.
 * NOTE: Caller becomes responsible for freeing returned data.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - index: 0-based index
 *
 * Example:
 *   void *data = list_remove_at(&list, 1);
 *   if (data) { free(data); }
 * --------------------------------------
 */
static inline void* list_remove_at(clibx_list *list, size_t index) {
    if (index >= list->count || list->count == 0) return NULL;
    
    if (index == 0) {
        return list_pop_front(list);
    }
    
    clibx_node *current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    clibx_node *to_remove = current->next;
    current->next = to_remove->next;
    
    if (index == list->count - 1) {
        list->tail = current;
    }
    
    void *data = to_remove->data;
    free(to_remove);
    list->count--;
    
    return data;
}

/*
 * list_remove_all
 * --------------------------------------
 * Remove all nodes from the list and optionally free their data.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - free_data: if non-zero, calls free() on each node's data
 *
 * Example:
 *   list_remove_all(&list, 1);  // free all data and nodes
 * --------------------------------------
 */
static inline void list_remove_all(clibx_list *list, int free_data) {
    clibx_node *current = list->head;
    while (current != NULL) {
        clibx_node *next = current->next;
        if (free_data) FREE(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

//
// Query Operations
//

/*
 * list_is_empty
 * --------------------------------------
 * Check if the list is empty.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
static inline int list_is_empty(clibx_list *list) {
    return list->count == 0;
}

/*
 * list_size
 * --------------------------------------
 * Get the number of elements in the list.
 *
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
static inline size_t list_size(clibx_list *list) {
    return list->count;
}

//
// Iteration Macros
//

/*
 * LIST_FOR_EACH
 * --------------------------------------
 * Iterate over all nodes in the list.
 *
 * Parameters:
 *   - node: variable to hold current node pointer
 *   - list: pointer to the list
 *
 * Example:
 *   clibx_node *node;
 *   LIST_FOR_EACH(node, &list) {
 *       printf("%d\n", *(int*)node->data);
 *   }
 * --------------------------------------
 */
#define LIST_FOR_EACH(node, list) \
    for (clibx_node *node = (list)->head; node != NULL; node = node->next)

//
// Memory Management
//

/*
 * list_free
 * --------------------------------------
 * Free all memory used by the list.
 * Does NOT automatically free the data pointed to by nodes.
 * Use list_remove_all(&list, 1) if you need to free all data.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Parameters:
 *   - list: pointer to the list
 *   - free_data: if non-zero, calls free() on each node's data
 *
 * Example:
 *   list_free(&list, 1);  // free all data and nodes
 * --------------------------------------
 */
static inline void list_free(clibx_list *list, int free_data) {
    list_remove_all(list, free_data);
}

//
// Utility: Print List of Integers
//

/*
 * list_print_int
 * --------------------------------------
 * Print all integers in the list in [a, b, c] format.
 * Assumes all nodes contain pointers to integers.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * Example:
 *   list_print_int(&list);
 * --------------------------------------
 */
static inline void list_print_int(clibx_list *list) {
    printf("[");
    clibx_node *current = list->head;
    int first = 1;
    while (current != NULL) {
        if (!first) printf(", ");
        printf("%d", *(int*)current->data);
        first = 0;
        current = current->next;
    }
    printf("]\n");
}

/*
 * list_print_str
 * --------------------------------------
 * Print all strings in the list in [a, b, c] format.
 * Assumes all nodes contain string pointers (char*).
 *
 * Time complexity: O(n * m) where m is average string length
 * Space complexity: O(1)
 *
 * Example:
 *   list_print_str(&list);
 * --------------------------------------
 */
static inline void list_print_str(clibx_list *list) {
    printf("[");
    clibx_node *current = list->head;
    int first = 1;
    while (current != NULL) {
        if (!first) printf(", ");
        printf("\"%s\"", (char*)current->data);
        first = 0;
        current = current->next;
    }
    printf("]\n");
}

#endif /* CLIBX_LIST_H */
