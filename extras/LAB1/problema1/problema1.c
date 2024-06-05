#include <stdio.h>
#include <stdlib.h>


typedef struct student {
    char first_name[30], last_name[30];
    int age;
    int grade[3];
    float avg_grade;
}Student;

void read_student(FILE* in, Student* student){
    if( fscanf(in, "%s %s %d %d %d %d\n", student->last_name, student->first_name,
               &student->age, &student->grade[0], &student->grade[1], &student->grade[2]) != 6) {
        perror("cant read students");
        exit(-4);
    }
}

void print_student(FILE* out, Student student) {
    fprintf(out, "%s %s %d %d %d %d\n", student.last_name, student.first_name,
           student.age, student.grade[0], student.grade[1], student.grade[2]);
}

void compute_average (Student* student) {
    //ideal as avea in struct un grade_count si merg cu un for
    student->avg_grade = (float)student->grade[0] + (float)student->grade[1] + (float)student->grade[2];
    student->avg_grade /= 3.f;
}

void increment_grades(Student* student) {
    //ideal as avea in struct un grade_count si merg cu un for
    if(student->grade[0] < 10)
        student->grade[0]++;
    if(student->grade[1] < 10)
        student->grade[1]++;
    if(student->grade[2] < 10)
        student->grade[2]++;
}

int main() {

    FILE* in = fopen("intrare.txt", "r");
    if (in == NULL) {
        perror("Nu a putut fi deschis fisierul");
        exit(-1);
    }

    int students_size;
    if(fscanf(in, "%d\n", &students_size) != 1) {
        printf("can't read student number\n");
        exit(-2);
    }

    Student* student = (Student*) malloc(students_size * sizeof (Student));
    if(student == NULL) {
        perror("Nu a putut fi alocat");
        exit(-3);
    }

    for(int i = 0; i < students_size; i++) {
        read_student(in, &student[i]);
    }

    for(int i = 0; i < students_size; i++) {
        print_student(stdout, student[i]);
    }

    //pct c
    puts("\npunctul c\n");
    for(int i = 0; i < students_size; i++) {
        compute_average(&student[i]);
        printf("%s %s %.2f\n", student[i].last_name, student[i].first_name, student[i].avg_grade);
    }
    //pct d
    puts("\npunctul d\n");
    for(int i = 0; i < students_size; i++) {
        increment_grades(&student[i]);
        print_student(stdout, student[i]);
    }
    return 0;
}
