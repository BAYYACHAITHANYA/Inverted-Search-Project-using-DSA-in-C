#include "hash.h"

// Function to search 
int search_database(hash_t *hash_table)
{
    	char word[50]; 
    	printf("Enter the word to search : ");
    	scanf("%s", word); // Read the word from user input

    	int i; // Variable to store index

    	// Determine the hash index based on the first character of the word
    	if (isalpha(word[0])) // If the first character is a letter (a-z or A-Z)
    	{	
        	i = tolower(word[0]) - 'a'; // Hash index for letters 'a' to 'z'
    	}
    	else if (isdigit(word[0])) // If the first character is a digit (0-9)
    	{
        	i = 26; // Hash index for digits
    	}
    	else 
    	{
        	i = 27; // Hash index for non-alphabetic, non-digit characters
    	}

    	// Pointer to traverse the main list 
    	main_n *temp = hash_table[i].link;
   	// Pointer to traverse the sublist of filenames for each word
    	sub_n *temp1 = NULL;
    
    	int found = 0; // Flag to track whether the word is found or not

    	while (temp != NULL)
    	{
        	// Check if the current word matches the user-provided word
        	if (strcmp(temp -> word, word) == 0)
        	{
            		found = 1; // Set the flag to indicate that the word was found
         
            		printf("%s is present in the %d files\n", temp -> word, temp -> filecount);

            		// Pointer to traverse the sublist of filenames 
            		temp1 = temp -> sublink;
            		// Traverse the sublist 
            		while (temp1 != NULL)	
            		{
                		// Check if the current sublist entry is valid
                		if (temp1 != NULL)
                		{
                    			// Print the word count in the file 
                    			if (temp1 -> wordcount > 1)
                    			{
                        			printf("In %s %d times\n", temp1 -> filename, temp1 -> wordcount);
                    			}
                    			else
                   			 {
                        			printf("In %s %d time\n", temp1 -> filename, temp1 -> wordcount);
                    			}
                		}
                			// Move to the next file in the sublist
                			temp1 = temp1 -> sublink;			
            		}
        	}
    
        	// Move to the next word in the main linked list
        	temp = temp -> mainlink;
    	}

    	// If the word was not found, print a message to inform the user
    	if (!found)
    	{
        	printf("Word is not found in the database\n");
    	}

    	return SUCCESS; // Return success 
}
