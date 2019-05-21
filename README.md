# simple-indexed-file-structure
Hash table with first index functioning as a overflow and items stored in buckets

student files are for testing includes writing to json

### General Exercise overview
Constraints
• Use of of structures  
• Memory allocation via malloc() and free()  
• Building by Makefile, so command make has to be used  
• Structured programming by using header files  
• Test via unit tests 

Tips and specs:  
• Create at start up the internal data structure with fixed sizes for index, buckets and
overflow.  
• “Stored objects” can have different sizes but have the same data elements, like: id,
name, address: {12, “Your name”, ”Address”} has size 4 +(9+1)+(7+1) = 22 and {234,
“My Name”, ”My address”} has size 4+(7+1)+(10+1) =23  
• Use hashing to calculate the number in the index array  
• Search for the first free position in the assigned bucket  
• In case there is no free position in this bucket than search for the first free position in the
overflow  
• In either case store the “stored object” at the free bucket position.  

### Exercise

7 Define the necessary structures  
8 Write the necessary functions which manages (allocate and deallocate) the internal data
structures.  
9 Only implement the CRD of the CRUD operations.  
10 Persist the in memory data in a JSON formatted or semicolon separated text file, per
line one record.  
