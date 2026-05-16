# CPE112 Final Project: Task Management System

## Project Description
This project is a menu-driven task management system implemented in C. It helps users manage tasks by adding, deleting, searching, displaying, sorting, and restoring recently deleted tasks. The system also saves task data to `tasks.txt` so the task list can be loaded again when the program restarts.

The project applies dynamic memory, pointers, linked lists, stack behavior, modular functions, file handling, searching, and merge sort to solve a practical task organization problem.

## Features
- Add tasks with name, deadline, and priority
- Display all tasks in a table format
- Search tasks by exact task name
- Delete tasks by task ID
- Undo the most recent deleted task
- Sort tasks by priority
- Sort tasks by nearest deadline
- Save and load tasks from `tasks.txt`
- Validate deadline format as `DD-MM-YYYY`

## Team Members
- Chaiwat Mitranon -           68070503416 - GitHub: `winnchaiwat-hash`
- Phrommin Gatwatananitiporn - 68070503442 - GitHub: `chokub`
- Phudit Wongviriyasit -       68070503447 - GitHub: `Poooooooooooooh`


## How to Run

### Prerequisites
- GCC compiler, such as TDM-GCC or MinGW on Windows
- C standard library

### Compilation
Run this command in the project directory:

```bash
gcc main.c TaskManager.c -o task_manager.exe
```

### Execution
Run the executable:

```bash
task_manager.exe
```

Then follow the menu options shown in the command-line interface.

## Functional Requirements Coverage
- Add / Insert data: `addTask`
- Delete data: `deleteTask`
- Search functionality: `searchTask`
- Display / visualization: `displayTasks` prints all tasks in CLI table format
- Algorithmic component: merge sort for sorting tasks by priority and deadline
- Dynamic memory and pointers: `malloc`, `free`, `Task *`, `UndoNode *`
- Modular functions: task operations are separated into `TaskManager.c` and declared in `TaskManager.h`
- Menu-driven program: `main.c` provides a repeated user menu
- Input validation: `main.c` validates menu choices, deadline format, priority range, and task IDs
- File persistence: `saveTasks` and `loadTasks` store and restore task data from `tasks.txt`

## Data Structures Used

### 1. Singly Linked List
The main task list uses a singly linked list. Each `Task` node stores the task ID, name, deadline, priority, and a pointer to the next task.

Why this structure is suitable:
The number of tasks is not fixed. A linked list can grow and shrink during runtime through dynamic memory allocation.

Advantages:
- Efficient insertion when adding a new node without resizing a fixed array
- Efficient deletion after the target node is found by changing pointer links
- Good fit for a CLI task list where tasks are frequently added and removed

Time complexity:
- Add at end: `O(n)` because the program traverses to the last node
- Delete by ID: `O(n)` because the program searches for the matching task ID
- Display all tasks: `O(n)`
- Search by name: `O(n)`

Comparison with array:
An array provides `O(1)` indexed access, but the task count must be fixed or reallocated when the array becomes full. A linked list is more flexible because memory is allocated only when a task is added. For this project, dynamic size and easier deletion are more important than random access by index.

### 2. Stack
The undo feature uses a stack implemented with linked nodes through the `UndoNode` structure. When a task is deleted, its data is pushed onto the top of the undo stack. When the user selects undo, the most recently deleted task is popped and restored.

Why this structure is suitable:
Undo operations naturally follow Last-In, First-Out behavior. The last deleted task should be the first task restored.

Advantages:
- Matches the expected behavior of undo functionality
- Push and pop operations only modify the top node
- Can grow dynamically based on how many delete operations are stored

Time complexity:
- Push deleted task: `O(1)`
- Pop and restore task: `O(1)`

Comparison with queue:
A queue uses First-In, First-Out behavior, which would restore the oldest deleted task first. That would feel incorrect for undo because users normally expect the latest action to be undone first. Therefore, a stack is more suitable than a queue.

## Algorithms Implemented

### Linear Search
The program searches for a task by comparing the target task name with each node in the linked list.

Time complexity: `O(n)`

Reason for use:
The task list is stored as a linked list, so sequential traversal is simple and works well for moderate task sizes.

Alternative:
A hash table could improve average search time to `O(1)`, but it would require extra memory and additional collision handling. For this version, linear search keeps the implementation clear while still satisfying the search requirement.

### Merge Sort on Linked List
The program sorts tasks by priority and deadline using merge sort. Merge sort divides the linked list into smaller lists, recursively sorts them, and merges them back in the correct order.

Time complexity: `O(n log n)`

Reason for use:
Merge sort is suitable for linked lists because it can rearrange nodes by changing pointers instead of relying on random index access.

Alternative:
Bubble sort is easier to implement, but it has `O(n^2)` time complexity and becomes inefficient as the number of tasks increases. Merge sort is more appropriate for an intermediate-level project because it is more efficient and demonstrates divide-and-conquer algorithm design.

### Deadline Validation
The program validates the deadline format and checks whether the day, month, and leap year are valid.

Time complexity: `O(1)` because the deadline string length is fixed.

## File Structure
- `main.c`: Handles menu input and user interaction
- `TaskManager.c`: Implements task operations, sorting, searching, file saving, and memory cleanup
- `TaskManager.h`: Contains structure definitions and function declarations
- `tasks.txt`: Stores task data between program runs

## Sample Input / Output

### Main Menu

```text
Task Management System
1. Add task
2. Display tasks
3. Delete task
4. Undo delete
5. Sort by priority
6. Sort by deadline
7. Search task
0. Exit
Choose an option:
```

### Add Task with Validation

```text
Choose an option: 1
Enter task name (or type cancel to return): Study Data Structures
Enter deadline (DD-MM-YYYY) or type cancel to return: 15052026
Invalid deadline format.
Enter deadline (DD-MM-YYYY) or type cancel to return: 15-05-2026
Enter priority (1-5) or type cancel to return: 8
Priority must be between 1 and 5.
Enter priority (1-5) or type cancel to return: 2
Task added.
```

### Display Tasks

```text
Choose an option: 2

ID    Name                           Deadline           Priority
------------------------------------------------------------------
1     Study Data Structures           15-05-2026         2
```

### Search Task

```text
Choose an option: 7
Enter task name to search (or type cancel to return): Study Data Structures

ID    Name                           Deadline           Priority
------------------------------------------------------------------
1     Study Data Structures           15-05-2026         2
```

### Delete and Undo

```text
Choose an option: 3
Enter task ID to delete (or type cancel to return): 1
Task deleted.

Choose an option: 4
Deleted task restored.
```

### Sort Tasks

```text
Choose an option: 5
Tasks sorted by priority.

Choose an option: 6
Tasks sorted by nearest deadline.
```

### Exit

```text
Choose an option: 0
```

## Key Code Explanation

- `main.c` controls the menu loop, reads user input, validates invalid values, and calls task operations.
- `readLine` reads user input safely and removes the trailing newline.
- `addTask` dynamically allocates a new `Task` node and appends it to the linked list.
- `deleteTask` removes a task by ID and pushes its data onto the undo stack.
- `undoDelete` pops the most recently deleted task from the stack and restores it to the task list.
- `searchTask` performs linear search by exact task name.
- `mergeSortTasks` sorts linked-list nodes by changing pointers instead of copying task data.
- `saveTasks` and `loadTasks` use file I/O to preserve task data between program runs.
- `freeTasks` and `freeUndoStack` release dynamically allocated memory before the program exits.

## GitHub Contribution Evidence

The repository commit history shows work from multiple GitHub accounts. Each member is expected to understand the full codebase and be able to explain the data structures, algorithms, and menu flow during the presentation.

## Limitations and Future Improvements
- Search currently requires an exact task name
- Deleted tasks can be restored in Last-In, First-Out order during the current program session only
- Future versions could add hash table search, partial keyword search, task categories, or a graphical interface
