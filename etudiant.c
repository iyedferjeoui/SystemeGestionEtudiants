#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 200
#define MAX_NAME_LEN 50

/* --- STRUCTURES --- */

// A simple struct to hold the 3 marks clearly
struct Marks {
    float math;
    float physics;
    float cs;
};

// The main Student struct containing the Marks struct
struct Student {
    int id;
    char fullName[MAX_NAME_LEN];
    int age;
    struct Marks marks;
    float average;
};

/* --- HELPER FUNCTIONS --- */

// Clears the input buffer (prevents skipping inputs)
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Waits for user to press Enter
void waitEnter() {
    printf("\n[Press Enter to continue...]");
    clearInput();
}

// Calculates average from the nested struct
float calculateAverage(struct Marks m) {
    return (m.math + m.physics + m.cs) / 3.0;
}

// Checks if an ID already exists in the list
int isIdTaken(int id, struct Student list[], int count) {
    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            return 1; // True, ID exists
        }
    }
    return 0; // False, ID is free
}

// Finds the index of a student by ID. Returns -1 if not found.
int findStudentIndex(struct Student list[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Swaps two students (used for sorting)
void swapStudents(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

/* --- INPUT VALIDATION --- */

// Checks if name contains only valid characters
int isValidName(char *name) {
    if (name[0] == '\0') return 0;
    
    for (int i = 0; name[i] != '\0'; i++) {
        char c = name[i];
        // Allow letters, spaces, hyphens, and apostrophes
        if (!isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            return 0;
        }
    }
    return 1;
}

// Gets a valid name from user
void getName(char *prompt, char *buffer) {
    while (1) {
        printf("%s", prompt);
        fgets(buffer, MAX_NAME_LEN, stdin);
        
        // Remove newline character
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }

        if (isValidName(buffer)) {
            return; // Valid name
        }
        printf("  ! Invalid name. Use letters only.\n");
    }
}

// Gets a valid integer from user
int getInt(char *prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1) {
            clearInput();
            return value;
        }
        printf("  ! Please enter a whole number.\n");
        clearInput();
    }
}

// Gets a valid float (decimal) from user
float getFloat(char *prompt) {
    float value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &value) == 1) {
            clearInput();
            return value;
        }
        printf("  ! Please enter a number.\n");
        clearInput();
    }
}

/* --- CORE FEATURES --- */

// Add one student manually
void addOneStudent(struct Student *s, struct Student list[], int currentCount) {
    // 1. Get Unique ID
    while (1) {
        s->id = getInt("Enter ID: ");
        if (!isIdTaken(s->id, list, currentCount)) {
            break;
        }
        printf("  ! ID %d already exists. Try again.\n", s->id);
    }

    // 2. Get Name
    getName("Enter Full Name: ", s->fullName);

    // 3. Get Age (5 to 100)
    while (1) {
        s->age = getInt("Enter Age: ");
        if (s->age >= 5 && s->age <= 100) {
            break;
        }
        printf("  ! Age must be between 5 and 100.\n");
    }

    // 4. Get Marks (0 to 20) using the nested struct
    printf("Enter Marks (0-20):\n");
    
    s->marks.math = getFloat("  Math: ");
    s->marks.physics = getFloat("  Physics: ");
    s->marks.cs = getFloat("  CS: ");

    // Validate marks range
    while (s->marks.math < 0 || s->marks.math > 20 ||
           s->marks.physics < 0 || s->marks.physics > 20 ||
           s->marks.cs < 0 || s->marks.cs > 20) {
        printf("  ! Marks must be between 0 and 20.\n");
        s->marks.math = getFloat("  Math: ");
        s->marks.physics = getFloat("  Physics: ");
        s->marks.cs = getFloat("  CS: ");
    }

    // 5. Calculate Average
    s->average = calculateAverage(s->marks);
}

// Display one student details
void printStudent(struct Student s) {
    printf("----------------------------\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.fullName);
    printf("Age: %d\n", s.age);
    printf("Marks -> Math: %.2f, Physics: %.2f, CS: %.2f\n", 
           s.marks.math, s.marks.physics, s.marks.cs);
    printf("Average: %.2f %s\n", s.average, s.average >= 10 ? "[PASS]" : "[FAIL]");
}

// Display all students
void showAll(int count, struct Student list[]) {
    if (count == 0) {
        printf("No students in the list.\n");
        return;
    }
    printf("\n=== STUDENT LIST (%d) ===\n", count);
    for (int i = 0; i < count; i++) {
        printf("\n[Student %d]\n", i + 1);
        printStudent(list[i]);
    }
}

/* --- FILE OPERATIONS --- */

// Load from file
int loadFromFile(struct Student list[], int *count) {
    char filename[100];
    printf("Enter filename (e.g., data.txt): ");
    fgets(filename, 100, stdin);
    // Remove newline from filename
    filename[strcspn(filename, "\n")] = 0;

    // Add .txt if missing
    if (strstr(filename, ".txt") == NULL) {
        strcat(filename, ".txt");
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("  ! Could not open file '%s'.\n", filename);
        return 0;
    }

    int loaded = 0;
    // Read until end of file or list is full
    while (!feof(file) && *count + loaded < MAX_STUDENTS) {
        struct Student temp;
        // Format: ID|Name|Age|Math|Physics|CS
        int result = fscanf(file, "%d|%[^|]|%d|%f|%f|%f\n", 
                            &temp.id, temp.fullName, &temp.age, 
                            &temp.marks.math, &temp.marks.physics, &temp.marks.cs);

        if (result == 6) {
            // Check for duplicate ID before adding
            if (!isIdTaken(temp.id, list, *count + loaded)) {
                temp.average = calculateAverage(temp.marks);
                list[*count + loaded] = temp;
                loaded++;
            }
        } else {
            char dummy[256];
            fgets(dummy, 256, file);
        }
    }

    fclose(file);
    printf("  > Successfully loaded %d students.\n", loaded);
    *count += loaded;
    return loaded > 0;
}

// Save to file
void saveToFile(struct Student list[], int count) {
    if (count == 0) {
        printf("Nothing to save.\n");
        return;
    }

    char filename[100];
    printf("Enter filename to save: ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = 0;

    if (strstr(filename, ".txt") == NULL) {
        strcat(filename, ".txt");
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("  ! Could not create file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%d|%.2f|%.2f|%.2f\n", 
                list[i].id, list[i].fullName, list[i].age,
                list[i].marks.math, list[i].marks.physics, list[i].marks.cs);
    }

    fclose(file);
    printf("  > Saved %d students to '%s'.\n", count, filename);
}

/* --- SORTING (Bubble Sort) --- */
void sortById(int count, struct Student list[]) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (list[j].id > list[j+1].id) {
                swapStudents(&list[j], &list[j+1]);
            }
        }
    }
    printf("Sorted by ID.\n");
    showAll(count, list);
}

void sortByAverage(int count, struct Student list[]) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (list[j].average < list[j+1].average) { // Higher average first
                swapStudents(&list[j], &list[j+1]);
            }
        }
    }
    printf("Sorted by Average.\n");
    showAll(count, list);
}

/* --- SEARCH --- */
void searchById(int count, struct Student list[]) {
    int id = getInt("Enter ID to search: ");
    int index = findStudentIndex(list, count, id);

    if (index == -1) {
        printf("Student with ID %d not found.\n", id);
    } else {
        printStudent(list[index]);
    }
}

/* --- STATISTICS --- */
void showStats(int count, struct Student list[]) {
    if (count == 0) {
        printf("No data available.\n");
        return;
    }

    float totalAvg = 0;
    int passCount = 0;
    int bestIndex = 0;

    for (int i = 0; i < count; i++) {
        totalAvg += list[i].average;
        if (list[i].average >= 10) passCount++;
        if (list[i].average > list[bestIndex].average) {
            bestIndex = i;
        }
    }

    printf("\n=== STATISTICS ===\n");
    printf("Total Students: %d\n", count);
    printf("Passed: %d | Failed: %d\n", passCount, count - passCount);
    printf("Class Average: %.2f\n", totalAvg / count);
    printf("Best Student: %s (Avg: %.2f)\n", list[bestIndex].fullName, list[bestIndex].average);
}

/* --- EDIT --- */
void editStudent(int count, struct Student list[]) {
    int id = getInt("Enter ID to edit: ");
    int index = findStudentIndex(list, count, id);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Editing student: %s\n", list[index].fullName);
    
    // Re-enter marks only (keeping ID and Name safe)
    printf("Enter new marks (0-20):\n");
    list[index].marks.math = getFloat("  Math: ");
    list[index].marks.physics = getFloat("  Physics: ");
    list[index].marks.cs = getFloat("  CS: ");

    while (list[index].marks.math < 0 || list[index].marks.math > 20 ||
           list[index].marks.physics < 0 || list[index].marks.physics > 20 ||
           list[index].marks.cs < 0 || list[index].marks.cs > 20) {
        printf("  ! Marks must be 0-20.\n");
        list[index].marks.math = getFloat("  Math: ");
        list[index].marks.physics = getFloat("  Physics: ");
        list[index].marks.cs = getFloat("  CS: ");
    }

    list[index].average = calculateAverage(list[index].marks);
    printf("Student updated successfully.\n");
}

/* --- DELETE --- */
void deleteStudent(int *count, struct Student list[]) {
    int id = getInt("Enter ID to delete: ");
    int index = findStudentIndex(list, *count, id);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    // Shift all students after the deleted one to the left
    for (int i = index; i < *count - 1; i++) {
        list[i] = list[i+1];
    }
    
    (*count)--;
    printf("Student deleted.\n");
}

/* --- MAIN MENU --- */
void runMenu(int *count, struct Student list[]) {
    while (1) {
        printf("\n==================================\n");
        printf("   STUDENT MANAGEMENT SYSTEM\n");
        printf("==================================\n");
        printf("1. Show All Students\n");
        printf("2. Add New Student\n");
        printf("3. Search by ID\n");
        printf("4. Edit Marks\n");
        printf("5. Delete Student\n");
        printf("6. Sort (by Avg)\n");
        printf("7. Statistics\n");
        printf("8. Save to File\n");
        printf("0. Exit\n");
        printf("==================================\n");

        int choice = getInt("Choice: ");

        if (choice == 1) {
            showAll(*count, list);
        }
        else if (choice == 2) {
            if (*count < MAX_STUDENTS) {
                printf("\n--- Add New Student ---\n");
                addOneStudent(&list[*count], list, *count);
                (*count)++;
                printf("Student added!\n");
            } else {
                printf("List is full!\n");
            }
        }
        else if (choice == 3) {
            searchById(*count, list);
        }
        else if (choice == 4) {
            editStudent(*count, list);
        }
        else if (choice == 5) {
            deleteStudent(count, list);
        }
        else if (choice == 6) {
            sortByAverage(*count, list);
        }
        else if (choice == 7) {
            showStats(*count, list);
        }
        else if (choice == 8) {
            saveToFile(list, *count);
        }
        else if (choice == 0) {
            int save = getInt("Save before exit? (1=Yes, 0=No): ");
            if (save == 1) saveToFile(list, *count);
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
        
        if (choice != 0) waitEnter();
    }
}

int main() {
    struct Student list[MAX_STUDENTS];
    int count = 0;

    printf("=== WELCOME ===\n");
    printf("1. Load from File\n");
    printf("2. Start Empty (Manual Entry)\n");
    int startChoice = getInt("Choice: ");

    if (startChoice == 1) {
        loadFromFile(list, &count);
    }

    // Start the main program loop
    runMenu(&count, list);

    return 0;
}
