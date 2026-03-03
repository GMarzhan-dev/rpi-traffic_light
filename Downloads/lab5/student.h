#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    char *name;
    int group_id;
    float gpa;
} Student;

// Function prototypes
Student initStudent(const char *name, int group_id, float gpa);
const char* getName(const Student *s);
int getGroupId(const Student *s);
float getGpa(const Student *s);

void setName(Student *s, const char *name);
void setGroupId(Student *s, int group_id);
void setGpa(Student *s, float gpa);

void freeStudent(Student *s);

#endif
