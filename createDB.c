#include "hash.h"

// Function to create a database
int create_database(Slist **head, hash_t *hash_table)
{

    	Slist *filetemp = *head; // Pointer to traverse the list of files
        if (filetemp == NULL) // Check if the list of files is empty
        {
                fprintf(stderr, "Error: Input list is empty.\n"); // Error message if the list is empty
                return FAILURE; // Return failure if the list is empty
        }

        // Traverse the list of files
        while (filetemp != NULL)
        {
                // Open the file for reading
                FILE *fptr = fopen(filetemp -> filename, "r");
                if (fptr == NULL) // Check if the file could not be opened
                {
                        fprintf(stderr, "Error opening file '%s'\n", filetemp -> filename);
                        return FAILURE; // Return failure if file opening fails
                }

                char word[20]; // Array to store each word from the file
                // Read each word from the file
                while (fscanf(fptr, "%s", word) != EOF)
                {
                        int i; // Variable to store the hash index for the word
                        
                        // Determine the hash index based on the first character of the word
                        if (isalpha(word[0])) // If the first character is a letter
                        {
                                i = tolower(word[0]) - 'a'; 
                        }
                        else if (isdigit(word[0])) // If the first character is a digit
                        {
                                i = 26; // Hash index for digits
                        }
                        else // For any other character (punctuation, etc.)
                        {
                                i = 27; // Hash index for non-alphabetic, non-digit characters
                        }

                        main_n *mtemp = hash_table[i].link;
                        main_n *mprev = NULL; // Pointer to the previous node in the list
                        while (mtemp != NULL && strcmp(mtemp -> word, word) != 0)
                        {
                                mprev = mtemp; // Move to the next node
                                mtemp = mtemp -> mainlink;
                        }
                        if (mtemp == NULL) // Word not found in the hash table
                        {
                                // Allocate memory for a new node for the word
                                mtemp = malloc(sizeof(main_n));
                                if (mtemp == NULL) 
                                {
                                        fprintf(stderr, "Error: Memory allocation failed for main node.\n");
                                        fclose(fptr); // Close the file before returning
                                        // Clean up already allocated memory (requires a function to traverse and free)
                                        return FAILURE;
                                }
                                strcpy(mtemp -> word, word); // Store the word in the new node
                                mtemp -> filecount = 1; // Initialize file count for this word
                                mtemp -> mainlink = NULL; 
                                mtemp -> sublink = NULL; // Initialize sublink (for file-specific word counts)
                                
                                // Create a new sub node 
                                sub_n *new_sub = malloc(sizeof(sub_n));
                                if (new_sub == NULL) // Memory allocation check for sub node
                                {
                                        fprintf(stderr, "Error: Memory allocation failed for sub node.\n");
                                        free(mtemp); // Free main node if sub node allocation fails
                                        fclose(fptr); // Close the file before returning
                                        return FAILURE;
                                }
                                 strcpy(new_sub -> filename, filetemp -> filename); // copy the filename
                                new_sub -> wordcount = 1; // Initialize word count for this file
                                new_sub -> sublink = NULL; 
                                mtemp -> sublink = new_sub; // Link the sub node to the main node

                                // Add the new node to the hash table
                                if (mprev) // If there was a previous node in the list
                                {
                                        mprev -> mainlink = mtemp; // Link the previous node to the new node
                                }
                                else 
                                {
                                        hash_table[i].link = mtemp;
                                }
                        }
                        else // Word found in the hash table
                        {
                                // Traverse the sublist to check if the word exists in this file
                                sub_n *stemp = mtemp -> sublink;
                                sub_n *sprev = NULL; // Pointer to the previous sub node
                                while (stemp != NULL && strcmp(stemp -> filename, filetemp -> filename) != 0) 
                                {
                                        sprev = stemp; // Move to the next sub node
                                        stemp = stemp -> sublink;
                                }

                                if (stemp == NULL) // Filename not found under this word
                                {
                                        // Allocate memory for a new sub node for this file
                                        stemp = malloc(sizeof(sub_n));
                                        if (stemp == NULL) // Memory allocation check for sub node
                                        {
                                                fprintf(stderr, "Error: Memory allocation failed for sub node.\n");
                                                fclose(fptr); // Close the file before returning
                                                return FAILURE;
                                        }
                                        strcpy(stemp -> filename, filetemp -> filename); // Store the filename
                                        stemp -> wordcount = 1; 
                                        stemp -> sublink = NULL; 
                                        
                                        // Link the new sub node to the appropriate position in the list
                                        if (sprev)
                                        {
                                                sprev -> sublink = stemp; // Link the previous sub node to the new one
                                        }
                                        else
                                        {
                                                mtemp -> sublink = stemp; // If no previous sub node, link it to the main node
                                        }
                                        mtemp -> filecount++; // Increment the file count for the word
                                }
                                else // Filename found, increment the word count for this file
                                {
                                        stemp -> wordcount++;
                                }
                        }

                }

        fclose(fptr); // Close the file after processing all words
        filetemp = filetemp -> link; // Move to the next file in the list
    }
    return SUCCESS; // Return success if the database is created successfully
}
