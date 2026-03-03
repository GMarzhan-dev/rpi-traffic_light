#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Build dataset dynamically and return array
Student* create_dataset(int *count) {
    char buffer[100];
    int group_id;
    float gpa;
    int capacity = 10;
    *count = 0;

    Student *students = malloc(capacity * sizeof(Student));
    if (!students) {
        fprintf(stderr,"malloc failed");
        exit(1);
    }

    while (1) {
	
        if (*count >= capacity) {
                printf("Capacity limit reached!\n ");
                break;
        }



        printf("Enter student name (or '#' to stop): ");
        scanf("%99s", buffer);

        if (strcmp(buffer, "#") == 0) {
            break;
        }

        printf("Enter group ID: ");
        scanf("%d", &group_id);

        printf("Enter GPA: ");
        scanf("%f", &gpa);
	/* TODO print current input and
		prompt if the current input should be saved, (y for yes n for no)
		if yes continue
		if no prompt which field to edit
		using a switch flow control and a setter, change the selected field
		using a getter confirm if the field saved correctly,
		repeat the edit if required
	*/


        students[*count] = initStudent(buffer, group_id, gpa);
        (*count)++;
    }

    return students;
}

int main() {
    int count;
    Student *students = create_dataset(&count);

    FILE *fp_all = fopen("students_all.txt", "w");
    FILE *fp_high = fopen("students_filtered.txt", "w");
    if (!fp_all || !fp_high) {
        perror("Error opening files");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp_all, "%s %d %.2f\n", students[i].name, students[i].group_id, students[i].gpa);
        if (students[i].gpa > 3.5) {
            fprintf(fp_high, "%s %d %.2f\n", students[i].name, students[i].group_id, students[i].gpa);
        }
        freeStudent(&students[i]);
    }

    fclose(fp_all);
    fclose(fp_high);
    free(students);

    printf("Saved %d students. Check students_all.txt and students_high.txt\n", count);
    return 0;
}
