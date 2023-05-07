#define HLINE 			205
#define VLINE 			186
#define TLCORNER		201
#define TRCORNER		187
#define BLCORNER		200
#define BRCORNER		188
#define HDLINE			203
#define HULINE			202
#define VLLINE			204
#define VRLINE			185
#define VHLINE			206

struct FreePos    
{
	int freeRow;
	int freeCol;
};

struct OccPos
{
	int occRow;
	int occCol;
};

void Initialization(struct FreePos Free[]) {
	int row = 1;
	int col = 1;

	for (int i = 0; i < 9; i++) {
		Free[i].freeRow = row;
		Free[i].freeCol = col;
		col++;
		if (col > 3) {
			col = 1;
			row++;
		}
	}
}

int SearchFree(struct FreePos Free[], int row, int col) {	
	for(int i = 0; i < 9; i++)
		if(row == Free[i].freeRow && col == Free[i].freeCol)
			return 1;
	return 0;
}

void RemoveFromFree(struct FreePos Free[], struct OccPos Occ[], int row, int col) {   
	for(int i = 0; i < 9; i++)
        if(Free[i].freeRow == row && Free[i].freeCol == col) {
            Occ[i] = (struct OccPos) {Free[i].freeRow, Free[i].freeCol};
            Free[i] = (struct FreePos) {0, 0};
        }
}

void input(int* row, int* col, int* peg) {
	do { 
		printf("\n\nEnter Row and Column: ");
		scanf("%d %d", row, col);
		fflush(stdin);
		
		if (*row < 1 || *row > 3 || *col < 1 || *col > 3)
			printf("\e[1;31m" "Invalid Option. Please choose between 1-3\n" "\e[1;97m");
			
	} while (*row < 1 || *row > 3 || *col < 1 || *col > 3);
	
	do { 
		printf("Enter the desired peg: ");
		scanf("%d", peg);
		fflush(stdin);
		
		if (*peg < 1 || *peg > 9)
			printf("\e[1;31m" "Invalid Option. Please choose between 1-9\n" "\e[1;97m");
			
	} while (*peg < 1 || *peg > 9);
}

int SearchPeg(int Peg[], int peg) {	
	for(int i = 0; i < 9; i++)
		if(peg == Peg[i])  
			return 1;
	return 0;
}

void AddPegToRoworCol(int arr[], int peg) {
	int i = 0;
	
	while (i < 3 && arr[i] != 0)
		i++;
	if (i < 3)
		arr[i] = peg;
}

void RemovePeg(int Peg[], int peg) {
	for(int i = 0; i < 9; i++)
		if(peg == Peg[i])  
			Peg[i] = 0;	
}

void DisplayAvailablePegs(int Peg[]) {
	printf("Available Pegs to take: ");
	for(int i = 0; i < 9; i++) {
		if(Peg[i] != 0)
			printf("%d ", Peg[i]);
	}
}

void DisplayCurrentBoard(int Board[][3]){
    	int i, j;
    
    	printf("\e[1;93m" 
	       "              ""  __  __   _   ___ ___ ___   ___  ___  _   _  _   ___ ___            \n"
	       "              "" |  \\/  | /_\\ / __|_ _/ __| / __|/ _ \\| | | |/_\\ | _ \\ __|      \n"
	       "              "" | |\\/| |/ _ \\ (_ || | (__  \\__ \\ (_) | |_| / _ \\|   / _|       \n"
	       "              "" |_|  |_/_/ \\_\\___|___\\___| |___/\\__\\_\\\\___/_/ \\_\\_|_\\___| \n\n\n" "\e[1;97m");

	printf("                                   ""    1   2   3\n");
    	printf("                                   ""  %c%c%c%c%c%c%c%c%c%c%c%c%c\n", TLCORNER, HLINE, HLINE, HLINE, HDLINE, HLINE, HLINE, HLINE, HDLINE, HLINE, HLINE, HLINE, TRCORNER);

    	for(i = 0; i < 3; i++) {
        	printf("                                   ""%d ", i + 1);
       		for(j = 0; j < 3; j++)
            		printf("%c %c ", VLINE, Board[i][j] != 0 ? '0' + Board[i][j] : 'X');
        	printf("%c\n", VLINE);

        	(i != 2) ? printf("                                   "
		                  "  %c%c%c%c%c%c%c%c%c%c%c%c%c\n", VLLINE, HLINE, HLINE, HLINE, VHLINE, HLINE, HLINE, HLINE, VHLINE, HLINE, HLINE, HLINE, VRLINE)
                 	 : printf("                                   "
				  "  %c%c%c%c%c%c%c%c%c%c%c%c%c\n", BLCORNER, HLINE, HLINE, HLINE, HULINE, HLINE, HLINE, HLINE, HULINE, HLINE, HLINE, HLINE, BRCORNER);
    }
}

void NextPlayerMove(struct FreePos Free[], struct OccPos Occ[], int Board[][3], int Peg[], int One[], int Two[], int Three[], int Four[], int Five[], int Six[]) {
	int row, col, peg;
	bool ok = false, next = false;

	do {
		input(&row, &col, &peg);

		if(SearchFree(Free, row, col) == 0) 
			printf("\e[1;31m""Position has been taken\n""\e[1;97m");
		if(SearchPeg(Peg, peg) == 0) 
			printf("\e[1;31m""Peg has been taken\n""\e[1;97m");

	} while (!SearchFree(Free, row, col) || !SearchPeg(Peg, peg));

	RemoveFromFree(Free, Occ, row, col);

	if(row == 1) AddPegToRoworCol(One, peg), next = true;
	if(row == 2) AddPegToRoworCol(Two, peg), next = true;
	if(row == 3) AddPegToRoworCol(Three, peg), next = true;

	if(next && col == 1) AddPegToRoworCol(Four, peg);
	if(next && col == 2) AddPegToRoworCol(Five, peg);
	if(next && col == 3) AddPegToRoworCol(Six, peg);

	Board[row - 1][col - 1] = peg;
	RemovePeg(Peg, peg);
	system("cls");
	DisplayCurrentBoard(Board);
}

int lineSum(int line[]){
    	int lineSum = 0;
	
   	if (line[0] && line[1] && line[2])
        	lineSum = line[0] + line[1] + line[2];
    
    	return lineSum;
}

void displayMenu()
{
	printf("\e[1;93m              "" __    __     ______     ______     __     ______ \n");
	printf("              ""/\\ `-./  \\   /\\  __ \\   /\\  ___\\   /\\ \\   /\\  ___\\ \n");
	printf("              ""\\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\ \\__ \\  \\ \\ \\  \\ \\ \\____ \n");
	printf("              "" \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\  \\ \\_____\\  \n");
	printf("              ""  \\/_/  \\/_/   \\/_/\\/_/   \\/_____/   \\/_/   \\/_____/ \n");
	printf("          "" ______     ______     __  __     ______     ______     ______   \n");
	printf("          ""/\\  ___\\   /\\  __ \\   /\\ \\/\\ \\   /\\  __ \\   /\\  == \\   /\\  ___\\ \n");
	printf("          ""\\ \\___  \\  \\ \\ \\/\\_\\  \\ \\ \\_\\ \\  \\ \\  __ \\  \\ \\  __<   \\ \\  __\\ \n");
	printf("          "" \\/\\_____\\  \\ \\___\\_\\  \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\ \\_____\\ \n");
	printf("          ""  \\/_____/   \\/___/_/   \\/_____/   \\/_/\\/_/   \\/_/ /_/   \\/_____/ \n");
	printf("\n\n\n");
}

void displayMechanics(){
	system("cls");
	displayMenu();
	printf("                                 What is a Magic Square?\n" "\e[1;97m"
	       "           A Magic Square is an arrangement of the numbers 1 - 9 in a 3x3 grid\n"
		   "                 wherein the sum of all rows and all  columns equal to 15.\n\n"
		   "\e[1;93m                                     Game Mechanics:\n" "\e[1;97m"
		   " Player A picks a peg (any number from 1 - 9) and places it in a free tile on the board.\n\n"
		   " Once player A has made their move, their chosen tile will be classified as [occupied]\n"
		   "                           and player B will  take their turn.\n\n"
		   "           The game ends when a row/column is formed and its sum is less than\n"
		   "      or when the board is filled up and the sum of all rows and columns equal to 15.\n\n"
		   "      The peg values cannot be repeated and it cannot be placed in an [occupied] tile.\n\n\n");
	printf("                               Press Enter to Continue ...");
	getchar();
	system("cls");
	
	
}
