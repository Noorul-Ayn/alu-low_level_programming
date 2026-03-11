#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int    id;
    char   name[50];
    float  grade;
} Student;

Student *students = NULL;
int      count    = 0;
int      capacity = 0;

void add_student       (void);
void display_students  (void);
void sort_students     (void);
void calculate_average (void);
void find_top_student  (void);
void grade_stability   (void);
void free_memory       (void);

typedef void (*MenuFn)(void);

MenuFn menu_functions[] = {
    add_student,
    display_students,
    sort_students,
    calculate_average,
    find_top_student,
    grade_stability
};

static void print_header(void)
{
    printf("\n==================================\n");
    printf("  DYNAMIC STUDENT RECORD ENGINE\n");
    printf("  Student ID : 54321\n");
    printf("  Analysis   : Grade Stability Score\n");
    printf("==================================\n");
}

static void print_divider(void)
{
    printf("----------------------------------------------------------\n");
}

static char letter_grade(float g)
{
    if (g >= 90) return 'A';
    if (g >= 80) return 'B';
    if (g >= 70) return 'C';
    if (g >= 60) return 'D';
    return 'F';
}

static void seed_data(void)
{
    const char *names[]  = { "Alice Mercer",  "Bob Nkosi",     "Clara Osei",
                              "David Patel",   "Eva Romero",    "Frank Tran",
                              "Grace Uwem",    "Henry Vasquez", "Iris Wolff",
                              "James Xu" };
    float grades[] = { 88.5f, 72.0f, 95.3f, 61.8f, 83.4f,
                        77.6f, 90.1f, 55.2f, 69.7f, 84.0f };
    int   ids[]    = { 1001, 1002, 1003, 1004, 1005,
                       1006, 1007, 1008, 1009, 1010 };

    capacity = 20;
    students = (Student *)malloc(capacity * sizeof(Student));
    if (!students) { perror("malloc"); exit(EXIT_FAILURE); }

    for (int i = 0; i < 10; i++) {
        students[i].id = ids[i];
        strncpy(students[i].name, names[i], sizeof(students[i].name) - 1);
        students[i].name[sizeof(students[i].name)-1] = '\0';
        students[i].grade = grades[i];
        count++;
    }
}

void add_student(void)
{
    if (count >= capacity) {
        capacity *= 2;
        Student *tmp = (Student *)realloc(students, capacity * sizeof(Student));
        if (!tmp) { perror("realloc"); return; }
        students = tmp;
    }

    Student *s = &students[count];
    printf("\nEnter student ID: "); scanf("%d", &s->id);
    printf("Enter student name: "); scanf(" %49[^\n]", s->name);
    printf("Enter grade (0-100): "); scanf("%f", &s->grade);

    if (s->grade < 0 || s->grade > 100) {
        printf("Invalid grade.\n");
        return;
    }

    /* string comparison - check for duplicate name */
    Student *ptr = students;
    for (int i = 0; i < count; i++, ptr++) {
        if (strcmp(ptr->name, s->name) == 0) {
            printf("Warning: Student '%s' already exists.\n", s->name);
        }
    }

    count++;
    printf("Student added.\n");
}

void display_students(void)
{
    if (count == 0) { printf("\nNo records found.\n"); return; }

    printf("\n");
    print_divider();
    printf("%-6s  %-22s  %-8s  %s\n", "ID", "Name", "Grade", "Letter");
    print_divider();

    Student *ptr = students;
    for (int i = 0; i < count; i++, ptr++) {
        printf("%-6d  %-22s  %-8.2f  %c\n",
               ptr->id, ptr->name, ptr->grade, letter_grade(ptr->grade));
    }
    print_divider();
    printf("Total: %d\n", count);
}

void sort_students(void)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            Student *p = students + j;
            Student *q = students + j + 1;
            if (p->grade < q->grade) {
                Student tmp = *p; *p = *q; *q = tmp;
            }
        }
    }
    printf("\nSorted by grade.\n");
    display_students();
}

void calculate_average(void)
{
    if (count == 0) { printf("\nNo records.\n"); return; }

    float sum = 0.0f;
    Student *ptr = students;
    for (int i = 0; i < count; i++, ptr++)
        sum += ptr->grade;

    float avg = sum / (float)count;
    printf("\nAverage: %.2f (%c)\n", avg, letter_grade(avg));
}

void find_top_student(void)
{
    if (count == 0) { printf("\nNo records.\n"); return; }

    Student *top = students;
    Student *ptr = students + 1;
    for (int i = 1; i < count; i++, ptr++)
        if (ptr->grade > top->grade) top = ptr;

    printf("\nTop Student\n");
    print_divider();
    printf("ID: %d\n",   top->id);
    printf("Name: %s\n",   top->name);
    printf("Grade: %.2f (%c)\n", top->grade, letter_grade(top->grade));
}

void grade_stability(void)
{
    if (count == 0) { printf("\nNo records.\n"); return; }

    float sum = 0.0f;
    Student *ptr = students;
    for (int i = 0; i < count; i++, ptr++) sum += ptr->grade;
    float mean = sum / (float)count;

    float variance = 0.0f;
    ptr = students;
    for (int i = 0; i < count; i++, ptr++)
        variance += (ptr->grade - mean) * (ptr->grade - mean);
    variance /= (float)count;

    float std_dev   = sqrtf(variance);
    float stability = 100.0f - std_dev;
    if (stability < 0) stability = 0.0f;

    printf("\nGrade Stability\n");
    printf("Mean: %.2f\n", mean);
    printf("Std Dev: %.2f\n", std_dev);
    printf("Stability: %.2f / 100\n", stability);

    if      (stability >= 85) printf("Verdict: Highly Stable\n");
    else if (stability >= 70) printf("Verdict: Moderately Stable\n");
    else                       printf("Verdict: High Variance\n");

    printf("\n%-22s  %-8s  %s\n", "Name", "Grade", "Deviation");
    print_divider();
    ptr = students;
    for (int i = 0; i < count; i++, ptr++) {
        float dev = ptr->grade - mean;
        printf("%-22s  %-8.2f  %+.2f\n", ptr->name, ptr->grade, dev);
    }
}

void free_memory(void)
{
    free(students);
    students = NULL;
    count = capacity = 0;
}

int main(void)
{
    seed_data();
    print_header();

    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Sort Students\n");
        printf("4. Average Grade\n");
        printf("5. Top Student\n");
        printf("6. Grade Stability\n");
        printf("7. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) { choice = 7; }

        if (choice >= 1 && choice <= 6) {
            menu_functions[choice - 1]();
        } else if (choice != 7) {
            printf("\nInvalid choice.\n");
        }

    } while (choice != 7);

    free_memory();
    printf("\nGoodbye!\n");
    return 0;
}
