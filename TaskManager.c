#include "TaskManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASKS_FILE "tasks.txt"

static int isLeapYear(int year)
{
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

static int parseDeadline(const char deadline[], int *day, int *month, int *year)
{
    int i;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (strlen(deadline) != 10 || deadline[2] != '-' || deadline[5] != '-')
    {
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            continue;
        }

        if (deadline[i] < '0' || deadline[i] > '9')
        {
            return 0;
        }
    }

    *day = ((deadline[0] - '0') * 10) + (deadline[1] - '0');
    *month = ((deadline[3] - '0') * 10) + (deadline[4] - '0');
    *year = ((deadline[6] - '0') * 1000) + ((deadline[7] - '0') * 100) +
            ((deadline[8] - '0') * 10) + (deadline[9] - '0');

    if (*year < 1 || *month < 1 || *month > 12)
    {
        return 0;
    }

    if (*month == 2 && isLeapYear(*year))
    {
        daysInMonth[1] = 29;
    }

    if (*day < 1 || *day > daysInMonth[*month - 1])
    {
        return 0;
    }

    return 1;
}

int isValidDeadline(const char deadline[])
{
    int day;
    int month;
    int year;

    return parseDeadline(deadline, &day, &month, &year);
}

static int deadlineValue(const char deadline[])
{
    int day;
    int month;
    int year;

    if (!parseDeadline(deadline, &day, &month, &year))
    {
        return 99999999;
    }

    return (year * 10000) + (month * 100) + day;
}

static void splitList(Task *source, Task **front, Task **back)
{
    Task *slow;
    Task *fast;

    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

static int compareByPriority(Task *left, Task *right)
{
    if (left->priority != right->priority)
    {
        return left->priority > right->priority;
    }

    return left->id < right->id;
}

static int compareByDeadline(Task *left, Task *right)
{
    int leftDeadline = deadlineValue(left->deadline);
    int rightDeadline = deadlineValue(right->deadline);

    if (leftDeadline != rightDeadline)
    {
        return leftDeadline < rightDeadline;
    }

    return left->id < right->id;
}

static Task *mergeSortedLists(Task *left, Task *right, int (*comesFirst)(Task *, Task *))
{
    Task *result;

    if (left == NULL)
    {
        return right;
    }

    if (right == NULL)
    {
        return left;
    }

    if (comesFirst(left, right))
    {
        result = left;
        result->next = mergeSortedLists(left->next, right, comesFirst);
    }
    else
    {
        result = right;
        result->next = mergeSortedLists(left, right->next, comesFirst);
    }

    return result;
}

static void mergeSortTasks(Task **head, int (*comesFirst)(Task *, Task *))
{
    Task *current;
    Task *left;
    Task *right;

    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return;
    }

    current = *head;
    splitList(current, &left, &right);

    mergeSortTasks(&left, comesFirst);
    mergeSortTasks(&right, comesFirst);

    *head = mergeSortedLists(left, right, comesFirst);
}

void addTask(Task **head, int *nextId, const char name[], const char deadline[], int priority)
{
    Task *newTask = (Task *)malloc(sizeof(Task));
    Task *current;

    if (newTask == NULL)
    {
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

    if (*head == NULL)
    {
        *head = newTask;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newTask;
    }

    (*nextId)++;
}

void displayTasks(Task *head)
{
    Task *current = head;

    if (current == NULL)
    {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n%-5s %-30s %-18s %-10s\n", "ID", "Name", "Deadline", "Priority");
    printf("------------------------------------------------------------------\n");

    while (current != NULL)
    {
        printf("%-5d %-30s %-18s %-10d\n",
               current->id,
               current->name,
               current->deadline,
               current->priority);
        current = current->next;
    }
}

void deleteTask(Task **head, UndoNode **undoStack, int id)
{
    Task *current;
    Task *previous;
    UndoNode *deletedTask;

    if (head == NULL || *head == NULL)
    {
        printf("No tasks available to delete.\n");
        return;
    }

    current = *head;
    previous = NULL;

    while (current != NULL && current->id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Task with ID %d was not found.\n", id);
        return;
    }

    deletedTask = (UndoNode *)malloc(sizeof(UndoNode));
    if (deletedTask == NULL)
    {
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

    if (previous == NULL)
    {
        *head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    printf("Task deleted.\n");
}

void undoDelete(Task **head, UndoNode **undoStack)
{
    UndoNode *top;
    Task *restoredTask;

    if (undoStack == NULL || *undoStack == NULL)
    {
        printf("No deleted task to undo.\n");
        return;
    }

    restoredTask = (Task *)malloc(sizeof(Task));
    if (restoredTask == NULL)
    {
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

void sortTasksByPriority(Task **head)
{
    mergeSortTasks(head, compareByPriority);
}

void sortTasksByDeadline(Task **head)
{
    mergeSortTasks(head, compareByDeadline);
}

Task *searchTask(Task *head, const char name[])
{
    Task *current = head;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

int saveTasks(Task *head)
{
    FILE *file = fopen(TASKS_FILE, "w");
    Task *current = head;

    if (file == NULL)
    {
        printf("Unable to save tasks.\n");
        return 0;
    }

    while (current != NULL)
    {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                current->id,
                current->name,
                current->deadline,
                current->priority,
                current->done);
        current = current->next;
    }

    fclose(file);
    return 1;
}

int loadTasks(Task **head, int *nextId)
{
    FILE *file;
    Task *tail = NULL;
    char line[160];
    int highestId = 0;

    if (head == NULL || nextId == NULL)
    {
        return 0;
    }

    file = fopen(TASKS_FILE, "r");
    if (file == NULL)
    {
        *nextId = 1;
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        Task *newTask = (Task *)malloc(sizeof(Task));

        if (newTask == NULL)
        {
            printf("Unable to load all tasks. Memory allocation failed.\n");
            fclose(file);
            return 0;
        }

        newTask->next = NULL;

        if (sscanf(line, "%d|%79[^|]|%10[^|]|%d|%d",
                   &newTask->id,
                   newTask->name,
                   newTask->deadline,
                   &newTask->priority,
                   &newTask->done) != 5)
        {
            free(newTask);
            continue;
        }

        if (*head == NULL)
        {
            *head = newTask;
        }
        else
        {
            tail->next = newTask;
        }

        tail = newTask;

        if (newTask->id > highestId)
        {
            highestId = newTask->id;
        }
    }

    fclose(file);
    *nextId = highestId + 1;
    return 1;
}

void freeTasks(Task **head)
{
    Task *current;
    Task *next;

    if (head == NULL)
    {
        return;
    }

    current = *head;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

void freeUndoStack(UndoNode **undoStack)
{
    UndoNode *current;
    UndoNode *next;

    if (undoStack == NULL)
    {
        return;
    }

    current = *undoStack;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *undoStack = NULL;
}
