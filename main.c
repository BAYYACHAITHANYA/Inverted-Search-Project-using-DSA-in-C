#include "hash.h"
#include <stdio.h>
/*Name :Bayya chaithanya
  Date :28/12/2024
  Project Name:Inverted Search*/

int main(int argc, char *argv[])
{
       	Slist *head = NULL;  // Pointer to the linked list of filenames

    	// Check if command line arguments are passed
    	if (argc > 1)
    	{
        	// If the arguments are valid, read and validate the command-line files
        	if (read_and_validate_cml(&head, argc, argv) == SUCCESS)
        	{
            	print_list(head);  // Print the linked list of filenames
            	hash_t arr[28];  // Array to store the hash table
            	create_hashtable(arr);  // Initialize the hash table
            	int option, flag = 0, lflag = 1;  // Initialize flags for menu options and loop

            	// Loop to show menu and take user input
            	while (lflag)
            	{
                	// Display the menu for the user to select an operation
                	printf("\nSelect your choice among the following operations:\n");
                	printf("\n 1. Create database\n 2. Display Database\n 3. Update Database\n 4. Search\n 5. Save Database\n");
                	printf("\nEnter your choice: ");
                	scanf("%d", &option);  // Take the user's choice

                	// Switch case to perform different actions based on user choice
                	switch (option)
                	{
                    	case 1:
                        	// Create database if not already created
                        	if (flag == 0)
                        	{
                            	int res = create_database(&head, arr);  // Create the database
                            	for (int i = 1; i < argc; i++)
                            	{
                                if (res == SUCCESS)
                                {
                                    	flag = 1;  // Mark database as created
                                    	printf("INFO : Successful creation of DATABASE for file: %s\n", argv[i]);
                                }
                                else if (res == DATA_NOT_FOUND)
                                {
                                    	printf("filenames linked list is empty\n");
                                }
                                else
                                {
                                    	printf("Create database unsuccessful\n");
                                }
                            	}
                        	}
                        	else
                        	{
                            		printf("INFO : Database is already created\n");  // Inform user if database is already created
                        	}
                        	break;

                    	case 2:
                        	// Display the database if created
                        	if (display_database(arr) == SUCCESS)
                        	{
                            		//printf("Display database completed\n");
                        	}
                        	else
                        	{
                            		printf("Display database unsuccessful\n");
                        	}
                        	break;
                    	case 4:
                        	// Search for a word in the database if the database is created
                        	if (flag == 1)
                        	{
                            	if (search_database(arr) == SUCCESS)
                            	{
                                	printf("Search database completed\n");
                            	}
                            	else
                            	{
                                	printf("Search database unsuccessful\n");
                            	}
                        	}
                        	else
                        	{
                            		printf("Database not created, first create the database\n");  // Inform user if database is not created
                        	}
                        break;
                    	case 5:
                        	// Save the database to a file
                        	if (save_database(arr) == SUCCESS)
                        	{
                            		printf("INFO : Database is saved\n");
                        	}
                        	else
                        	{
                            		printf("Saving database failed\n");
                        	}
                        break;

                    	case 3:
                        	// Update the database if it's already created
                        	if (flag == 0)
                        	{
                            	int res1;
                            	if ((res1 = update_database(arr, &head)) == SUCCESS)
                            	{
                                	printf("INFO : Database updated successfully\n");
                                	print_list(head);  // Print the updated list of filenames
                            	}
                            	else if (res1 == DATA_NOT_FOUND)
                            	{
                                	printf("Enter the backup file containing backup data\n");  // Prompt for a backup file if necessary
                            	}
                            	else
                            	{
                                	printf("Restoring database failed due to incorrect file extension\n");  
                            	}
                        	}
                        	else
                        	{
                            		printf("INFO : Database is already created, update is not possible\n");  
                   	    	}
                        break;

                    default:
                        // Inform user of an invalid menu option
                        printf("Invalid option! Please try again\n");
                        break;
                }

               		 // Ask if the user wants to continue
               		 printf("\nDo you want to continue?\nEnter y/Y to continue and n/N to discontinue\n");
                	char y;
                	getchar();  
                	scanf("%c", &y);  // Read user's decision to continue or not

                	// Set the flag based on user's response to continue or exit the menu
                	if (y == 'y' || y == 'Y')
                	{
                    		lflag = 1;  // Continue the loop
                	}	
               		 else
                	{
                    		lflag = 0;  // Exit the loop
                	}
            	}
        	}
        	else
        	{
            		printf("\n\n\nINFO : Files are not there\nCreate database is not possible\n");
            		print_list(head);  // Print the current list of filenames (if any)
        	}
    	}
    	else
    	{
        	printf("INFO : Insufficient arguments\nPlease pass the arguments like a.out <txt file>\n");
    	}

    	return 0;  // Return 0 indicating the program has finished
}
