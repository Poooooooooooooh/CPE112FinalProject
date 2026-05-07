#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_TASKS 100
#define MAX_NAME_LENGTH 80

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int done;
} Task;

int loadTasks(Task tasks[], int *count, int *nextId);
int saveTasks(Task tasks[], int count);
void addTask(Task tasks[], int *count, int *nextId);
void listTasks(Task tasks[], int count);

#endif
