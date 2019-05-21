/* author: Shelby Hendrickx */
#include "student.h"
#include <stdio.h>
#include <stdlib.h>

void printStudent(student* std) 
{
  printf("Student [%ld]: %s %s\n", std->id, std->first_name, std->last_name);
}

void jinit(char* file)
{
  FILE *fp = fopen(file, "w");
  if (!fp)
  {
    printf("Failed opening file");
    return;
  }

  fprintf(fp, "{ \"students\" : [\n");
  
  fclose(fp);
}

void jclose(char* file)
{
  FILE *fp = fopen(file, "a");
  if (!fp)
  {
    printf("Failed opening file");
    return;
  }

  fprintf(fp, "]}\n");

  fclose(fp);
}

void jwrite(char* file, student* std)
{
  FILE *fp = fopen(file, "a");

  if (!fp)
  {
    printf("Failed opening file");
    return;
  }

  fprintf(fp, "\t{ \"id\":\"%ld\", \"first_name\":\"%s\", \"last_name\":\"%s\" },\n", std->id, std->first_name, std->last_name);

  fclose(fp);
}
