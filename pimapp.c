#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct PersonalInfoRecord
{ 
	char id[10];
	char ptype;
	char name[31];

	union
	{
		struct
		{
			char dept[31];
			int hireyear;
			char tenured;
		}prof;
		struct
		{
			char faculty[31];
			int admyear;
		}stud;
	}info;

	struct PersonalInfoRecord *next;
} PersonalInfoRecord;



// Adding new node
struct PersonalInfoRecord* updateRecord(struct PersonalInfoRecord *pirp, struct PersonalInfoRecord *new) {
	// Below node will act as pointer (currently pointing to the head)
	struct PersonalInfoRecord *current = pirp;
	
	// Add new node at the appropriate location
	// The new node is first or the new node has smallest id
	if (pirp == NULL || atoi(pirp->id) > atoi(new->id)) {
		new->next = pirp; // new->next becomes what was the previous head
		// The head should be the new node
		pirp = new;
		return pirp;
	} else {
		// traversing list
		while (current != NULL){
			if (current->next == NULL) {
				if (atoi(current->id) != atoi(new->id)) {
				// Then append to the end of the list
					current->next = new;
					return pirp;

				} else { // The tail is the matching ID

                                	if (strcmp(new->name, "") != 0) strcpy(current->name, new->name);
                                	if (new->ptype == 'P') {
                                        	if (strcmp(new->info.prof.dept, "") != 0) strcpy(current->info.prof.dept, new->info.prof.dept);
                                        	if (new->info.prof.hireyear != atoi("")) current->info.prof.hireyear = new->info.prof.hireyear;
                                        	if (new->info.prof.tenured != 0) strcpy(&current->info.prof.tenured, &new->info.prof.tenured);
                                	} else if (new->ptype == 'S') {
                                        	if (strcmp(new->info.stud.faculty, "") != 0) strcpy(current->info.stud.faculty, new->info.stud.faculty);
                                        	if (new->info.stud.admyear != atoi("")) current->info.stud.admyear = new->info.stud.admyear;
					}
					free(new);
					return pirp;
				}
			} else { // current next isn't NULL
				if (atoi(current->id) == atoi(new->id)){
					if (strcmp(new->name, "") != 0) strcpy(current->name, new->name);
                                        if (new->ptype == 'P') {
                                                if (strcmp(new->info.prof.dept, "") != 0) strcpy(current->info.prof.dept, new->info.prof.dept);
                                                if (new->info.prof.hireyear != atoi("")) current->info.prof.hireyear = new->info.prof.hireyear;
                                                if (new->info.prof.tenured != 0) strcpy(&current->info.prof.tenured, &new->info.prof.tenured);
                                        } else if (new->ptype == 'S') {
                                                if (strcmp(new->info.stud.faculty, "") != 0) strcpy(current->info.stud.faculty, new->info.stud.faculty);
                                                if (new->info.stud.admyear != atoi("")) current->info.stud.admyear = new->info.stud.admyear;
                                        }
					free(new);
					return pirp;
				}

				if (atoi(current->next->id) < atoi(new->id)){
					current = current->next;
					continue;
				} else if (atoi(current->next->id) > atoi(new->id)) {
					// then we've found the spot where node should be inserted
					struct PersonalInfoRecord *nextnode = current->next;
					current->next = new;
					new->next = nextnode;
					return pirp;
				} else { // the next node has the matching ID and needs to be updated
                                        if (strcmp(new->name, "") != 0) strcpy(current->next->name, new->name);
                                        if (new->ptype == 'P') {
                                                if (strcmp(new->info.prof.dept, "") != 0) strcpy(current->next->info.prof.dept, new->info.prof.dept);
                                                if (new->info.prof.hireyear != atoi("")) current->next->info.prof.hireyear = new->info.prof.hireyear;
                                                if (new->info.prof.tenured != 0) strcpy(&current->next->info.prof.tenured, &new->info.prof.tenured);
                                        } else if (new->ptype == 'S') {
                                                if (strcmp(new->info.stud.faculty, "") != 0) strcpy(current->next->info.stud.faculty, new->info.stud.faculty);
                                                if (new->info.stud.admyear != atoi("")) current->next->info.stud.admyear = new->info.stud.admyear;
                                        }
					free(new);
					return pirp;
                                }
			}
		}
	}
}

struct PersonalInfoRecord* inList(struct PersonalInfoRecord *pirp, int retrievedId) {
	struct PersonalInfoRecord *current = pirp;
	while (current != NULL) {
		// If the last node isn't a match
		if (atoi(current->id) != retrievedId && current->next == NULL) {
			break;
		}
		if (atoi(current->id) == retrievedId) {
			return current; // we found the match
		} else if (current->next == NULL) {
			break;
		} else {
			current = current->next; // move to the next node and keep searching
			continue;
		}
	}
	return NULL;
}

void printList(struct PersonalInfoRecord *pirp) {
	while (pirp != NULL) {
		// checking the ptype
		// If student
		if (pirp->ptype == 'S'){
			printf("%s,%c,%s,%s,%d\n", pirp->id, pirp->ptype, pirp->name, pirp->info.stud.faculty, pirp->info.stud.admyear);
			pirp = pirp->next; // move to the following node
		} else { // If professor
			printf("%s,%c,%s,%s,%d,%c\n", pirp->id, pirp->ptype, pirp->name, pirp->info.prof.dept, pirp->info.prof.hireyear,pirp->info.prof.tenured);
			pirp = pirp->next; // move to the following node
		}
	}
}

struct PersonalInfoRecord* deleteRecord(struct PersonalInfoRecord *pirp, struct PersonalInfoRecord *new) {
	struct PersonalInfoRecord *current = pirp;
	int delete = atoi(new->id);
	struct PersonalInfoRecord *deleted;
	while (current != NULL) {
		if (atoi(current->id) == delete) {
			// The node should be removed
			deleted = pirp;
			pirp = current->next;
			free(deleted);
			break;
		} else if (current->next == NULL && atoi(current->id) != delete) {
			// Then we are at the end of the list and we didn't find the correct ID
			break;
		}

		if (atoi(current->next->id) != delete) {
			current = current->next; // keep traversing
			continue;
			}
		// If we got here, we found the node to be deleted
		// current is the node that comes right before the node to be deleted
		deleted = current->next; // the node to be deleted
		current->next = deleted->next;
		free(deleted);
		break;
	}
	return pirp;
}	

void freeMemory(struct PersonalInfoRecord *pirp) {
	struct PersonalInfoRecord *prev; //will store the previous node
	while (pirp != NULL){
		if (pirp->next != NULL) {
			prev = pirp;
			pirp = pirp->next; // move to the next node
			free(prev);
		} else { // There is only one node in the list
			free(pirp);
		}
	}
}



// The main of your application
int main(int argc, char *argv[])
{
	// Making a linkedlist
	
	// This is the head node
	struct PersonalInfoRecord *pirp = (struct PersonalInfoRecord *)malloc(sizeof(struct PersonalInfoRecord));
	
	// Keeping track of the memory location
	struct PersonalInfoRecord *previousNode = NULL;

	// This is the node containing the record
	pirp = NULL;
	
	// The number of arguments is incorrect
	char command;
        if (argc != 2) {
                fprintf(stderr, "Error, please pass the database filename as the argument.\nUsage ./pimapp <dbfile>\n");
                return 1;
	}
	
	char inputbuffer[100], *input; // to store each input line;

	while (fgets(input=inputbuffer, 100, stdin) != NULL) // Get each input line.
	{
		if(strncmp(input, "END", 3) == 0) { 
			break;
		} // We are asked to terminate.
		
		if(strncmp(input, "LIST", 4) == 0) { 
			printList(pirp);
			continue;
		}  // We are asked to display
		
		int field = 1; char*fielddata;
		// The new node should be reinitialized
		
		struct PersonalInfoRecord *new = (struct PersonalInfoRecord *)malloc(sizeof(struct PersonalInfoRecord));
                new->next = NULL;
		
		while ((fielddata = strsep(&input, ",\n")) != NULL){
			// Storing the command (insert or delete)	

			if (field == 1) {
                                char com;
                                sscanf(fielddata, "%c", &com);
                                command = com;
                                field = 2;
                                continue;
			}

			if (field == 2) {
				strcpy(new->id, fielddata);
				field = 3;

				if (inList(pirp,atoi(new->id)) != NULL) {
					new->ptype = inList(pirp,atoi(new->id))->ptype;
				}
                                continue;
			}

			// Check if the ID is in the list

			// The command is I and the node isn't in the list
			if (command == 'I') {
			
				if (field == 3) {
					if (inList(pirp,atoi(new->id)) == NULL){
                                		char type;
                                		sscanf(fielddata, "%c", &type);
                                		new->ptype = type;
                               			field = 4;
						continue;
					} else { 
						field = 4;
						continue;
					}
				} else if (field == 4) {
					strcpy(new->name, fielddata);
					field = 5;
					continue;
				} else if (new->ptype == 'P' && field == 5) {
                                	strcpy(new->info.prof.dept, fielddata);
                                	field = 6;
					continue;
				} else if (new->ptype == 'P' && field == 6) {
					int data;
					data = atoi(fielddata);
					new->info.prof.hireyear = data;
					field = 7;
					continue;
				} else if (new->ptype == 'P' && field == 7) {
					strcpy(&(new->info.prof.tenured), fielddata);
					break;
				} else if (new->ptype == 'S' && field == 5) {
					strcpy(new->info.stud.faculty, fielddata);
					field = 6;
					continue;
				} else if (new->ptype == 'S' && field == 6) {
					int data;
					data = atoi(fielddata);
					new->info.stud.admyear = data;
					break;
				}
			} 
		}
						
		if (command == 'I') { // Then record should be updated
			pirp = updateRecord(pirp, new);
		} else if (command == 'D') { // Then the record should be deleted
			pirp = deleteRecord(pirp, new);
			free(new);
		}

	}
	FILE *f = fopen(argv[1], "wt");
        // If it cannot open the file to write, an error message should be displayed to stderr
        if (f == NULL) {
                fprintf(stderr, "Error, unable to open %s for writing\n", argv[1]);
		free(pirp);
		return 3;
        } else {
                // If the program successfully opened the file for writing, then it must write to it
                // The program should free all the memory allocated to the linked list
		while (pirp != NULL) {
		struct PersonalInfoRecord *prev = pirp;
                if (pirp->ptype == 'S'){ // If student
			prev = pirp;
                        fprintf(f,"%s,%c,%s,%s,%d\n", pirp->id, pirp->ptype, pirp->name, pirp->info.stud.faculty, pirp->info.stud.admyear);
			pirp = pirp->next; // move to the following node
			free(prev); // delete previous node
                } else { // If professor
                        fprintf(f,"%s,%c,%s,%s,%d,%c\n", pirp->id, pirp->ptype, pirp->name, pirp->info.prof.dept, pirp->info.prof.hireyear,pirp->info.prof.tenured);
                        prev = pirp;
			pirp = pirp->next; // move to the following node
                	free(prev); // delete previous node
		}
		}	
		fclose(f);

                return 0; // Appropriate return code from this program.
		}
}
