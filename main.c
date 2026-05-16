#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TaskManager.h"

static int readLine(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) == NULL)
    {
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }

    return 1;
}

static int isCancelInput(const char *input)
{
    return input != NULL &&
           ((input[0] == 'c' || input[0] == 'C') &&
            (input[1] == 'a' || input[1] == 'A') &&
            (input[2] == 'n' || input[2] == 'N') &&
            (input[3] == 'c' || input[3] == 'C') &&
            (input[4] == 'e' || input[4] == 'E') &&
            (input[5] == 'l' || input[5] == 'L') &&
            input[6] == '\0');
}

int main(void)
{
    Task *taskList = NULL;
    UndoNode *undoStack = NULL;
    int choice;
    int id;
    int nextId = 1;
    int running = 1;
    char name[MAX_NAME_LENGTH];
    char deadline[MAX_DEADLINE_LENGTH];
    char input[32];
    int priority;
    Task *foundTask;

    loadTasks(&taskList, &nextId);

    while (running)
    {
        printf("\nTask Management System\n");
        printf("1. Add task\n");
        printf("2. Display tasks\n");
        printf("3. Delete task\n");
        printf("4. Undo delete\n");
        printf("5. Sort by priority\n");
        printf("6. Sort by deadline\n");
        printf("7. Search task\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (!readLine(input, sizeof(input)) || sscanf(input, "%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter task name (or type cancel to return): ");
            if (!readLine(name, sizeof(name)))
            {
                printf("Invalid input.\n");
                break;
            }

            if (isCancelInput(name))
            {
                printf("Add task canceled.\n");
                break;
            }

            if (name[0] == '\0')
            {
                printf("Task name cannot be empty.\n");
                break;
            }

            printf("Enter deadline (DD-MM-YYYY) or type cancel to return: ");
            if (!readLine(deadline, sizeof(deadline)))
            {
                printf("Invalid input.\n");
                break;
            }

            if (isCancelInput(deadline))
            {
                printf("Add task canceled.\n");
                break;
            }

            if (!isValidDeadline(deadline))
            {
                printf("Invalid deadline format.\n");
                break;
            }

            printf("Enter priority (1-5) or type cancel to return: ");
            if (!readLine(input, sizeof(input)))
            {
                printf("Invalid input.\n");
                break;
            }

            if (isCancelInput(input))
            {
                printf("Add task canceled.\n");
                break;
            }

            if (sscanf(input, "%d", &priority) != 1)
            {
                printf("Invalid priority input.\n");
                break;
            }

            if (priority < 1 || priority > 5)
            {
                printf("Priority must be between 1 and 5.\n");
                break;
            }

            addTask(&taskList, &nextId, name, deadline, priority);
            saveTasks(taskList);
            printf("Task added.\n");
            break;
        case 2:
            displayTasks(taskList);
            break;
        case 3:
            printf("Enter task ID to delete (or type cancel to return): ");
            if (!readLine(input, sizeof(input)))
            {
                printf("Invalid input.\n");
                break;
            }

            if (isCancelInput(input))
            {
                printf("Delete canceled.\n");
                break;
            }

            if (sscanf(input, "%d", &id) != 1)
            {
                printf("Invalid task ID input.\n");
                break;
            }

            deleteTask(&taskList, &undoStack, id);
            saveTasks(taskList);
            break;
        case 4:
            undoDelete(&taskList, &undoStack);
            saveTasks(taskList);
            break;
        case 5:
            sortTasksByPriority(&taskList);
            saveTasks(taskList);
            printf("Tasks sorted by priority.\n");
            displayTasks(taskList);
            break;
        case 6:
            sortTasksByDeadline(&taskList);
            saveTasks(taskList);
            printf("Tasks sorted by nearest deadline.\n");
            displayTasks(taskList);
            break;
        case 7:
            printf("Enter task name to search (or type cancel to return): ");
            if (!readLine(name, sizeof(name)))
            {
                printf("Invalid input.\n");
                break;
            }

            if (isCancelInput(name))
            {
                printf("Search canceled.\n");
                break;
            }

            foundTask = searchTask(taskList, name);
            if (foundTask == NULL)
            {
                printf("Task named \"%s\" was not found.\n", name);
            }
            else
            {
                printf("\n%-5s %-30s %-18s %-10s\n", "ID", "Name", "Deadline", "Priority");
                printf("------------------------------------------------------------------\n");
                printf("%-5d %-30s %-18s %-10d\n",
                       foundTask->id,
                       foundTask->name,
                       foundTask->deadline,
                       foundTask->priority);
            }
            break;
        case 0:
            running = 0;
            break;
        default:
            printf("Invalid option.\n");
            break;
        }
    }

    freeTasks(&taskList);
    freeUndoStack(&undoStack);

    return 0;
}
