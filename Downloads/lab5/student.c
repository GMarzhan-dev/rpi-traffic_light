#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Initializer or Constructor
Student initStudent(const char *name, int group_id, float gpa) {
    Student s;
    s.name = malloc(strlen(name) + 1);
    if (s.name != NULL) {
        strcpy(s.name, name);
    }
    s.group_id = group_id;
    s.gpa = gpa;
    return s;
}

// Getters
const char* getName(const Student *s) { return s->name; }
int getGroupId(const Student *s) { return s->group_id; }
float getGpa(const Student *s) { return s->gpa; }

// Setters
void setName(Student *s, const char *name) {
    char *newName = malloc(strlen(name) + 1);
    if (newName != NULL) {
        strcpy(newName, name);
        free(s->name);
        s->name = newName;
    }
}
void setGroupId(Student *s, int group_id) { s->group_id = group_id; }
void setGpa(Student *s, float gpa) { s->gpa = gpa; }

// Destructor
void freeStudent(Student *s) {
    free(s->name);
    s->name = NULL;
}
