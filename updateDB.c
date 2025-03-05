#include "hash.h"

// Function to validate 
int backup_validate(char *file);

// Function to update the database 
int update_database(hash_t *hash_table , Slist **head) 
{

    	char file[20];  // Buffer to store the file name 
    	printf("Enter file name to backup: ");
    	scanf("%s", file);  

    	int res = 0;
    	// Validate the backup file by calling the backup_validate function
    	if((res = backup_validate(file)) == FAILURE) 
	{
        	return FAILURE;  // Return failure if file validation fails
    	}
    	else if(res == DATA_NOT_FOUND) 
	{
        	return DATA_NOT_FOUND;  // Return DATA_NOT_FOUND if no data is found in the file
    	}

    	// Open the backup file in read mode
   	 FILE *fptr = fopen(file, "r");
    	char str[50];  // Buffer

    	// Read each word 
    	while(fscanf(fptr, "%s", str) != EOF) 
	{
        int index = atoi(strtok(str, "#;"));  // finidng index

        // Allocate memory for a new main node and initialize its values
        main_n *mnew = malloc(sizeof(main_n));
        if(mnew == NULL) 
	{
            return FAILURE;  // Return failure if memory allocation failed
        }
        strcpy(mnew -> word, strtok(NULL, "#;"));  // Extract word from the line
        mnew -> filecount = atoi(strtok(NULL, "#;"));  // Extract file count
        mnew -> mainlink = NULL;  

        // If the hash table index is empty, insert the new node as the first node
        if(hash_table[index].link == NULL) 
	{
            hash_table[index].link = mnew;
        } 
	else 
	{
            // Otherwise, traverse the existing linked list to insert the new node
            main_n *mtemp = hash_table[index].link;
            while(mtemp->mainlink != NULL) 
	    {

                mtemp = mtemp -> mainlink;
            }

            mtemp -> mainlink = mnew;  // Add the new node
        }

        // Loop to add sub-nodes 
        for(int i = 1; i <= mnew->filecount; i++) 
	{
            // Allocate memory for a new sub-node 
            sub_n *snew = malloc(sizeof(sub_n));
            strcpy(snew -> filename, strtok(NULL, "#;"));  // Extract file name
            snew -> wordcount = atoi(strtok(NULL, "#;"));  // Extract word count
            snew -> sublink = NULL;  // Initialize the sub-link as NULL

            // If this is the first sub-node, set it as the sub-link of the main node
            if(i == 1) 
	    {
                mnew -> sublink = snew;
            } else 
	    {
                sub_n *stemp = mnew -> sublink;
                while(stemp->sublink != NULL) 
		{
                    stemp = stemp -> sublink;
                }
                stemp -> sublink = snew;  // Add the new sub-node at the end
            }
        }
    	}

    	// declare temparary pointers
    	Slist *temp = *head;
   	Slist *prev = NULL;

    	// Traverse the linked list
    	while(temp != NULL) 
	{
        	int matchFound = 0;  // Flag to track if a match is found

        	// Traverse the hash table
        	for(int i = 0; i < 28; i++) 
		{
            	if(hash_table[i].link != NULL) 
		{
                main_n *mtemp = hash_table[i].link;

                // Traverse the main node
                while(mtemp != NULL) 
		{
                    sub_n *stemp = mtemp -> sublink;

                    // Traverse the sub-nodes in the hash table
                    while(stemp != NULL) 
		    {
                        if(strcmp(stemp -> filename, temp -> filename) == 0) 
			{
                            
                            if(prev == NULL) 
			    {
                                *head = temp -> link;  // Update the head if the first node is matched
                            } else 
			    {
                                prev -> link = temp -> link; 
                            }
                            temp = temp -> link;  // Move to the next node in the list
                            matchFound = 1;
                            break;  // Exit the sublink loop if match is found
                        }
                        stemp = stemp -> sublink;  // Move to the next sub-node
                    }

                    if(matchFound) break;  // Exit the mainlink
                    mtemp = mtemp -> mainlink;  // Move to the next main node
                }
            }

            if(matchFound) break;  // Exit
        }

        // If no match found, move to the next node in the linked list
        if(!matchFound) 
	{
            prev = temp;
            temp = temp -> link;
        }
    	}

    // After deleting matched nodes, create the database with remaining data
    	if(create_database(head, hash_table) == SUCCESS) 
	{
        	return SUCCESS;  // Return success if the database is created successfully
    	} 
    	else 
    	{
        	printf("Create database failed\n");
    	}
}

// Function to validate the backup file 
int backup_validate(char *file) 
{
    	// Check if the file name ends with ".txt"
    	if(strstr(file, ".txt") == NULL)
        	return FAILURE;  // Return failure if the file is not a .txt file

    	// Try to open the file for reading
   	 FILE *fptr = fopen(file, "r");
    	if(fptr == NULL)
        	return DATA_NOT_FOUND;  // Return DATA_NOT_FOUND if the file cannot be opened

    	// Move to the end of the file to check if it's empty
    	fseek(fptr, 0, SEEK_END);
    	if(ftell(fptr) == 0) 
	{
        	printf("ERROR: File is empty\n");
        	fclose(fptr);
        	return FAILURE;  // Return failure if the file is empty
    	}

    	char ch;
    	fseek(fptr, 0, SEEK_SET);

    	// Check if the first character is '#', and  the last character is also '#'
    	if((ch = fgetc(fptr)) == '#') 
	{
        	fseek(fptr, -2, SEEK_END);
        	ch = fgetc(fptr);
        	if(ch != '#') 
		{
            	fclose(fptr);
            	return DATA_NOT_FOUND;  // return data not found
        	}
    	} 
    	else 
    	{
        	fclose(fptr);
       		return DATA_NOT_FOUND;  
    	}

    	fclose(fptr);
    	return SUCCESS;  // Return success 
}
