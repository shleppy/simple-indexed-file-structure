/* author: Shelby Hendrickx */
#ifndef SIFS_H
#define SIFS_H

typedef struct container {
  char* key;
  void* content;
} container;

typedef struct sifs {
  container **containers;
  int INDEX_SIZE;
  int BUCKET_SIZE;
  int OVERFLOW_SIZE;
} sifs;

void init(sifs*); // TODO change return type to sifs* and pass ints
void destroy(sifs*);

/* pre : Sifs is initialized, char* is the key, void* is a valid structure
   post: The struct is added to the sifs at the hashed location
 */
void create(sifs, char*, void*);

/* pre : Sifs is initialized
   post: Returns the struct found at the position of the hashed key or null.
 */ 
void* read(sifs, char*);

/* pre : Sifs is initialized
   post: Struct at the position of the hashed key is removed from the file structure
         and freed from memory
 */
void delete(sifs, char*);

/* pre : Sifs is initialized, Key is not null
   post: A valid hash is calculated which returns an index to a bucket.
 */
int get_hash(sifs table, char*);

#endif
