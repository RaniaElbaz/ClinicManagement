#include "CLINIC.h"

//create list to reserve in
void createList(record** head){
	u8 i;
	
	for(i = 0;i < SLOTS;i++){
		record* node = (record*) malloc(sizeof(record));
		node->ID = 0;
		node->label = SLOTS - i;
		node->next = (*head);
		(*head) = node;
	}
}

//read input from user
u8* readLine(){
	u8 ip[BUFFER];
	u8 pos = 0;
	
	scanf("%s",ip);
	for(pos=0;ip[pos]!='\0';++pos);
	u8* input = (u8*) malloc(pos);
	strcpy(input,ip);
	
	return input;
}

//search for ID
bool FindID(record* List,u32 id){
	if(List == NULL) return false;
	while(List != NULL){ //check if ID does exist
		if(List->ID == id){
			return true;
		}
		List = List->next;
	}
	if(List == NULL) return false;
}

//add a patient record
void addP(record** List_ref,u32 id){
	u8 count = 0;
	bool not_found = false;
	u8 *tmpname;
	
	printf("\t\t----New patient record----\n");
	printf("Enter patient INFO:\n");
	
	while(count < TRY){
		if(!(FindID(*List_ref,id))) break;
		if(FindID(*List_ref,id)){
			printf("ID exists\n");
			count++;
		}
	}
	
	if(count == TRY){
		printf("too many tries..\ncheck list of patients IDs:");
		printresv(*List_ref);
		HOLD;
		return;
	}
	
	record* newrec = (record*) malloc(sizeof(record)); 
	record *last = *List_ref;
	newrec->ID  = id;
	printf("enter first name: ");
	tmpname = readLine();
	newrec->fname = tmpname;
	printf("enter last name: ");
	tmpname = readLine();
	newrec->lname = tmpname;
	printf("enter gender: ");
	scanf("%s",&newrec->gender);
	printf("enter age: ");
	scanf("%d",&newrec->age);
	newrec->next = NULL;
	if (*List_ref == NULL){ 
		*List_ref = newrec; 
		DONE;
		return; 
	} 
	while (last->next != NULL) 
		last = last->next; 
	last->next = newrec; 
	DONE;
	return; 
}

//edit a patient record
void editP(record** List_ref,u32 id){
	bool termP = false;
	u8 editkey, *tmpFname, *tmpLname;
	record* ptr = (*List_ref);
	
	if(!(FindID(ptr,id))){
			printf("Incorrect ID"); 
			HOLD;
			return;
	}
	
	if(FindID(ptr,id)){
		while(ptr != NULL){
			if(ptr->ID == id){
				break;
			}
			ptr = ptr->next;
		}
		printList(ptr,1);
		while (termP == false){
			printf("what do you want to edit?\n");
			printf("1.first name\n2.last name\n3.gender\n4.age\n5:print new patients record and exit\n>>");
			scanf("%d",&editkey);
			switch(editkey){
				case 1: printf("enter first name: ");
						tmpFname = readLine(); 
						ptr->fname = tmpFname; break;
				case 2: printf("enter last name: "); 
						tmpLname = readLine();
						ptr->lname = tmpLname; break;
				case 3: printf("enter gender: ");
						scanf("%s",&ptr->gender); break;
				case 4: printf("enter age: ");
						scanf("%d",&ptr->age); break;
				case 5: termP = true; break;
			}
		}
	}
}

//check free slots
void check(record* n){
	while(n != NULL){ //check which slots are free
		if((n->label == 1) && (n->ID == 0)){
			printf("1.From 2PM T0 2:30PM \n");
		}
		if((n->label == 2) && (n->ID == 0)){
			printf("2.From 2:30PM To 3PM \n");
		}
		if((n->label == 3) && (n->ID == 0)){
			printf("3.From 3PM To 3:30PM \n");
		}
		if((n->label == 4) && (n->ID == 0)){
			printf("4.From 3:30PM To 4PM \n");
		}
		if((n->label == 5) && (n->ID == 0)){
			printf("5.From 4PM To 4:30PM \n");
		}	
		n = n->next;
	}
}

//reserve a slot
void res(record* list,u32 id){
	u8 c;
	record* ptr = list;
	
	printf("choose which time slot(1-5)\n>>");
	scanf("%d",&c);

	while(list != NULL){
		if(list->label == c){
			list->ID = id;
			return;
		}
		list = list->next;
	}
}

//cancel reservation
void cancel(record* list,u32 id){
	while(list != NULL){
		if(list->ID == id){
			list->ID = 0;
			return;
		}
		list = list->next;
	}
}

//print all reservations
void printresv(record* n){
	puts("\t\t----Today's reservations----\n");
	
	if (n == NULL) printf("list is empty\n");
    while(n !=NULL)
    {
        if((n->label == 1)){
			if(n->ID== 0) printf("1.From 2PM T0 2:30PM |\t No appointments\n");
			else printf("\n1.From 2PM T0 2:30PM |\t %d\n",n->ID);
		}
		if((n->label == 2)){
			if(n->ID== 0) printf("2.From 2:30PM To 3PM |\t No appointments\n");
			else printf("2.From 2:30PM To 3PM |\t %d\n",n->ID);
		}
		if((n->label == 3)){
			if(n->ID== 0) printf("3.From 3PM To 3:30PM |\t No appointments\n");
			else printf("3.From 3PM To 3:30PM |\t %d\n",n->ID);
		}
		if((n->label == 4)){
			if(n->ID== 0) printf("4.From 3:30PM To 4PM |\t No appointments\n");
			else printf("4.From 3:30PM To 4PM |\t %d\n",n->ID);
		}
		if((n->label == 5)){
			if(n->ID== 0) printf("5.From 4PM To 4:30PM |\t No appointments\n");
			else printf("5.From 4PM To 4:30PM |\t %d\n",n->ID);
		}
        n = n ->next;
    }
}

//print patients record
void printList(record* n,u8 c){
	u8 i;
	puts("\n\t\t----Patient's record----\n");
	
	if (n == NULL) printf("list is empty\n");
    for(i = 0;i < c;i++){
		if (n == NULL) return;
        printf("ID: %d \t", n->ID);
		printf("name: %s %s \t", n->fname,n->lname);
		printf("gender: %c \t", n->gender);
		printf("age: %d \t", n->age);
        n = n ->next;
		printf("\n");
    }
	printf("\n");
}