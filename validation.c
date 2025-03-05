#include "hash.h"

// Function to validate command line arguments
int read_and_validate_cml(Slist **head, int argc, char *argv[])
{
    for(int i = 1; i < argc; i++)
    {
        // Check if the argument contains ".txt" 
        if(strstr(argv[i], ".txt") != NULL)
        {
            FILE *temp;
            if((temp = fopen(argv[i], "r")) != NULL)
            {
                fseek(temp, 0, SEEK_END);  // Move the file pointer to the end
                if(ftell(temp) != 0)  // Check if the file is not empty
                {
                    // If file is not empty, attempt to insert it into the linked list
                    if(insert_to_list(argv[i], head) == FAILURE)
                    {
                        printf("insert list failed\n");
                        return FAILURE;  // Return failure if insertion fails
                    }
                }
                else
                {
                    printf("%s file is empty.\n", argv[i]);  // Inform if the file is empty
                    fclose(temp);
                    return FAILURE;  // Return failure for empty file
                }
            }
            else
            {
                printf("INFO: %s => This is not exist in the current directory\n", argv[i]);  // File does not exist
                return FAILURE;  // Return failure if file doesn't exist
            }
        }
        else
        {
            printf("INFO : %s => This file has not a .txt file\n", argv[i]);  // If the file isn't a .txt file
            return FAILURE;  // Return failure if file is not a .txt
        }
    }
    
    printf("INFO : Successfully inserting file names into file linked list\n\n");
    return SUCCESS;  // Return success after processing all arguments
}

// Function to insert a file name into the linked list
int insert_to_list(char *argv, Slist **head)
{
    Slist *new = malloc(sizeof(Slist));  // Allocate memory for a new list node
    if(new == NULL)
        return FAILURE;  // Return failure if memory allocation fails
    strcpy(new -> filename, argv);  // Copy the filename into the new node
    new -> link = NULL;  // Set the new node's link to NULL 

    if(*head == NULL)  // If the list is empty
    {
        *head = new;  // Set the head to the new node
        printf("%s file is added\n", argv);  // Inform that the file was added
    }
    else
    {
        Slist *temp = *head;
        // Traverse the list to check if the file already exists
        while(temp -> link)
        {
            if(!strcmp(temp -> filename, argv))
                break;  // Exit loop if file already exists
            temp = temp -> link;  // Move to the next node
        }
        // If the file was not found in the list
        if(strcmp(temp -> filename, argv))
        {
            temp -> link = new;  // Add the new node to the end of the list
            printf("%s file is added\n", argv);  // Inform that the file was added
        }
        else
        {
            printf("%s file already exists.\n", argv);  // Inform that the file is already in the list
            free(new);  // Free the memory of the new node
        }
    }
    return SUCCESS;  // Return success after inserting the file
}

// Function to initialize the hash table 
void create_hashtable(hash_t *arr)
{
    int i;
    for(i = 0; i < 28; i++)
    {
        arr[i].key = i;  // Set the key to the index
        arr[i].link = NULL;  // Initialize the link to NULL (empty list)
    }
}

// Function to print the file names in the linked list
void print_list(Slist *head)
{
    if(head == NULL)  // If the list is empty
    {
        printf("Info : List is empty\n");  // Inform that the list is empty
    }
    else
    {
        // Traverse and print each file in the list
        while(head != NULL)
        {
            printf("%s ", head -> filename);  // Print the filename
            head = head -> link;  // Move to the next node
            if(head != NULL)  // If there are more files, print an arrow
                printf("-> ");
        }
    }
    printf("-> NULL\n");  // End of the list
}
