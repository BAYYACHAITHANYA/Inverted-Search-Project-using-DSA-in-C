#include "hash.h"

// Function to save 
int save_database(hash_t *hash_table)
{
    	char filename[50]; 
    	printf("Enter the file name to save database : ");
    	scanf("%s", filename); 

   	 // Check if the filename contains ".txt"
    	if (strstr(filename, ".txt") != NULL)
    	{
        	// Open the file in write mode
        	FILE *fptr = fopen(filename, "w");

        	// Loop through each index in the hash table 
        	for (int i = 0; i < 28; i++)
        	{
            		// Check if there is a linked list at this index 
            		if (hash_table[i].link != NULL)
            		{
                		// Pointer to traverse 
                		main_n *mtemp = hash_table[i].link;

                		// Traverse the linked list of words
                		while (mtemp != NULL)
                		{
                    			// Write the current word's index, word, and file count to the file
                    			fprintf(fptr, "#%d;%s;%d;", i, mtemp -> word, mtemp -> filecount);

                    			// Pointer to traverse the sublist 
                    			sub_n *stemp = mtemp -> sublink;

                    			// Traverse the sublist
                    			while (stemp != NULL)
                    			{
                        			// Write the filename and word count to the file
                        			fprintf(fptr, "%s;%d;", stemp -> filename, stemp -> wordcount);

                        			// Move to the next sub node 
                       				 stemp = stemp -> sublink;
                    			}

                   			 fprintf(fptr, "%s", "#\n");

                   			 // Move to the next word in the main linked list
                    			mtemp = mtemp -> mainlink;
                		}	
            		}
        	}

        	// Close the file 
        	fclose(fptr);
    	}
    	else
    	{
       	 	printf("INFO : %s => This file is not a .txt file\n", filename);
    	}

    	return SUCCESS; // Return success
}
