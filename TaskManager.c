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

void deleteTask(Task **head, UndoNode **undoStack, int id) {
    Task *current;
    Task *previous;
    UndoNode *deletedTask;

    if (head == NULL || *head == NULL) {
        printf("No tasks available to delete.\n");
        return;
    }

    current = *head;
    previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d was not found.\n", id);
        return;
    }

    deletedTask = (UndoNode *)malloc(sizeof(UndoNode));
    if (deletedTask == NULL) {
        printf("Unable to delete task. Memory allocation failed.\n");
        return;
    }

    deletedTask->id = current->id;
    strncpy(deletedTask->name, current->name, MAX_NAME_LENGTH - 1);
    deletedTask->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(deletedTask->deadline, current->deadline, MAX_DEADLINE_LENGTH - 1);
    deletedTask->deadline[MAX_DEADLINE_LENGTH - 1] = '\0';
    deletedTask->priority = current->priority;
    deletedTask->done = current->done;

    deletedTask->next = *undoStack;
    *undoStack = deletedTask;

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Task deleted.\n");
}

void undoDelete(Task **head, UndoNode **undoStack) {
    UndoNode *top;
    Task *restoredTask;

    if (undoStack == NULL || *undoStack == NULL) {
        printf("No deleted task to undo.\n");
        return;
    }

    restoredTask = (Task *)malloc(sizeof(Task));
    if (restoredTask == NULL) {
        printf("Unable to undo delete. Memory allocation failed.\n");
        return;
    }

    top = *undoStack;
    *undoStack = top->next;

    restoredTask->id = top->id;
    strncpy(restoredTask->name, top->name, MAX_NAME_LENGTH - 1);
    restoredTask->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(restoredTask->deadline, top->deadline, MAX_DEADLINE_LENGTH - 1);
    restoredTask->deadline[MAX_DEADLINE_LENGTH - 1] = '\0';
    restoredTask->priority = top->priority;
    restoredTask->done = top->done;

    restoredTask->next = *head;
    *head = restoredTask;

    free(top);
    printf("Deleted task restored.\n");
}

void sortTasksByPriority(Task **head) {
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

            if (first->priority < second->priority) {
                first->next = second->next;
                second->next = first;
                *current = second;
                swapped = 1;
            }

            current = &((*current)->next);
        }
    } while (swapped);
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
