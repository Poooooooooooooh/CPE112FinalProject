#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_NAME_LENGTH 80
#define MAX_DEADLINE_LENGTH 11

typedef struct Task {
    int id;
    char name[MAX_NAME_LENGTH];
    char deadline[MAX_DEADLINE_LENGTH];
    int priority;
    int done;
    struct Task *next;
} Task;

typedef struct UndoNode {
    int id;
    char name[MAX_NAME_LENGTH];
    char deadline[MAX_DEADLINE_LENGTH];
    int priority;
    int done;
    struct UndoNode *next;
} UndoNode;

void addTask(Task **head, int *nextId, const char name[], const char deadline[], int priority);
void displayTasks(Task *head);
void deleteTask(Task **head, UndoNode **undoStack, int id);
void undoDelete(Task **head, UndoNode **undoStack);
void sortTasksByPriority(Task **head);
void sortTasksByDeadline(Task **head);
Task *searchTask(Task *head, const char name[]);
int isValidDeadline(const char deadline[]);
int saveTasks(Task *head);
int loadTasks(Task **head, int *nextId);
void freeTasks(Task **head);
void freeUndoStack(UndoNode **undoStack);

#endif
