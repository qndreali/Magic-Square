#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.c"

int main(){

	struct FreePos Free[9];
  	struct OccPos Occ [9] = {};
	
	int Board[3][3] = {};
	int Peg[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int One [3] = {}, Two [3] = {}, Three[3] = {}, Four[3] = {}, Five[3] = {}, Six  [3] = {};
	
	bool turn = true;
	int  option, i, turncount = 1;

	do{
		displayMenu();
		printf("                                       [1] Play       \n");
		printf("                                       [2] Mechanics  \n");
		printf("                                       [3] Exit       \n\e[1;97m");
		do {
			printf("\n\nEnter Option: ");
			scanf("%d", &option);
			fflush(stdin);
			        
			if(option > 2 || option < 1) 
				printf("\e[1;31m" "Invalid Option.\n" "\e[1;97m");
			            
		} while (option > 2 || option < 1); 	
		
		if(option == 2)
			displayMechanics();
		if(option == 3)
			return 0;
	} while (option != 1);
	
	system("cls");
		
	Initialization(Free);
	DisplayCurrentBoard(Board);	 
		
	while(turncount<=9) {
		if (turncount % 2 == 0)
			printf("\n\e[1;96m                                   ""Player B's Turn: \e[1;97m\n");
		else
			printf("\n\e[1;94m                                   ""Player A's Turn: \e[1;97m\n");
	
		printf("\nAvailable positions to take: ");
		for(i = 0; i < 9; i++)
			if(Free[i].freeRow!=0&&Free[i].freeCol!=0)
				printf("(%d,%d) ",Free[i].freeRow,Free[i].freeCol);
		printf("\n");
		DisplayAvailablePegs(Peg);
		printf("\nOccupied positions: "); 
		for(i = 0; i < 9; i++) 
			if(Occ[i].occRow!=0&&Occ[i].occCol!=0)
				printf("(%d,%d) ",Occ[i].occRow,Occ[i].occCol);
					
		NextPlayerMove(Free,Occ,Board,Peg,One,Two,Three,Four,Five,Six); 
	
		if ((lineSum(One) < 15 && lineSum(One)) || (lineSum(Two) < 15 && lineSum(Two)) || (lineSum(Three) < 15 && lineSum(Three)) || 
			(lineSum(Four) < 15 && lineSum(Four)) || (lineSum(Five) < 15 && lineSum(Five)) || (lineSum(Six) < 15 && lineSum(Six))) {
			turn = turncount % 2;
			(turn == false) ? printf("\n\e[1;94m                                   ""Player A's Wins! \e[1;97m\n") 
			                : printf("\n\e[1;96m                                   ""Player B's Wins! \e[1;97m\n");	
			break;
		} else
			turncount++;
	}
	
	if (turncount == 10) 
		printf("\n\e[1;94m                                   ""Player A's Wins! \e[1;97m\n");

	return 0;
}
