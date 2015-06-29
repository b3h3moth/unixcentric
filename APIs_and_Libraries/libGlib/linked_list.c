#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib-2.0/glib.h>

#define MAX_BUF 50

GList *list;

int main(int argc, char *argv[]) {
    char new_element[MAX_BUF];
    int i=0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* Add an element to list */
    list = g_list_append(list, argv[1]);

    printf("Please give new element for list: ");
    fgets(new_element, MAX_BUF+1, stdin);

    for (i=0; i<strlen(new_element); i++) {
        if (new_element[i] == '\n')
            new_element[i] = '\0';
    }

    list = g_list_prepend(list, new_element);
    list = g_list_append(list, "third");

    while (list != NULL) {
        printf("%s\n", (char *)list->data);
        list = list->next;
    }

    g_list_free(list);

    return(EXIT_SUCCESS);
}
