#include <stdio.h>
#include "TaskManager.h"

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

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice)
        {
        case 1:
            printf("Enter task name: ");
            scanf(" %79[^\n]", name);

            printf("Enter deadline (DD-MM-YYYY): ");
            scanf(" %10s", deadline);

            printf("Enter priority (1-5): ");
            if (scanf("%d", &priority) != 1)
            {
                printf("Invalid priority input.\n");
                return 1;
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
            printf("Enter task ID to delete: ");
            if (scanf("%d", &id) != 1)
            {
                printf("Invalid task ID input.\n");
                return 1;
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
            printf("Enter task name to search: ");
            scanf(" %79[^\n]", name);

            foundTask = searchTask(taskList, name);
            if (foundTask == NULL)
            {
                printf("Task named \"%s\" was not found.\n", name);
            }
            else
            {
                printf("\n%-5s %-30s %-18s %-10s %-10s\n", "ID", "Name", "Deadline", "Priority", "Status");
                printf("--------------------------------------------------------------------------------\n");
                printf("%-5d %-30s %-18s %-10d %-10s\n",
                       foundTask->id,
                       foundTask->name,
                       foundTask->deadline,
                       foundTask->priority,
                       foundTask->done ? "Done" : "Pending");
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
