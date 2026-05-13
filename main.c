#include <stdio.h>
#include <string.h>
#include "TaskManager.h"

static void clearInput(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

static int taskIdExists(Task *head, int id)
{
    Task *current = head;

    while (current != NULL)
    {
        if (current->id == id)
        {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

static int readInt(const char prompt[], const char errorMessage[])
{
    int value;

    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1)
        {
            clearInput();
            return value;
        }

        printf("%s\n", errorMessage);
        clearInput();
    }
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
    char deadlineInput[MAX_NAME_LENGTH];
    int priority;
    int cancelled;
    Task *foundTask;

    loadTasks(&taskList, &nextId);

    while (running)
    {
        printf("\n========== Task Management System ==========\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Undo Delete\n");
        printf("5. Sort Tasks by Priority\n");
        printf("6. Sort Tasks by Deadline\n");
        printf("7. Search Task\n");
        printf("0. Save and Exit\n");

        do
        {
            choice = readInt("Choose an option: ",
                             "Invalid input. Please enter a number from 0 to 7.");

            if (choice < 0 || choice > 7)
            {
                printf("Invalid option. Please choose 0 to 7.\n");
            }
        } while (choice < 0 || choice > 7);

        switch (choice)
        {
        case 1:
            printf("Enter task name: ");
            scanf(" %79[^\n]", name);
            clearInput();

            do
            {
                printf("Enter deadline (DD-MM-YYYY only, include hyphens): ");
                scanf(" %79s", deadlineInput);
                clearInput();

                if (!isValidDeadline(deadlineInput))
                {
                    printf("Invalid deadline. Please use DD-MM-YYYY format only.\n");
                }
            } while (!isValidDeadline(deadlineInput));
            strcpy(deadline, deadlineInput);

            do
            {
                priority = readInt("Enter priority (1-5): ",
                                   "Invalid priority input. Please enter a number from 1 to 5.");

                if (priority < 1 || priority > 5)
                {
                    printf("Priority must be between 1 and 5.\n");
                }
            } while (priority < 1 || priority > 5);

            addTask(&taskList, &nextId, name, deadline, priority);
            saveTasks(taskList);
            printf("Task added.\n");
            break;
        case 2:
            displayTasks(taskList);
            break;
        case 3:
            if (taskList == NULL)
            {
                printf("No tasks available to delete.\n");
                break;
            }

            cancelled = 0;
            do
            {
                id = readInt("Enter task ID to delete (0 to cancel): ",
                             "Invalid task ID input. Please enter a number.");

                if (id == 0)
                {
                    cancelled = 1;
                    break;
                }

                if (!taskIdExists(taskList, id))
                {
                    printf("Task with ID %d was not found. Please try again.\n", id);
                }
            } while (!taskIdExists(taskList, id));

            if (cancelled)
            {
                printf("Delete cancelled.\n");
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
            if (taskList == NULL)
            {
                printf("No tasks available to search.\n");
                break;
            }

            cancelled = 0;
            do
            {
                printf("Enter task name to search (0 to cancel): ");
                scanf(" %79[^\n]", name);
                clearInput();

                if (strcmp(name, "0") == 0)
                {
                    cancelled = 1;
                    break;
                }

                foundTask = searchTask(taskList, name);
                if (foundTask == NULL)
                {
                    printf("Task named \"%s\" was not found. Please try again.\n", name);
                }
            } while (foundTask == NULL);

            if (cancelled)
            {
                printf("Search cancelled.\n");
                break;
            }

            printf("\n%-5s %-30s %-18s %-10s %-10s\n", "ID", "Name", "Deadline", "Priority", "Status");
            printf("--------------------------------------------------------------------------------\n");
            printf("%-5d %-30s %-18s %-10d %-10s\n",
                   foundTask->id,
                   foundTask->name,
                   foundTask->deadline,
                   foundTask->priority,
                   foundTask->done ? "Done" : "Pending");
            break;
        case 0:
            running = 0;
            break;
        }
    }

    if (saveTasks(taskList))
    {
        printf("Tasks saved. Goodbye.\n");
    }

    freeTasks(&taskList);
    freeUndoStack(&undoStack);

    return 0;
}
