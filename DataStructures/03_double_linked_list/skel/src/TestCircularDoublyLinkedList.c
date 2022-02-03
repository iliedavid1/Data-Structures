#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.h"

#define MAX_STRING_SIZE 64

int main() {
    doubly_linked_list_t *doublyLinkedList;

    int is_int = 0;
    int is_string = 0;
    while(1) {
        char command[16], added_elem[64], *end_ptr;
        long nr, pos;
        scanf("%s", command);
        if(strcmp(command, "create_str") == 0){
            doublyLinkedList = dll_create(MAX_STRING_SIZE);
            is_string = 1;
        }
        if(strcmp(command, "create_int") == 0){
            doublyLinkedList = dll_create(sizeof(int));
            is_int = 1;
        }
        /* pentru a apela functia de stergere a nodului din mijloc */
        if(strcmp(command, "delete") == 0) {
            dll_remove_mid(&doublyLinkedList);
        }
        if(strcmp(command, "add") == 0){
            scanf("%ld", &pos);
            scanf("%s", added_elem);
            nr = strtol(added_elem, &end_ptr, 10);
            if(nr != 0) {
                dll_add_nth_node(doublyLinkedList, pos, &nr);
            }
            else{
                dll_add_nth_node(doublyLinkedList, pos, end_ptr);
            }
        }
        if(strcmp(command, "remove") == 0){
            scanf("%ld", &pos);
            struct dll_node_t *del = dll_remove_nth_node(doublyLinkedList, pos);
            free(del->data);
            free(del);
        }
        if(strcmp(command, "print") == 0){
            if(is_int == 1){
                dll_print_int_list(doublyLinkedList);
            }
            if(is_string == 1){
                dll_print_string_list(doublyLinkedList);
            }
        }
        if(strcmp(command, "free") == 0){
            dll_free(&doublyLinkedList);
            break;
        }
    }
    return 0;
}
