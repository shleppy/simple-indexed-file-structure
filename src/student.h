/* author: Shelby Hendrickx */
#ifndef STUDENT_H
#define STUDENT_H

typedef struct student {
  long id;
  char* first_name;
  char* last_name;
} student;

void printStudent(student*);

void jinit(char* file);
void jwrite(char* file, student*);
void jclose(char* file);

#endif
