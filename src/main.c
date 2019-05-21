/* author: Shelby Hendrckx */
#include "sifs.h"
#include "student.h"
#include <stdio.h>

#define NULL_KEY "NULL_CONTAINER_KEY"
#define NULL_CONTENT "NULL_CONTAINER_CONTENT"

void print_read_result(student* std);

int main(int argc, char* argv[])
{
  /* Student Creation */
  student std1 = {
    .id = 104,
    .first_name = "Jane",
    .last_name = "Doe"
  };
  printStudent(&std1);
  student std2 = {
    .id = 3883,
    .first_name = "John",
    .last_name = "Doe"
  };
  printStudent(&std2);
  student std3 = {
    .id = 321,
    .first_name = "Foo",
    .last_name = "Bar"
  };
  printStudent(&std3);

  /* Local sifs containing all the data */
  sifs sifs;
  sifs.INDEX_SIZE = 6;
  sifs.BUCKET_SIZE = 10;
  sifs.OVERFLOW_SIZE = 9;

  /* Sifs is initialized */
  init(&sifs);
  printf("allocated memory\n");

  /* Student 1 is added */
  create(sifs, std1.first_name, &std1);
  printf("added one student %s\n", std1.first_name);

  /* Student 2 is added */
  create(sifs, std2.first_name, &std2);
  printf("added another student %s\n", std2.first_name);

  /* Student 3 is added */
  create(sifs, std3.first_name, &std3);
  printf("added one student %s\n", std3.first_name);

  /* Students returned */
  student* ret_ptr = (student*)read(sifs, "John");
  print_read_result(ret_ptr);

  student* ret_ptr2 = (student*)read(sifs, "Jane");
  print_read_result(ret_ptr2);

  student* ret_ptr3 = (student*)read(sifs, "Foo");
  print_read_result(ret_ptr3);

printf("WRITING FILE START\n");
  /* Persist files to json */
  char* file = "students.json";
  jinit(file);
  jwrite(file, ret_ptr);
  jwrite(file, ret_ptr2);
  jwrite(file, ret_ptr3);
  jclose(file);
printf("WRITING FILE END\n");

  /* Remove jane */
  delete(sifs, "Jane");
printf("here\n");
  student* ret_rm = read(sifs, "Jane");
  /* Try to read returned student should be null */
  print_read_result(ret_rm);

  /* Freed from memory */
  destroy(&sifs);
  printf("freed memory\n");

  return 0;
}

void print_read_result(student* std)
{
  if (std == NULL) 
    printf("Read returned null\n");
  else 
    printf("Returned student: %s %s\n", std->first_name, std->last_name);
}