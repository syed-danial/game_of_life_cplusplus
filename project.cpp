//The headers libriries used in this program
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

//declaring some inportant global variables
const int column = 20;
const int row = 20;
const int live = 1;
const int dead = 0;
int nei_array[200][200]={};
char grid[row][column];
char newgrid[row][column];

//declaring Functions used in this Project 
void fileInput();
/*
	First Function
	The function which is used to read the file and uses this functoin to procced furthur.
*/
void fileOutput(char grid[][column], int generations, int number_cells, int row, int column);
/*
	Second Function
	This function is used to create a file and write the coordinates and required information.
*/
void description();
/*
	Third Function
	This function is created in order to tell you the description of the game
*/
void rules();
/*
	Fourth Function
	This function is used to show you the rules of the game
*/
void initialGrid(int row, int column);
/*
	Fifth Function
	This function is used to store the grid as dead initially
*/
void sec_array(int row, int column, int secondary[][200]);
/*
	Sixth Function
	This function is used to store the coordinates in secondary array
*/
void makeGrid(char grid[][column], int row, int column);
/*
	Seventh Function
	This function is used to make the grid of the cells stored in secondary array
*/
void nextGridGenerator(char grid[][column],int neighbours);
/*
	Eighth Function
	This function is used to generate the next grid upto the generations given in the txt file
*/
void neighboursAlive(char grid[][column], int i, int j, int &neighbours);
/*
	Ninth Function
	This function is used to check the the neighbours of the alive cells
*/
void copyGrid(char from[][column], char to[][column]);
/*
	Tenth Function
	This function copies the intial grid into the next grid
*/
void cellNextState(char grid[][column], int i, int j, int neighbours);
/*
	Eleventh Function
	This function decides the next state of the grid accordingly to the live cells
*/
void neighbourArray(char grid[][column], int nei_array[][200], int i, int j);
/*
	Twelfth Function
	This funnction stores the neighbours in the nei_array
*/

//main driver

int main()
{
	//Function call for description
	description();
	
	//Function call for rules
	rules();
	
	//Function for file input and for further callof function
	fileInput();
	
	//Function call for initial grid
	initialGrid(row, column);

} 


//Decription function
void description()
{
	cout<<"\n"<<setw(50)<<"WELCOME TO THE GAME OF LIFE!"<<"\n\n";
	cout<<"In this project you will implement a mathematical game known as “Game of Life” devised by John"
		<<"Conway in 1970.\nThis zero-player game is set on a two dimensional array of cells.\n(potentially "
		<<"infinite in dimensions).\nEach cell is in a state. Grid changes over a number of discrete time steps."
		<<"\nChange of cell state determined by its current state, states of its neighbors, and the set of "
		<<"rules.";
	cout<<"\n\nThe rules of the game are given below: \n";
	
}

//rules function
void rules()
{
	cout<<"1. Two possible states for each cell\n"
		<<"a) Live\n"
		<<"b) Dead\n"
		<<"2. States can change\n"
		<<"a) Living cell can die (death).\n"
		<<"b) Dead cell can become alive (birth).\n"
		<<"3. Simple set of rules specifying\n"
		<<"a) Death (overcrowding OR underpopulation).\n"
		<<"b) Birth (reproduction)."<<endl;
	cout<<"The dead cells are shown by a blank space while the live cells are shown by '*'"<<endl;
	cout<<"\n\n\nThe program will start now!"<<endl;
}


//File input function
void fileInput()
{
	ifstream myfile;  // Function object
	int generations, number_cells, x[20]={}, y[20]={};   //  
	int neighbours; 									//	  	Declaration of variables and arrays
	int secondary[200][200]={};						   //
	
	// Function to open the file
	myfile.open("input.txt");
	
	// If input file does not open
	if(!myfile)
	{
		cout<<"The input file did not open successfully!!!!"<<endl;
	}
	
	/////  If file opens
	else
	{
		//file reading
		myfile>>generations;  //----> Reading Generation
		myfile>>number_cells; //----> Reading Number of Cells
		for(int i = 0; i < number_cells; i++)
		{
			myfile>>x[i];  ///---->   Reading x coordinates
			myfile>>y[i]; ///----->   Reading y coordinates
			secondary[x[i]][y[i]] = live; //Storing them in secondary array
			grid[x[i]][y[i]] = live; //Making the coordinates as live in the grid
		}
	}
	//Displaying Sec array
	cout<<"The secondary array is: "<<endl;
	//Function call for sec array
	sec_array(row, column, secondary);
	cout<<"THE FILE READ SUCCESSFULL!!!"<<endl;
	//Making grid of the intially grid state
	cout<<"\nGeneration # 0"<<endl;
	makeGrid(grid, row, column);
	
	//Proceeding towards the next state generations
	int counter=0;  ////////----------------> Variable to monitor the generations
	int i=0, j=0;
	while(counter<generations)
	{
		cout<<"Generation # "<<counter+1<<endl;
		//Function call of the next grid generator
		nextGridGenerator(grid, neighbours);
		//Function call for checking neighbouring array
		//There is a choice if you want to display the neighbour array 
		neighbourArray(grid, nei_array, i, j);
		//Function of copying grid
		copyGrid(newgrid, grid);
		//Function call to make the grid invovling latest cell state
		makeGrid(grid, row, column);
		counter++;  ////////-----------------> Incrementing counter
	}  
	//Function call to output the coordinates in the file
	fileOutput(grid, generations, number_cells, row, column);
	
	
}

//Function for implementating and displaying secondary array
void sec_array(int row, int column, int secondary[][200])
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			if(secondary[i][j] == live)
			//cout<<i<<" "<<j<<endl;
		}
	}

}

//Funtion for initially storing the grid as dead cells
void initialGrid(int row, int column)
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			grid[i][j] = dead;   ///--------> Initiallizing them as dead
		}
	}
	
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			newgrid[i][j] = dead; ///------> Initializing new geid for the next state as dead cells overall
		}
	}
}

//Function to implement and display the grid
void makeGrid(char grid[][column], int row, int column)
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			if(grid[i][j] == live)
			{
				cout<<"*";  //// If cells are live
			}
			else
			{
				cout<<"."; //// If cells are dead
			}
		}
	cout<<endl;	
	}
}

/// Function to check and increment the counter when there is a dead neighbours
void neighboursAlive(char grid[][column], int i, int j, int &neighbours)
{
	// Different conditons to check the neighbours 
	if(grid[i+1][j] == live)
	{
		neighbours++;
	}
	if(grid[i-1][j] == live)
	{
		neighbours++;
	}
	if(grid[i][j+1] == live)
	{
		neighbours++;
	}
	if(grid[i][j-1] == live)
	{
		neighbours++;
	}
	if(grid[i+1][j+1] == live)
	{
		neighbours++;
	}
	if(grid[i-1][j-1] == live)
	{
		neighbours++;
	}
	if(grid[i+1][j-1] == live)
	{
		neighbours++;
	}
	if(grid[i-1][j+1] == live)
	{
		neighbours++;
	}
	// Conditions END
}

// Function to implement and store the neighbours array
void neighbourArray(char grid[][column], int nei_array[][200], int i, int j)
{
	//Different conditions on stroing the neighbours into an array
	if(grid[i+1][j] == live)
	{
		nei_array[i][j] = grid[i+1][j];
	}
	if(grid[i-1][j] == live)
	{
		nei_array[i][j] = grid[i-1][j];
	}
	if(grid[i][j+1] == live)
	{
		nei_array[i][j] = grid[i][j+1];
	}
	if(grid[i][j-1] == live)
	{
		nei_array[i][j] = grid[i][j-1];
	}
	if(grid[i+1][j+1] == live)
	{
		nei_array[i][j] = grid[i+1][j+1];
	}
	if(grid[i-1][j-1] == live)
	{
		nei_array[i][j] = grid[i-1][j-1];
	}
	if(grid[i+1][j-1] == live)
	{
		nei_array[i][j] = grid[i+1][j-1];
	}
	if(grid[i-1][j+1] == live)
	{
		nei_array[i][j] = grid[i-1][j+1];
	}
	
	
	//--------------------------------------->>>> ERASE COMMENT IF YOU WANT TO DISPLAY THE COORDINATES OF NEIGHBOURS
	/*
	cout<<"The neighbours are: \n";
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			if((grid[i+1][j] == live || grid[i-1][j+1] == live || grid[i+1][j-1] == live || grid[i-1][j-1] == live || grid[i+1][j+1] == live || grid[i][j-1] == live 
				|| grid[i][j+1] == live || grid[i-1][j] == live ))
			{
				cout<<i<<","<<j<<endl;
			}
		}
	}*/
}

//Function to implement the next state of cell 
void cellNextState(char grid[][column], int i, int j, int neighbours)
{
	// if the neighbours are more than 3
	if(grid[i][j] == live && neighbours > 3)
	{
		newgrid[i][j] = dead;
	}
	// if neighbour is less than 2
	if(grid[i][j] == live && neighbours < 2)
	{
		newgrid[i][j] = dead;
	}
	// if neighbours is equal to 3
	if(grid[i][j] == dead && neighbours == 3)
	{
		newgrid[i][j] = live;
	}
	// if neighbours equal to 2 or 3 both
	if(grid[i][j] == live && (neighbours == 3 || neighbours == 2))
	{
		newgrid[i][j] = live;
	}

}

//This function generates the next state grid
void nextGridGenerator(char grid[][column],int neighbours)
{
	// neighbouring array 
	int nei_array[200]={};
	for(int i=1; i<row-1; i++)
	{
		for(int j=1; j<column-1; j++)
		{
			neighbours=0;
			// Function call to check the neighbours which willl be alive
			neighboursAlive(grid, i, j, neighbours);
			//Function to check next state  cell
			cellNextState(grid, i, j, neighbours);
		}
	}	
}

//Function to implement the copying the grid 
void copyGrid(char from[][column], char to[][column])
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			to[i][j] = from[i][j]; //copying the grid ito new grid
		}
	}
}

// Function to write the coordinates of the file
void fileOutput(char grid[][column], int generations, int number_cells, int row, int column )
{
	ofstream file;
	file.open("output.txt");
	file<<generations<<endl; ///----------> writing the generations
	file<<number_cells<<endl; ///---------> writing the number of cells
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			if(grid[i][j] == live)
			{
				file<<i<<","<<j<<endl; ////----------> Writing the coordinates of x and y 
			}
		}
	}
}
