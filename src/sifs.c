/* author: Shelby Hendrickx */
#include "sifs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init(sifs* table) 
{
  // malloc rows
  table->containers = malloc(sizeof(container*) * table->INDEX_SIZE);
  if (table->containers == NULL)
    printf("Malloc returned NULL at rows");

  // malloc overflow at first row
  table->containers[0] = malloc(sizeof(container) * table->OVERFLOW_SIZE);
  if (table->containers[0] == NULL)
    printf("Malloc returned NULL at overflow\n");
    
  // malloc buckets in all other rows
  for (int i = 1; i < table->INDEX_SIZE; i++)
  {
    table->containers[i] = malloc(sizeof(container) * table->BUCKET_SIZE);
    if (table->containers[i] == NULL)
      printf("Malloc returned NULL at bucket %d", i);
  }
  
  // initialize overflow with null values
  for (int i = 0; i < table->OVERFLOW_SIZE; i++)
  {
    table->containers[0][i].key = NULL;
    table->containers[0][i].content = NULL;
  }

  // initialize all buckets with null values;
  for (int i = 1; i < table->INDEX_SIZE; i++)
  {
    for (int j = 0; j < table->BUCKET_SIZE; j++)
    {
      table->containers[i][j].key = NULL;
      table->containers[i][j].content = NULL;
    }
  }
}
   
void destroy(sifs* table)
{
  for (int i = 0; i < table->INDEX_SIZE; i++)
    free(table->containers[i]);

  free(table->containers);
}

void create(sifs table, char* key, void* content)
{
  int hash = get_hash(table, key);
  for (int i = 0; i < table.BUCKET_SIZE; i++)
  {
    if (table.containers[hash][i].key == NULL) 
    {
      printf("Found empty bucket\n");
      table.containers[hash][i].key = key;
      table.containers[hash][i].content = content;
      return;
    }
    printf("Found occupied bucket\n");
  }

  for (int i = 0; i < table.OVERFLOW_SIZE; i++)
  {
    if (table.containers[0][i].key == NULL)
    {
      printf("Found empty bucket in overflow\n");
      table.containers[0][i].key = key;
      table.containers[0][i].content = content;
      return;
    }
    printf("Found occupied bucket in overflow\n");
  }
  printf("No space available in current table for key: %s\n", key);
}

void* read(sifs table, char* key)
{
  int hash = get_hash(table, key);

  for (int i = 0; i < table.BUCKET_SIZE; i++)
  {
    if (table.containers[hash][i].key == NULL) continue;
    if (strcmp(table.containers[hash][i].key, key) == 0) 
      return table.containers[hash][i].content;
  }

  for (int i = 0; i < table.OVERFLOW_SIZE; i++)
  {
    if (table.containers[0][i].key == NULL) continue;
    if (strcmp(table.containers[0][i].key, key) == 0)
      return table.containers[0][i].content;
  }

  printf("Not found while reading\n");
  return NULL;
}

void delete(sifs table, char* key)
{
  int hash = get_hash(table, key);
  for (int i = 0; i < table.BUCKET_SIZE; i++)
  {
    if (table.containers[hash][i].key == NULL) continue;
    if (strcmp(table.containers[hash][i].key, key) == 0) 
    {
      table.containers[hash][i].key = NULL;
      table.containers[hash][i].content = NULL;
      return;
    }  
  }

  for (int i = 0; i < table.OVERFLOW_SIZE; i++)
  {
    if (table.containers[hash][i].key == NULL) continue;
    if (strcmp(table.containers[hash][i].key, key) == 0) 
    {
      table.containers[hash][i].key = NULL;
      table.containers[hash][i].content = NULL;
      return;
    }
  }
}

int get_hash(sifs table, char* key)
{
  char *runner = key;
  int sum = 0;
  while (*runner != '\0')
  {
    sum += *runner;
    runner++;
  }
  return (31 * sum  % (table.INDEX_SIZE - 1)) + 1;
}
