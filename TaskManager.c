#include "TaskManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int deadlineValue(const char deadline[]) {
    int day;
    int month;
    int year;

    if (sscanf(deadline, "%d-%d-%d", &day, &month, &year) != 3) {
        return 99999999;
    }

    return (year * 10000) + (month * 100) + day;
}

void addTask(Task **head, int *nextId, const char name[], const char deadline[], int priority) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    Task *current;

    if (newTask == NULL) {
        printf("Unable to add task. Memory allocation failed.\n");
        return;
    }

    newTask->id = *nextId;
    strncpy(newTask->name, name, MAX_NAME_LENGTH - 1);
    newTask->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(newTask->deadline, deadline, MAX_DEADLINE_LENGTH - 1);
    newTask->deadline[MAX_DEADLINE_LENGTH - 1] = '\0';
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

    printf("\n%-5s %-30s %-18s %-10s %-10s\n", "ID", "Name", "Deadline", "Priority", "Status");
    printf("--------------------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-5d %-30s %-18s %-10d %-10s\n",
               current->id,
               current->name,
               current->deadline,
               current->priority,
               current->done ? "Done" : "Pending");
        current = current->next;
    }
}

void sortTasksByDeadline(Task **head) {
    int swapped;
    Task **current;
    Task *first;
    Task *second;

    if (head == NULL || *head == NULL) {
        return;
    }

    do {
        swapped = 0;
        current = head;

        while ((*current)->next != NULL) {
            first = *current;
            second = first->next;

            if (deadlineValue(first->deadline) > deadlineValue(second->deadline)) {
                first->next = second->next;
                second->next = first;
                *current = second;
                swapped = 1;
            }

            current = &((*current)->next);
        }
    } while (swapped);
}
