#include "hash.h"
#include <stdio.h>

// Function to display 
int display_database(hash_t *hash_table)
{
   	 int i;  
    	printf("Index\t\tword\t\t\tfilecount\tfilename\t\twordcount\tfilename\t\twordcount\n\n");

    	// Loop through each index of the hash table
    	for (i = 0; i < 28; i++) 
    	{
        	// Check if the current index has a linked list
        	if (hash_table[i].link != NULL)
        	{
            		main_n *temp = hash_table[i].link;
            
           		 // Traverse the linked list of words (main nodes)
            		while (temp != NULL)
            		{
                		// Print the current word and its file count
                		printf("%d\t\t%-13s\t\t%-5d", i, temp -> word, temp -> filecount);

                		// Pointer to traverse the sublist of filenames (sub nodes)
                		sub_n *temp1 = temp -> sublink;

                		// Traverse the sublist
                		while (temp1 != NULL)
                		{
                   	 		// Print the filename and the word count for the current word in this file
                    			printf("\t\t%-10s\t\t%-5d", temp1 -> filename, temp1 -> wordcount);
                    
                   		 	// Move to the next filename in the sublist
                    			temp1 = temp1 -> sublink;
                		}
                
                		// Move to the next word in the main linked list
               		 	temp = temp -> mainlink;

                		printf("\n");
            		}
        	}
    	}
    	return SUCCESS;  // Return success afte  displaying the database
}
