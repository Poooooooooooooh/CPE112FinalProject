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
- Chaiwat  Mitranon          68070503416
- Phrommin Gatwatananitiporn 68070503442
- Phudit   Wongviriyasit     68070503447


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

## Data Structures Used

### 1. Singly Linked List
The main task list uses a singly linked list. Each `Task` node stores the task ID, name, deadline, priority, status, and a pointer to the next task.

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

Example actions:
- Add a task: enter task name, deadline in `DD-MM-YYYY`, and priority from 1 to 5
- Display tasks: show all tasks in the current linked list
- Search task: enter an exact task name
- Delete task: enter task ID
- Undo delete: restore the most recently deleted task
- Sort by priority: higher priority appears first
- Sort by deadline: nearest deadline appears first

## Limitations and Future Improvements
- Search currently requires an exact task name
- Deleted tasks can be restored in Last-In, First-Out order during the current program session only
- Future versions could add hash table search, partial keyword search, task categories, or a graphical interface
