#include "TaskManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTask(Task **head, int *nextId, const char name[], int priority) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    Task *current;

    if (newTask == NULL) {
        printf("Unable to add task. Memory allocation failed.\n");
        return;
    }

    newTask->id = *nextId;
    strncpy(newTask->name, name, MAX_NAME_LENGTH - 1);
    newTask->name[MAX_NAME_LENGTH - 1] = '\0';
    newTask->priority = priority;
    newTask->done = 0;
    newTask->next = NULL;

    if (*head == NULL) {
        *head = newTask;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTask;
    }

    (*nextId)++;
}

void displayTasks(Task *head) {
    Task *current = head;

    if (current == NULL) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n%-5s %-40s %-10s %-10s\n", "ID", "Name", "Priority", "Status");
    printf("---------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-5d %-40s %-10d %-10s\n",
               current->id,
               current->name,
               current->priority,
               current->done ? "Done" : "Pending");
        current = current->next;
    }
}
