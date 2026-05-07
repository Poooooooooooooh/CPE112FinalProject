#include <stdio.h>
#include "TaskManager.h"

int main(void) {
    int choice;
    int running = 1;

    while (running) {
        printf("\nTask Management System\n");
        printf("1. Load tasks\n");
        printf("2. Save tasks\n");
        printf("3. Add task\n");
        printf("4. List tasks\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                printf("Load tasks is not implemented yet.\n");
                break;
            case 2:
                printf("Save tasks is not implemented yet.\n");
                break;
            case 3:
                printf("Add task is not implemented yet.\n");
                break;
            case 4:
                printf("List tasks is not implemented yet.\n");
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    }

    return 0;
}
