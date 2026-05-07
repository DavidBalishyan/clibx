#include "clibx_list.h"

/*
 * demo_list.c
 * -----------------------------------------------------
 * Demonstrates the linked list implementation in clibx.h
 * -----------------------------------------------------
 */

// Comparison function for integers
int int_cmp(void *a, void *b) {
    return *(int *)a == *(int *)b;
}

// Comparison function for strings
int str_cmp(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

int main(void) {
    printf("clibx Linked List Demo\n\n");

    printf("1. Integer linked list\n");
    printf("------------------------\n");
    
    clibx_list int_list = list_init();
    
    // Add integers to the back
    printf("Pushing 10, 20, 30 to back:\n");
    int *val1 = NEW(int); *val1 = 10;
    int *val2 = NEW(int); *val2 = 20;
    int *val3 = NEW(int); *val3 = 30;
    
    list_push_back(&int_list, val1);
    list_push_back(&int_list, val2);
    list_push_back(&int_list, val3);
    
    printf("List: ");
    list_print_int(&int_list);
    printf("Size: %zu\n\n", list_size(&int_list));
    
    // Prepend to front
    printf("Pushing 5 to front:\n");
    int *val0 = NEW(int); *val0 = 5;
    list_push_front(&int_list, val0);
    printf("List: ");
    list_print_int(&int_list);
    printf("Size: %zu\n\n", list_size(&int_list));
    
    // Access elements
    printf("Accessing elements (0-based indexing):\n");
    void *data = list_get(&int_list, 0);
    if (data) printf("  Index 0: %d\n", *(int *)data);
    
    data = list_get(&int_list, 2);
    if (data) printf("  Index 2: %d\n", *(int *)data);
    
    printf("  Front: %d\n", *(int *)list_front(&int_list));
    printf("  Back: %d\n\n", *(int *)list_back(&int_list));
    
    // Search for a value
    printf("Searching for value 20:\n");
    int search = 20;
    if (list_contains(&int_list, &search, int_cmp)) {
        printf("  Found!\n\n");
    }
    
    // Remove operations
    printf("Removing front element:\n");
    void *removed = list_pop_front(&int_list);
    if (removed) {
        printf("  Removed: %d\n", *(int *)removed);
        free(removed);
    }
    printf("List: ");
    list_print_int(&int_list);
    printf("Size: %zu\n\n", list_size(&int_list));
    
    printf("Removing element at index 1:\n");
    removed = list_remove_at(&int_list, 1);
    if (removed) {
        printf("  Removed: %d\n", *(int *)removed);
        free(removed);
    }
    printf("List: ");
    list_print_int(&int_list);
    printf("Size: %zu\n\n", list_size(&int_list));
    
    // Iteration
    printf("Iterating with LIST_FOR_EACH macro:\n");
    printf("  Values: ");
    clibx_node *node;
    int first = 1;
    LIST_FOR_EACH(node, &int_list) {
        if (!first) printf(", ");
        printf("%d", *(int *)node->data);
        first = 0;
    }
    printf("\n\n");
    
    // Clean up integer list
    list_free(&int_list, 1);
    
    
    // ===== STRING LIST EXAMPLE =====
    printf("2. STRING LINKED LIST\n");
    printf("----------------------\n");
    
    clibx_list str_list = list_init();
    
    printf("Building list: [apple, banana, cherry]\n");
    list_push_back(&str_list, strdup("apple"));
    list_push_back(&str_list, strdup("banana"));
    list_push_back(&str_list, strdup("cherry"));
    
    printf("List: ");
    list_print_str(&str_list);
    printf("Size: %zu\n\n", list_size(&str_list));
    
    // Prepend
    printf("Prepending 'grape':\n");
    list_push_front(&str_list, strdup("grape"));
    printf("List: ");
    list_print_str(&str_list);
    printf("\n");
    
    // Search
    printf("Searching for 'banana':\n");
    char search_str[] = "banana";
    if (list_contains(&str_list, search_str, (int (*)(void*, void*))str_cmp)) {
        printf("  Found!\n\n");
    }
    
    // Iteration using LIST_FOR_EACH_DATA
    printf("Iterating with LIST_FOR_EACH macro:\n");
    LIST_FOR_EACH(node, &str_list) {
        printf("  - %s\n", (char *)node->data);
    }
    printf("\n");
    
    // Clean up string list (free_data=1 to free strings)
    list_free(&str_list, 1);
    
    
    // ===== STRUCT EXAMPLE =====
    printf("3. CUSTOM STRUCT LINKED LIST\n");
    printf("-----------------------------\n");
    
    typedef struct {
        int id;
        char name[50];
    } Person;
    
    clibx_list person_list = list_init();
    
    printf("Creating list of people:\n");
    Person *p1 = NEW(Person);
    p1->id = 1;
    strcpy(p1->name, "Alice");
    
    Person *p2 = NEW(Person);
    p2->id = 2;
    strcpy(p2->name, "Bob");
    
    Person *p3 = NEW(Person);
    p3->id = 3;
    strcpy(p3->name, "Charlie");
    
    list_push_back(&person_list, p1);
    list_push_back(&person_list, p2);
    list_push_back(&person_list, p3);
    
    printf("People in list:\n");
    LIST_FOR_EACH(node, &person_list) {
        Person *person = (Person *)node->data;
        printf("  ID: %d, Name: %s\n", person->id, person->name);
    }
    printf("Size: %zu\n\n", list_size(&person_list));
    
    // Clean up
    list_free(&person_list, 1);
    
    printf("=== Demo Complete ===\n");
    return 0;
}
