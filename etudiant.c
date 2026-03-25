#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SUBJECTS 3

/* ============================================================
   STRUCT
   ============================================================ */
struct Student {
    int   id;
    char  fullName[50];
    int   age;
    float marks[NUM_SUBJECTS];  /* Math, Physics, CS */
    float average;              /* auto-calculated from marks */
};

/* ============================================================
   UTILITIES
   ============================================================ */
void separator() {
    printf("==========================================\n");
}

void pressEnter() {
    printf("\n[Press Enter to continue...]");
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();}
float calcAverage(float marks[]) {
    float sum = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++)
        sum += marks[i];
    return sum / NUM_SUBJECTS;
}

int idExists(int id, struct Student *list, int count) {
    for (int i = 0; i < count; i++)
        if (list[i].id == id) return 1;
    return 0;
}

int findById(struct Student *list, int count, int id) {
    for (int i = 0; i < count; i++)
        if (list[i].id == id) return i;
    return -1;
}

void swapStudents(struct Student *a, struct Student *b) {
    struct Student tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ============================================================
   INPUT
   ============================================================ */
char *subjects[NUM_SUBJECTS] = {"Math", "Physics", "CS"};

void inputStudent(struct Student *s, struct Student *list, int count) {
    printf("ID           : ");
    scanf("%d", &s->id);
    while (idExists(s->id, list, count)) {
        printf("  ! ID already used, enter a unique ID : ");
        scanf("%d", &s->id);
    }

    printf("Full name    : ");
    scanf(" %49[^\n]", s->fullName);

    printf("Age          : ");
    scanf("%d", &s->age);
    while (s->age < 5 || s->age > 100) {
        printf("  ! Invalid age (5-100) : ");
        scanf("%d", &s->age);
    }

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%-8s mark : ", subjects[i]);
        scanf("%f", &s->marks[i]);
        while (s->marks[i] < 0 || s->marks[i] > 20) {
            printf("  ! Invalid mark (0-20) : ");
            scanf("%f", &s->marks[i]);
        }
    }

    s->average = calcAverage(s->marks);
}

void askCount(int *n) {
    do {
        printf("Number of students : ");
        scanf("%d", n);
    } while (*n <= 0);
}

void fillList(int n, struct Student *list) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        inputStudent(&list[i], list, i);
    }
}

/* ============================================================
   DISPLAY
   ============================================================ */
void printStudent(struct Student s) {
    printf("  ID       : %d\n", s.id);
    printf("  Name     : %s\n", s.fullName);
    printf("  Age      : %d\n", s.age);
    for (int i = 0; i < NUM_SUBJECTS; i++)
        printf("  %-8s : %.2f\n", subjects[i], s.marks[i]);
    printf("  Average  : %.2f  %s\n", s.average, s.average >= 10 ? "[PASS]" : "[FAIL]");
    printf("------------------------------------------\n");
}

void printAll(int n, struct Student *list) {
    separator();
    printf("   STUDENT LIST (%d)\n", n);
    separator();
    for (int i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        printStudent(list[i]);
    }
}

void printByOrder(int n, struct Student *list) {
    separator();
    printf("   STUDENTS BY ENTRY ORDER\n");
    separator();
    for (int i = 0; i < n; i++)
        printf("[%d] %-20s  ID:%-4d  Age:%-3d  Avg:%.2f  %s\n",
               i + 1, list[i].fullName, list[i].id, list[i].age,
               list[i].average, list[i].average >= 10 ? "[PASS]" : "[FAIL]");
}

/* ============================================================
   SORT  (bubble sort)
   ============================================================ */
void sortById(int n, struct Student *list) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (list[j].id > list[j+1].id)
                swapStudents(&list[j], &list[j+1]);
    printf("Sorted by ID.\n");
    printAll(n, list);
}

void sortByName(int n, struct Student *list) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(list[j].fullName, list[j+1].fullName) > 0)
                swapStudents(&list[j], &list[j+1]);
    printf("Sorted by name.\n");
    printAll(n, list);
}

void sortByAge(int n, struct Student *list) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (list[j].age > list[j+1].age)
                swapStudents(&list[j], &list[j+1]);
    printf("Sorted by age.\n");
    printAll(n, list);
}

void sortByAverage(int n, struct Student *list) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (list[j].average > list[j+1].average)
                swapStudents(&list[j], &list[j+1]);
    printf("Sorted by average.\n");
    printAll(n, list);
}

/* ============================================================
   SEARCH
   ============================================================ */
void searchById(int n, struct Student *list) {
    int id;
    printf("ID to search : ");
    scanf("%d", &id);
    int idx = findById(list, n, id);
    if (idx == -1)
        printf("No student with ID %d.\n", id);
    else
        printStudent(list[idx]);
}

void searchByName(int n, struct Student *list) {
    char name[50];
    printf("Name to search : ");
    scanf(" %49[^\n]", name);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strstr(list[i].fullName, name)) {
            printStudent(list[i]);
            found = 1;
        }
    }
    if (!found)
        printf("No student named '%s'.\n", name);
}

void searchByAge(int n, struct Student *list) {
    int age;
    printf("Age to search : ");
    scanf("%d", &age);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (list[i].age == age) {
            printStudent(list[i]);
            found = 1;
        }
    }
    if (!found)
        printf("No student aged %d.\n", age);
}

/* ============================================================
   STATISTICS
   ============================================================ */
void printStats(int n, struct Student *list) {
    float sumAge = 0, sumAvg = 0;
    int oldest = 0, youngest = 0, best = 0, worst = 0, passed = 0;

    for (int i = 0; i < n; i++) {
        sumAge += list[i].age;
        sumAvg += list[i].average;
        if (list[i].age     > list[oldest].age)       oldest   = i;
        if (list[i].age     < list[youngest].age)      youngest = i;
        if (list[i].average > list[best].average)      best     = i;
        if (list[i].average < list[worst].average)     worst    = i;
        if (list[i].average >= 10) passed++;
    }

    separator();
    printf("   STATISTICS\n");
    separator();
    printf("Total students   : %d\n",       n);
    printf("Passed / Failed  : %d / %d\n",  passed, n - passed);
    printf("Average age      : %.2f\n",     sumAge / n);
    printf("Oldest           : %s (%d)\n",  list[oldest].fullName,   list[oldest].age);
    printf("Youngest         : %s (%d)\n",  list[youngest].fullName, list[youngest].age);
    printf("Class average    : %.2f\n",     sumAvg / n);
    printf("Best student     : %s (%.2f)\n",list[best].fullName,     list[best].average);
    printf("Worst student    : %s (%.2f)\n",list[worst].fullName,    list[worst].average);
    separator();
}

/* ============================================================
   FILTER
   ============================================================ */
void showAdults(int n, struct Student *list) {
    printf("\n--- Adults (>= 18) ---\n");
    int found = 0;
    for (int i = 0; i < n; i++)
        if (list[i].age >= 18) { printStudent(list[i]); found = 1; }
    if (!found) printf("No adult students.\n");
}

void showMinors(int n, struct Student *list) {
    printf("\n--- Minors (< 18) ---\n");
    int found = 0;
    for (int i = 0; i < n; i++)
        if (list[i].age < 18) { printStudent(list[i]); found = 1; }
    if (!found) printf("No minor students.\n");
}

void showOlderThan(int n, struct Student *list) {
    int threshold;
    printf("Minimum age : ");
    scanf("%d", &threshold);
    printf("\n--- Age > %d ---\n", threshold);
    int found = 0;
    for (int i = 0; i < n; i++)
        if (list[i].age > threshold) { printStudent(list[i]); found = 1; }
    if (!found) printf("No student older than %d.\n", threshold);
}

/* ============================================================
   EDIT
   ============================================================ */
void editAge(int n, struct Student *list) {
    int id;
    printf("Student ID : ");
    scanf("%d", &id);
    int idx = findById(list, n, id);
    if (idx == -1) { printf("ID not found.\n"); return; }
    printf("New age : ");
    scanf("%d", &list[idx].age);
    while (list[idx].age < 5 || list[idx].age > 100) {
        printf("  ! Invalid age (5-100) : ");
        scanf("%d", &list[idx].age);
    }
    printf("Age updated.\n");
}

void editName(int n, struct Student *list) {
    int id;
    printf("Student ID : ");
    scanf("%d", &id);
    int idx = findById(list, n, id);
    if (idx == -1) { printf("ID not found.\n"); return; }
    printf("New name : ");
    scanf(" %49[^\n]", list[idx].fullName);
    printf("Name updated.\n");
}

void editMarks(int n, struct Student *list) {
    int id;
    printf("Student ID : ");
    scanf("%d", &id);
    int idx = findById(list, n, id);
    if (idx == -1) { printf("ID not found.\n"); return; }
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%-8s mark : ", subjects[i]);
        scanf("%f", &list[idx].marks[i]);
        while (list[idx].marks[i] < 0 || list[idx].marks[i] > 20) {
            printf("  ! Invalid mark (0-20) : ");
            scanf("%f", &list[idx].marks[i]);
        }
    }
    list[idx].average = calcAverage(list[idx].marks);
    printf("Marks and average updated.\n");
}

void editStudent(int n, struct Student *list) {
    int id;
    printf("Student ID : ");
    scanf("%d", &id);
    int idx = findById(list, n, id);
    if (idx == -1) { printf("ID not found.\n"); return; }
    printf("New name : ");
    scanf(" %49[^\n]", list[idx].fullName);
    printf("New age  : ");
    scanf("%d", &list[idx].age);
    while (list[idx].age < 5 || list[idx].age > 100) {
        printf("  ! Invalid age (5-100) : ");
        scanf("%d", &list[idx].age);
    }
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("%-8s mark : ", subjects[i]);
        scanf("%f", &list[idx].marks[i]);
        while (list[idx].marks[i] < 0 || list[idx].marks[i] > 20) {
            printf("  ! Invalid mark (0-20) : ");
            scanf("%f", &list[idx].marks[i]);
        }
    }
    list[idx].average = calcAverage(list[idx].marks);
    printf("Student updated.\n");
}

/* ============================================================
   ADD / DELETE
   ============================================================ */
void addStudent(int *n, struct Student **list) {
    *list = (struct Student *)realloc(*list, sizeof(struct Student) * (*n + 1));
    if (!*list) { printf("Memory error.\n"); return; }
    printf("\n--- New Student ---\n");
    inputStudent(&(*list)[*n], *list, *n);
    (*n)++;
    printf("Student added.\n");
}

void deleteById(int *n, struct Student *list) {
    int id;
    printf("ID to delete : ");
    scanf("%d", &id);
    int idx = findById(list, *n, id);
    if (idx == -1) { printf("ID not found.\n"); return; }
    for (int i = idx; i < *n - 1; i++)
        list[i] = list[i + 1];
    (*n)--;
    printf("Student deleted.\n");
}

/* ============================================================
   MENUS
   ============================================================ */
void menuSort(int n, struct Student *list) {
    int c;
    while (1) {
        printf("\n");
        separator();
        printf("         SORT\n");
        separator();
        printf("  1. By ID\n");
        printf("  2. By Name\n");
        printf("  3. By Age\n");
        printf("  4. By Average\n");
        printf("  0. Back\n");
        separator();
        printf("Choice : ");
        scanf("%d", &c);
        if (c == 0) return;
        switch (c) {
            case 1: sortById(n, list);      break;
            case 2: sortByName(n, list);    break;
            case 3: sortByAge(n, list);     break;
            case 4: sortByAverage(n, list); break;
            default: printf("Invalid choice.\n");
        }
        pressEnter();
    }
}

void menuSearch(int n, struct Student *list) {
    int c;
    while (1) {
        printf("\n");
        separator();
        printf("         SEARCH\n");
        separator();
        printf("  1. By ID\n");
        printf("  2. By Name\n");
        printf("  3. By Age\n");
        printf("  0. Back\n");
        separator();
        printf("Choice : ");
        scanf("%d", &c);
        if (c == 0) return;
        switch (c) {
            case 1: searchById(n, list);   break;
            case 2: searchByName(n, list); break;
            case 3: searchByAge(n, list);  break;
            default: printf("Invalid choice.\n");
        }
        pressEnter();
    }
}

void menuFilter(int n, struct Student *list) {
    int c;
    while (1) {
        printf("\n");
        separator();
        printf("         FILTER\n");
        separator();
        printf("  1. Adults  (>= 18)\n");
        printf("  2. Minors  (<  18)\n");
        printf("  3. Older than X\n");
        printf("  0. Back\n");
        separator();
        printf("Choice : ");
        scanf("%d", &c);
        if (c == 0) return;
        switch (c) {
            case 1: showAdults(n, list);     break;
            case 2: showMinors(n, list);     break;
            case 3: showOlderThan(n, list);  break;
            default: printf("Invalid choice.\n");
        }
        pressEnter();
    }
}

void menuEdit(int n, struct Student *list) {
    int c;
    while (1) {
        printf("\n");
        separator();
        printf("         EDIT\n");
        separator();
        printf("  1. Edit Age\n");
        printf("  2. Edit Name\n");
        printf("  3. Edit Marks\n");
        printf("  4. Edit Full Student\n");
        printf("  0. Back\n");
        separator();
        printf("Choice : ");
        scanf("%d", &c);
        if (c == 0) return;
        switch (c) {
            case 1: editAge(n, list);     break;
            case 2: editName(n, list);    break;
            case 3: editMarks(n, list);   break;
            case 4: editStudent(n, list); break;
            default: printf("Invalid choice.\n");
        }
        pressEnter();
    }
}

void menuDisplay(int n, struct Student *list) {
    int c;
    while (1) {
        printf("\n");
        separator();
        printf("         DISPLAY\n");
        separator();
        printf("  1. All students\n");
        printf("  2. By entry order\n");
        printf("  3. Statistics\n");
        printf("  0. Back\n");
        separator();
        printf("Choice : ");
        scanf("%d", &c);
        if (c == 0) return;
        switch (c) {
            case 1: printAll(n, list);    break;
            case 2: printByOrder(n, list);break;
            case 3: printStats(n, list);  break;
            default: printf("Invalid choice.\n");
        }
        pressEnter();
    }
}

/* ============================================================
   MAIN MENU
   ============================================================ */
void mainMenu(int *n, struct Student **list) {
    int c;
    while (1) {
        printf("\n");
        printf("==========================================\n");
        printf("||       STUDENT MANAGEMENT            ||\n");
        printf("==========================================\n");
        printf("||  1. Sort                            ||\n");
        printf("||  2. Search                          ||\n");
        printf("||  3. Statistics                      ||\n");
        printf("||  4. Filter                          ||\n");
        printf("||  5. Edit                            ||\n");
        printf("||  6. Add student                     ||\n");
        printf("||  7. Delete student                  ||\n");
        printf("||  8. Display                         ||\n");
        printf("||  0. Exit                            ||\n");
        printf("==========================================\n");
        printf("Choice : ");
        scanf("%d", &c);

        switch (c) {
            case 1: menuSort(*n, *list);                       break;
            case 2: menuSearch(*n, *list);                     break;
            case 3: printStats(*n, *list);   pressEnter();     break;
            case 4: menuFilter(*n, *list);                     break;
            case 5: menuEdit(*n, *list);                       break;
            case 6: addStudent(n, list);     pressEnter();     break;
            case 7: deleteById(n, *list);    pressEnter();     break;
            case 8: menuDisplay(*n, *list);                    break;
            case 0: printf("\nGoodbye!\n"); return;
            default: printf("Invalid choice.\n"); pressEnter();
        }
    }
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {
    int n;
    askCount(&n);

    struct Student *list = (struct Student *)malloc(sizeof(struct Student) * n);
    if (!list) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    fillList(n, list);
    mainMenu(&n, &list);

    free(list);
    return 0;
}
