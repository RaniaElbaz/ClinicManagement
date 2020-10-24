/**********************************
		Clinic Management
**********************************/
#include "CLINIC.h"

void main(){
	u8 i, *input, op;
	u32 psw, id;
	bool termP = false, exit = false;
	record* PList = NULL;
	record* reslist = NULL;
	
	createList(&reslist);
	
	while(termP == false){
		exit = false;
		
		printf("\nchoose which mode:\nuser\tadmin\texit\n>>");
		input = readLine();
		
		//ADMIN MODE
		if(strcmp(input, "admin") == 0){
			for(i = 0;i <= TRY;i++){
				printf("Password: ");
				scanf("%d",&psw);
				if(psw == PASSWORD){
					printf("\t\t----Welcome Dr.----\n");
					HOLD;
					break;
				}
				else{
					printf("%u tries remaining..\n",TRY-i);
				}  
			}
			if(i > TRY){
				printf("too many tries\nClosing...");
				break;
			} 
			while(exit == false){
				printf("1.Add record\n2.edit record\n3.reserve\n4.cancel reservation\n5:exit\n");
				printf("choose from 1 to 5\n>>");
				scanf("%d",&op);
				if(op < 5){
					printf("Enter ID: ");
					scanf("%d",&id);
				}
				
				switch(op){
					case 1 : addP(&PList,id); 
							 printList(PList,MAX_PT); HOLD;
							 break;
					case 2 : editP(&PList,id);
							 printList(PList,MAX_PT);
							 break;
					case 3 : if(FindID(PList,id)){
								if(FindID(reslist,id)){
									puts("This patient has already reserved\n");
								}
								else{
									check(reslist);
									res(reslist,id);
								}
							 }
							 else{
								 printf("ID nout found"); 
							 }
							 HOLD;
							 break;							 
					case 4 : if(FindID(PList,id)){
								if(FindID(reslist,id)){
									cancel(reslist,id);
								}
							 }								
							 break;
					case 5 : exit = true; break;
					default: break;
				}
			}
		}
		
		//USER MODE
		else if(strcmp(input, "user") == 0){
			printf("1.View Record\t2.View today's reservations\n>>");
			scanf("%d",&op);
			switch(op){
				case 1: printf("Enter your ID: "); 
						scanf("%d",&id);
						if(FindID(PList,id)){
							while(PList != NULL){ //check if ID does exist
								if(PList->ID == id){
									printList(PList,1);
									break;
								}
								PList = PList->next;
							}
						}
						else{
							puts("ID not found!"); 
							HOLD;
						}
						break;
				case 2:  printresv(reslist); break;
				default: printf("Invalid choice"); HOLD; break;
			}	
		}
		
		//TERMINATE PROGRAM
		else if(strcmp(input, "exit") == 0){
			puts("\t\t----Thank You!----");
			break;
		}
		
		//INVALID CHOICE
		else{
			printf("Invalid choice .. try again please!\n");
		}
		
		free(input);
	}
}