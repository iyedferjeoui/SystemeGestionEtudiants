🎓 Système de Gestion des Étudiants — Version 2
A Student Management System written in C, developed and extended as part of my Computer Science studies at ISSAT Sousse.
Version 2 is a major upgrade over v1 — it introduces grades with automatic average calculation, file persistence, edit and delete operations, sorting, and class statistics, all built on top of a clean modular architecture with thorough input validation.

📋 Description
This program allows users to manage student records through an interactive console menu. It goes well beyond basic course requirements by implementing nested structs, dynamic file I/O, structured data modeling, and robust input validation — applying core C concepts in a practical, real-world project.

✨ Features
👤 Student Management

➕ Add new students (ID, full name, age, marks)
📋 Display all registered students
🔍 Search for a student by ID
✏️ Edit a student's marks
🗑️ Delete a student by ID (with automatic list shifting)

📊 Grades & Statistics

3 subject marks: Math, Physics, CS (validated 0–20)
Automatic average calculation on entry and update
PASS / FAIL status displayed per student
Class statistics: total students, pass/fail count, class average, best student

📂 File Operations

💾 Save student records to a .txt file
📂 Load student records from a .txt file at startup
Auto-appends .txt extension if missing
Skips duplicate IDs when loading to prevent data corruption

🔢 Sorting

Sort students by Average (highest first)
Sort students by ID (ascending)


🛠️ Concepts Used

struct with nested structs (Student contains Marks)
Pointers and pass-by-reference (*count, *s)
File I/O with fopen, fscanf, fprintf, fclose
Input validation for integers, floats, and names
Bubble Sort algorithm
Modular code design (each feature is its own function)
isalpha, fgets, strcspn for safe string handling


🆕 What's New in Version 2
Featurev1v2Save to file❌✅Load from file at startup❌✅Nested struct Marks (named fields)❌✅Safer input (fgets + isValidName)❌✅Duplicate ID check on file load❌✅Save prompt on exit❌✅

Note: v1 used a flat marks[3] array and realloc-based dynamic memory. v2 replaces this with a cleaner nested struct approach and static allocation, with the major addition being full file persistence.


🚀 How to Compile & Run
Make sure GCC is installed on your system.
Linux / macOS:
bashgcc etudiant.c -o etudiant
./etudiant
Windows:
bashgcc etudiant.c -o etudiant.exe
etudiant.exe

🖥️ Program Flow
On startup, you choose to either load existing data from a file or start with an empty list. You are then presented with the main menu:
==================================
   STUDENT MANAGEMENT SYSTEM
==================================
1. Show All Students
2. Add New Student
3. Search by ID
4. Edit Marks
5. Delete Student
6. Sort (by Avg)
7. Statistics
8. Save to File
0. Exit
==================================
When exiting, the program asks if you want to save before closing.

📁 Project Structure
SystemeGestionEtudiants/
├── etudiant.c       # Full source code (single file)
└── README.md

📄 File Format
Student data is saved and loaded using a simple pipe-separated format:
ID|Full Name|Age|Math|Physics|CS
Example:
1|Iyed Ferjeoui|20|17.50|15.00|18.00
2|Ali Ben Salah|21|12.00|14.50|11.00

🔮 Planned for Version 3

📊 Grade distribution chart (in terminal)
🌐 Web interface rewrite using Python / Flask
🗃️ Binary file format for more efficient storage
📤 Export to CSV for spreadsheet compatibility


👨‍💻 Author
Iyed Ferjeoui — CS Student at ISSAT Sousse, Tunisia
🔗 GitHub Profile
