#include <iostream>
#include<time.h>
#include <stdlib.h>
#include<conio.h>
#include<memory>
using namespace std;


//--------------------------------Class-------------------------



class Minesweeper {
    int ** matrix;                          //Frontend board
    int **board;                            //Backend board
    int score;                              //Variable to store score
public:
    char getBoardState(int x , int y);      //Function to get the specific value from the backend board
    void setBoardState(int x,int y,int ch); //Function to set a specific value at specific Coordinate of frontend board
    void setMines();                        //Function to set 7 Mines in the backend board
    void set_matrix();                      //Function to initialize the backend board with random numbers
    void set_board();                       //FUnction to initialize the front end board with zero
    void print();                           //Function to print the frontend board
    bool checkwin();                        //Function to check win
    bool legal_move(int x , int y);  		//Function to check the legal move
    int reveal(int x , int y);              //Function to reveal the value of specific index
    void play();              				//Function to play the game
    Minesweeper();                          //Constructor to initialize the matrix and Board
    virtual ~Minesweeper();                 //Destructor to Free all pointers
};


//--------------------Definition of declared function-----------------------------


//Constructor to intialize the matrix (Backend board) and Board (Frontend Board)
Minesweeper::Minesweeper() {
    score=0;
    matrix=new int * [7];  	     //Dynamically creating Array of 7 pointer variable
    board=new int * [7];  			 //Dynamically creating Array of 7 pointer variable
    for(int i = 0 ; i < 7 ; ++i )
    {
        matrix[i] = new int[7];    //Dynamically creating array of 7 integer type variable at each index
        board[i] = new int[7];     //Dynamically creating array of 7 integer type variable at each index
    }
    setMines();                     //This function will set mines in the backend board (Matrix)
    set_matrix();                   //This funtion will intialize the remaining indexes of backend board (Matrix)
    set_board();                    //This funtion will intialize indexes of frontend board (board)
}


//Function to get the specific value from the backend board
char Minesweeper::getBoardState(int x, int y) {
    return matrix[x][y];
}


//Function to set a specific value at specific Coordinate of frontend board
void Minesweeper::setBoardState(int x, int y, int ch) {
    board[x][y]=ch;
}


//Function to set 7 Mines in the backend board
void Minesweeper::setMines() {
    int MineX;
    int MineY;
    for (int i = 0; i < 7; i++) 			//Setting Up Mines
    {
        srand(time(0));
        MineX = rand() % 5;         		//Randomly generate X- coordinate
        MineY = rand() % 5;        			//Randomly generate Y- coordinate
        if (getBoardState(MineX, MineY) == 5 || (MineX == 0 && MineY == 0))
        {
            i--;
        }
        else
        {
            matrix[MineX][MineY]=5;     	//will set up Mines at the randomly generated Coordinates

        }
    }
}


//Function to intialize the backend board with random numbers
//board will be intialize with (1,2,3) only....These will be added as score
void Minesweeper::set_matrix() {
    srand(time(0));							//Setting Up Random numbers
    for (int i = 0 ; i < 7 ; i++)
    {
        for (int j = 0; j < 7; ++j) {

            if (getBoardState(i, j) != 5 )
            {
                matrix[i][j] = rand() % 3 + 1;
            }
        }
    }

}


//Function to print the frontend board
void Minesweeper::print() {
    cout<<"\n\t\tCurrent Board State is : \n\n";
    cout<<"\t\t ___________________________________________\n\n";
    for (int i = 0 ; i < 7 ; ++i) 				//Setting Up Random numbers
    {
        cout<<"\t\t";
        for (int j = 0; j < 7; ++j)
        {
            if (board[i][j]==0)
            {
                cout<<" | "<<" X ";
            }
            else if (board[i][j]==5)
            {
                cout<<" | "<<" * ";
            }
            else
            {
                cout<<" | "<<" "<<board[i][j]<<" ";
            }
        }
        cout<<" | \n\n\t\t ___________________________________________\n\n";
    }
    cout<<"\n\t\t\t\tCurrent Score : "<<score<<endl<<endl;
}


//Function to play the game
void Minesweeper::play() {
	cout<<"\n\n\t\t*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^\n\n";
    cout<<"\t\t\t\tMINE SWEEPER\n\n";
    cout<<"\t\t^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^*^\n";
    getch();
    system("cls");
    cout<<"\n\n\t\t\t\tINSTRUCTIONS\n";
    cout<<"\n\t\t--> Given is is 7 by 7 Marix.";
    cout<<"\n\t\t--> Mines are represented by * symbol.";
    cout<<"\n\t\t--> Total 7 Mines are hidden in this Matrix.";
    cout<<"\n\t\t--> Enter Coordinates to reveal the index.";    
    cout<<"\n\n\t\t\t\tBEST OF LUCK\n"; 
	getch();
    system("cls");   
    print();                                    //print initial state of board
    int x,y;                                    //variables to take in coordinates from player
    do
    {
        Re:
        int num;
        cout << "\t\tEnter Coordinates (x,y): \n";
        cout<<"\t\tx : ";cin>>x; x = x - 1;
        cout<<"\t\ty : ";cin>>y; y = y - 1;
        if (legal_move(x, y))                   //Checking whether the move is legal or not
        {
            num=reveal(x, y); 
			if(num==-1)
			{
				return;
			}                      //Reveal the value of entered Coordinate
        }
        else{
            goto Re;                            //Tag to return if coordinates are out of bound
        }
    }while(!checkwin());                        //Game will continue until frontend board == backend board
}

//FUnction to initialize the front end board with zero
void Minesweeper::set_board() {
    for (int i = 0 ; i < 7 ; i++) 				//Setting Up front end board
    {
        for (int j = 0; j < 7; ++j)
        {
            board[i][j]=0;
        }
        cout<<endl;
    }
}


//Function to check the coordinates entered by the player,will return true
// if the moves are legal and return false if the coordinates are out of bound
bool Minesweeper::legal_move(int x, int y) {
    if (x < 0 || y < 0 || x > 7 || y > 7)
    {
        cout<<"\n\t\tValue Out of Bound\n";
        return false;
    }
    else if (board[x][y]!=0)
    {
    	cout<<"\n\t\tEnter Some Unique Coordinates\n";
    	return false;
	}
    else
        return true;
}


//Function to reveal the index whose coordinates was entered by the player
int Minesweeper::reveal(int x, int y) {
    int ch = getBoardState(x,y);    		//will get the required coordinate's value from the backend board
    setBoardState(x,y,ch);          		//assign that value to the frontend board
    system("cls");
    if(ch==5)                       		//if mine found at that coordinates, then game will end
    {
        cout<<"\a\n";
        print();                    		//to print the final state of the board
        cout<<"\t\t\t\tYou found a Mine !!!";
        cout<<"\n\t\t============================================\n\n";
        cout<<"\t\t\t\tGAME OVER\n\n";
        cout<<"\t\t============================================\n\n";
        return -1;                            //Will end of game
    }
    else
    {
        score+=ch;                  		//This will add score of each turn
        print();
		return 0;                    		//This will print Frontend Board state at each turn
    }
}


//Function to compare board state with matrix state to check whether
//it's a win or player will get another chance
bool Minesweeper::checkwin() {
   for(int i = 0 ; i < 7 ; ++i )
   {
       for( int j = 0 ; j < 7 ; j++ )
       {
           if(matrix[i][j]==5)
           {
               continue;
           }
           else{
               if(board[i][j]!=matrix[i][j])
               {
                   return false;                //Will return false if both matrices won't match
               }
           }
       }
   }
   return true;                 //Will return true if all the indexes of both matrices will match
}


//Destructor to Free all pointers
Minesweeper::~Minesweeper() {
    for (int i = 0; i < 7; i++)
    {
        delete[] matrix[i];             	//delete each row of matrix
        delete[] board[i];              	//delete each row of board
    }
    delete[] matrix;                    	//delete address in matrix
    delete[] board;                     	//delete address in board
    matrix = NULL;                      	//Free double pointer matrix
    board = NULL;                       	//Free double  pointer board
    cout<<"\\n\t\t destructor call ";
}



//----------------Main function---------------


int main() {
   unique_ptr <Minesweeper> obj = make_unique <Minesweeper>();     //Object of Class
   obj->play();          //Call of play function
   
   return 0;
}

