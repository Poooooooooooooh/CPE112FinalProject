#include <stdio.h>
#include "TaskManager.h"

#define TASKS_FILE "tasks.txt"

int loadTasks(Task tasks[], int *count, int *nextId) {
    FILE *file = fopen(TASKS_FILE, "r");
    int maxId = 0;

    *count = 0;
    *nextId = 1;

    if (file == NULL) {
        return 0;
    }

    while (*count < MAX_TASKS &&
           fscanf(file, " %d|%79[^|]|%d",
                  &tasks[*count].id,
                  tasks[*count].name,
                  &tasks[*count].done) == 3) {
        if (tasks[*count].id > maxId) {
            maxId = tasks[*count].id;
        }

        (*count)++;
    }

    *nextId = maxId + 1;
    fclose(file);

    return 1;
}

int saveTasks(Task tasks[], int count) {
    FILE *file = fopen(TASKS_FILE, "w");
    int i;

    if (file == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%d\n", tasks[i].id, tasks[i].name, tasks[i].done);
    }

    fclose(file);

    return 1;
}
