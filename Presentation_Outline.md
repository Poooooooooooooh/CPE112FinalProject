# CPE112 Final Project: Task Manager Presentation Slides Outline

## Slide 1: Title Slide
- Project Title: CPE112 Final Project - Task Manager
- Team Members: [Your Name] (GitHub: Poooooooooooooh)
- Date: [Current Date]

## Slide 2: Team Members Information
- Name: [Your Full Name]
- Student ID: [If applicable]
- GitHub Username: Poooooooooooooh
- Contributions: Implemented all features, code development, testing

## Slide 3: Problem Description
- Problem: Need a simple task management system for personal use
- Requirements: Add, delete, search, display tasks; persist data; priority and deadlines
- Solution: C-based console application with linked list and file I/O

## Slide 4: System Design (Diagram/Flow)
- High-level architecture:
  - Main menu loop
  - Task operations (add, delete, search, display)
  - Data persistence via file
- Flowchart: [Describe or insert diagram]
  - Start -> Display Menu -> User Choice -> Perform Action -> Save to File -> Loop

## Slide 5: Data Structures Used
- Linked List: Dynamic storage for tasks (no fixed size limit)
- Justification: Efficient for insertions/deletions; suitable for variable number of tasks
- Task Struct: Fields - ID, title, description, priority, deadline

## Slide 6: Algorithms Implemented
- Linear Search: For finding tasks by title
- Bubble Sort: For sorting tasks by priority
- File I/O: Read/write tasks to text file for persistence
- Undo Stack: Simple array-based stack for delete undo

## Slide 7: Key Code Explanation
- Main Function: Menu loop and user input handling
- Add Task: Create new node, insert into linked list
- Delete Task: Find node, remove from list, push to undo stack
- Persistence: Write linked list to file on exit, read on start

## Slide 8: Sample Input/Output
- Input: Add task - Title: "Study", Desc: "Math homework", Priority: 3, Deadline: "2023-12-01"
- Output: Task added successfully
- Display: List of tasks with details
- Search: Input "Study" -> Output matching tasks

## Slide 9: Challenges & Improvements
- Challenges:
  - Date validation and parsing
  - Implementing undo without complex data structures
  - File I/O error handling
- Improvements:
  - Add GUI using GTK or similar
  - Better date handling with libraries
  - Multi-user support with database
  - Enhanced search with filters

## Slide 10: Conclusion
- Summary: Successfully implemented task manager with core features
- GitHub Link: https://github.com/Poooooooooooooh/CPE112FinalProject
- Commit Hash: 85fd919 (or relevant hash)
- Thank you!