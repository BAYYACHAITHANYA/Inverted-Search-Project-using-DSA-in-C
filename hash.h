#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SUCCESS 0
#define FAILURE -1
#define DATA_NOT_FOUND 1

/* Structure for hashtable */
typedef struct hash_table
{
	int key;
	struct main_node *link;
}hash_t;
/* Structure for creating main node */
typedef struct main_node
{
	int filecount;
	char word[50];
	struct main_node *mainlink;
	struct sub_node *sublink;
}main_n;
/* Stucture for creating sub node */
typedef struct sub_node
{
	int wordcount;
	char filename[50];
	struct sub_node *sublink;
}sub_n;
/* Structure for creating single linked list */
typedef struct file_names
{
	char filename[20];
	struct file_names *link;
}Slist;

/* function prototypes */

/* read and validate function */
int read_and_validate_cml( Slist** head, int argc, char *argv[]);

/*Function to insert filenames to linked list */
int insert_to_list(char *argv, Slist **head);

/* create hashtable function */
void create_hashtable(hash_t *arr);

/* create database function */
int create_database(Slist **head, hash_t *hash_table);

/*display database function*/
int display_database(hash_t *hash_table);

/*search function */
int search_database(hash_t *hash_table);

/* save database function */
int save_database(hash_t *hash_table);

/* update database function */
int update_database(hash_t *hash_table, Slist **head);

/* function to pritn the filenames names stored in the linked list */
void print_list(Slist *head);

#endif
