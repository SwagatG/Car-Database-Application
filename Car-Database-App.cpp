//*****************************************************************************************
//  Program Filename	: Binary Read/Write Lab
//  Version				: 4.0
//  Author				: Swagat Ghimire
//  Purpose				: Documenting information in an Auto Dealership
//  Date				: September 29, 2015
//*****************************************************************************************

//Preprocessor Directives
#include <iostream>
#include <iomanip>	//required for output manipulation
#include <fstream>  //required for file I/O
#include <stdlib.h>
#include <string.h>
#include <vector>	//required for vectors
#define FILE_IN "CarRecords.dat"	//easier to use infile
#define FILE_OUT "CarRecords.dat"	//easier to use outfile

using namespace std;

//Name Constant Definitions
struct DealerInfo //Stores all info need by the dealer
{
	int inventoryNum;
	char VIN[18];
	char make[20];
	char model[20];
	char exColour[20]; //External Colour
	char inColour[20]; //Internal Colour
	char transmission[20];
	float price;
};
vector<DealerInfo> cars; //create a global vector of type DealerInfo to store all data (for ease of access)

const string line = string(80, '_'); //defines a line for easy use

//*****************************************************************************************
// Function Name: Input
// Purpose: To gather stored data from the file "CarRecords.dat"
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: File: "CarRecords.dat"
// External Outputs from Function: None
//*****************************************************************************************
void Input()
{
    ifstream input; //Used to connect to the file
    DealerInfo currentCar; //Temporarily store the current set of information before pushing to the global vector
	input.open(FILE_IN, ios::in|ios::binary); //open the connection
 
	if(!input ) //Ensure that the file is opened
	{
		cout << "Can't find input file " << FILE_IN << ".\n"; //If not, tell them there is no info
		cout << "Starting a new record.\n"; //Let them know they'll start a new file
		system("Pause");
		system("CLS");
	}
	else //If there is a file with data
	{ 
 		while (!input.eof()) //Until the end of file is reached
 		{
			input.read((char *) &currentCar, sizeof(DealerInfo)); //Read info and store to temporary struct
			cars.push_back(currentCar); //push the info on temporary struct to the main global vector
		}
		cars.pop_back(); //I didn't recognize then end of file character as the end of file and did one more loop. Delete that false input.
	}
	input.close(); //close connection
}	

//*****************************************************************************************
// Function Name: Title
// Purpose: To quickly output a title on demand
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: Cout of the title and a line.
//*****************************************************************************************
void Title()
{
	cout << "Car Dealership Inventory" << endl << line << endl;
}

//*****************************************************************************************
// Function Name: Welcome
// Purpose: To quickly output a welcoming statement
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: File: None
// External Outputs from Function: Cout of Welcome statement
//*****************************************************************************************
void Welcome()
{
	cout << "Welcome to the Car Dealership Inventory Program." << endl << endl;
}

//*****************************************************************************************
// Function Name: Sort
// Purpose: To sort information in the global vector
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: File: None
// External Outputs from Function: None
//*****************************************************************************************
void Sort()
{
	DealerInfo temp; //To store the largest value as space is made for it
	int max, checks; // max is the location of the largest inventory num. Checks is the number of cars that must be checked (you don't have to check with previously foudn maxes)
	int arraySize = cars.size(); //To store the number of cars in the vector
	for (int i = 0; i < arraySize; i++) //Repeat as many times as there are cars
	{
		int checks = arraySize -1 - i; //Check up until the last car that hasn't already been found to be a relative max
		max = 0; //Set the first car as the max
		for (int j = 0; j <= checks; j++) // check as many times as needed
		{
			if (cars[j].inventoryNum > cars[max].inventoryNum) //if the next car has a bigger inventoryNum than the current max
			{
				max = j; //then set that car as the max
			}
		}
		temp = cars[max]; //move the max to a temp location
		cars[max] = cars[checks]; //move the last car that hasn't been found to be a max to the current max's position
		cars[checks] = temp; //move the current max from the temp location to the furthest spot available.
	}
}

//*****************************************************************************************
// Function Name: Search
// Purpose: To find the position in the array of a given inventory number
// Inputs to Function: Inventory Number
// Outputs from Function: Location in array of that number
// External Inputs to Function: File: None
// External Outputs from Function: None
//*****************************************************************************************
int Search(int InvNum)
{
	int result, isResult = 0; //result is the found location, isResult ensures that a result has been found
	for (int i = 0; i < cars.size(); i ++) //for each element in the global vector
	{
		if (cars[i].inventoryNum == InvNum) // check the queried InvNum with it's inventoryNum, if there is a match
		{
			result = i; //set the result to that location in the array
			isResult += 1; //record that there is a match
			break;
		}
	}
	if (isResult > 0) //If there is a result
	{
		return result; //return the result
	}
	else //If there is no result
	{
		return -1; //Return a negative value (can't be an array position). This is understood by other functions as no matches.
	}
}

//*****************************************************************************************
// Function Name: DeleteVehicle
// Purpose: To remove a vehicle from the directory
// Inputs to Function: vehicleNum - the position of the vehicle in teh array
// Outputs from Function: None
// External Inputs to Function: File: cin of responses to prompts (i.e. inventoryNum or isDelete Value) 
// External Outputs from Function: cout of prompts and vehicle information
//*****************************************************************************************
void DeleteVehicle(int vehicleNum)
{
	int searchQuery, searchResult, numCars; //Used to find the location of the vehicle should it's position be unknown
	char isDelete; //used ensure that the user wishes to delete
	system("CLS");
	Title();
	if (vehicleNum < 0) //if the user hasn't decided on the vehicle to delte, this function will be seeded with -1
	{
		cout << "Please enter the inventory number of the vehicle you wish to find.\nAlternatively, enter '0' to clear all records.\n"; //it will then ask them for a invNum, or a 0 to delete everything
		do
		{
			cout << "\nEnter Number to Search (1000-9999 or 0): ";
			cin >> searchQuery;
		} while ((searchQuery < 1000 || searchQuery > 9999) && searchQuery != 0); //Error Prevention
	
		if (searchQuery == 0) // if they decided to delete everthing
		{
			cout << "\nAre you certain that you wish to delete ALL of your data?\n"; //Ensure that they are certain they wish to do this
			system("Pause"); //Increase chances of user reading previous statement
			do
			{
				cout << "\nEnter 'y' for yes, or 'n' for no: ";	//prompt the user to input a command
				cin >> isDelete;		
			} while (tolower(isDelete) != 'y' && tolower(isDelete) != 'n');//ensure the choice is valid
			
			if (tolower(isDelete) == 'y') //if they still wish to clear all data
			{
				numCars = cars.size(); //number of cars in the vector
				for (int i = 0; i < numCars; i++) //for every car documented
				{
					cars.pop_back(); //delete the last car in the array (thus all of them)
				}
				vehicleNum = -2; //set vehicleNum to -2 to have a seperate path in the next if statement
			}
		}
		else //if they do not wish to delete everything
		{
			vehicleNum = Search(searchQuery); //Input the inventoryNum they chose into the search function, and store the result
		}
		
	}
	if (vehicleNum == -1) //If it does not find a match
	{
		cout << "There is no vehicle with the inventory number " << searchQuery << ".\n"; //inform user
		system ("Pause");
		system ("CLS");
	}
	else if (vehicleNum == -2) //If the user has deleted all data
	{
		cout << endl << line << endl << "All of your records have been deleted.\n"; //inform user
		system ("Pause");
		system ("CLS");
	}
	else //if there is a match
	{
		cout << "Deleting:\n\nVehicle Information:\n\n"; //Give user all the vehicle info
		cout << "Inventory Number: " << cars[vehicleNum].inventoryNum << endl;
		cout << "Auto VIN: " << cars[vehicleNum].VIN << endl;
		cout << "Make: " << cars[vehicleNum].make << endl;
		cout << "Model: " << cars[vehicleNum].model << endl;
		cout << "Exterior Colour: " << cars[vehicleNum].exColour << endl;
		cout << "Interior Colour: " << cars[vehicleNum].inColour << endl;
		cout << "Transmission Type: " << cars[vehicleNum].transmission << endl;
		cout << "Enter Retail Price: $" << cars[vehicleNum].price << endl << endl;
		cout << "\nWould you like to DELETE this car?"; //ask that they wish to delete
		do //Ensure that a valid answer is selected
		{
			cout << "\nEnter 'y' or 'n': "; //give options
			cin >> isDelete;
		} while (tolower(isDelete) != 'n' && tolower(isDelete) != 'y'); //Error Prevention
		if (tolower(isDelete) == 'y') //if they confirm wanting to delte
		{
			cars[vehicleNum].inventoryNum = 10000; //give that vehicle an invNum bigger than any valid options
			Sort(); //Sort it to move that vehicle to the end of the array
			cars.pop_back(); //Delete the last item in the array
		} 
	}
	system ("CLS"); 
}

//*****************************************************************************************
// Function Name: EditInfo
// Purpose: To allow user to edit information of previously declared cars
// Inputs to Function: ChangedCar - car they wish to change
// Outputs from Function: ChangedCar - the car data after edits
// External Inputs to Function: File: cin of new information for the old cars
// External Outputs from Function: Cout of prompts and Vehicle Information 
//*****************************************************************************************
DealerInfo EditInfo(DealerInfo ChangedCar)
{
	char isCorrect, editChoice; //to determine if they wish to edit at all, and what they want to edit
	int oldNum = Search(ChangedCar.inventoryNum); //used to determine the position of the original car (if it's already in the vector) New cars will not be there
	int newNum;
	do
	{
		system ("CLS");
		Title();
		cout << "Editing:\n\nVehicle Information: \n\n";
		cout << "Inventory Number: " << ChangedCar.inventoryNum << endl; //Show user all of the car's info before asking to edit
		cout << "Auto VIN: " << ChangedCar.VIN << endl;
		cout << "Make: " << ChangedCar.make << endl;
		cout << "Model: " << ChangedCar.model << endl;
		cout << "Exterior Colour: " << ChangedCar.exColour << endl;
		cout << "Interior Colour: " << ChangedCar.inColour << endl;
		cout << "Transmission Type: " << ChangedCar.transmission << endl;
		cout << "Enter Retail Price: $" << ChangedCar.price << endl << endl;
		cout << "\nWould you like to edit this information?";
		do
		{
			cout << "\nEnter 'y' or 'n': "; //prompt user to choose an option
			cin >> isCorrect;
		} while (tolower(isCorrect) != 'n' && tolower(isCorrect) != 'y'); //ensure that the option is valid
		
		if (tolower(isCorrect) == 'y') // if they wish to edit
		{
			cout << "\nWhich Item Would you like to edit? Enter...\n\t1 - Inventory Number\n\t2 - VIN\n\t3 - Make\n\t4 - Model\n\t5 - Exterior Colour\n\t6 - Interior Colour\n\t7 - Transmission Type\n\t8 - Retail Price\n";
			//list all the options they have
			do
			{
				cout << "\nSelection: ";
				cin >> editChoice;
				if (editChoice !='1' && editChoice !='2' && editChoice !='3' && editChoice !='4' && editChoice !='5' && editChoice !='6' && editChoice !='7' && editChoice !='8')
				{
					cout << "Invalid Selection.\n";//If they choose an invalid number, inform them
				}
			} while (editChoice !='1' && editChoice !='2' && editChoice !='3' && editChoice !='4' && editChoice !='5' && editChoice !='6' && editChoice !='7' && editChoice !='8');
			//when a valid number is chosen continue
			switch (editChoice) //depending on the value they wish to change...
			{
				case '1':	do //If they wish to edit inventory number
							{
								cout << "\nEnter Inventory Number (1000 - 9999): ";
								cin >> ChangedCar.inventoryNum;
								newNum = Search(ChangedCar.inventoryNum); //Finds the value of any previous vehicles with the chosen inventory num
								if (oldNum >= 0) //If the new number has matches
								{
									if (newNum >= 0 && newNum != oldNum)//if the match is not the same as this car's initial number
									{
										cout << "This Inventory number is already taken by a " << cars[newNum].exColour << " " << cars[newNum].make << " " << cars[newNum].model << ".\nPlease use another.\n";
										ChangedCar.inventoryNum = 0;
										//inform user that the selection is taken, and set the value to 0 so they repeat the loop
									}
								}
							} while (ChangedCar.inventoryNum < 1000 || ChangedCar.inventoryNum > 9999); //continue until there is a valid number
							break;
				case '2':	cout << "Enter Auto VIN: "; //Changing the Auto VIN
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.VIN, 20, '\n');
							break;
				case '3':	cout << "Enter Make: "; //Changing the Make
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.make, 20, '\n');
							break;
				case '4':	cout << "Enter model: "; //Changing the Model
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.model, 20, '\n');
							break;
				case '5':	cout << "Enter Exterior Colour: "; //Changing the exterior Colour
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.exColour, 20, '\n');
							break;
				case '6':	cout << "Enter Interior Colour: "; //Changing the interior Colour
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.inColour, 20, '\n');
							break;
				case '7':	cout << "Enter Transmission Type: "; // Changing the Transmission
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.transmission, 20, '\n');
							break;
				case '8':	cout << "Enter price: $"; //Changing the price
							cin >> ChangedCar.price;
							break;
			}
		}
	} while (tolower(isCorrect) != 'n'); //Continue editing until user chooses not to
	
	return ChangedCar; //Return the altered information.
}

//*****************************************************************************************
// Function Name: Menu
// Purpose: To allow user to select what they wish to do
// Inputs to Function: None
// Outputs from Function: char selection - User's decision of what to do
// External Inputs to Function: File: cin of the user's selection
// External Outputs from Function: Cout of prompts to get the selection 
//*****************************************************************************************
char Menu()
{
	char selection = '0'; //make slection invalid until the user enters a viable value
	cout << "Menu\n\t1)Enter a New Vehicle\n\t2)Display Vehicle Inventory\n\t3)Search for Vehicle (By Inventory Number)\n\t4)Delete A Vehicle\n\t5)Exit This Program\n";
	//Provide options
	do
	{
		cout << "\nSelection: "; //Prompt for selection
		cin >> selection;
		if (selection !='1' && selection !='2' && selection !='3' && selection !='4'&& selection !='5') //if the selection is invalid
		{
			cout << "Invalid Selection.\n"; //Inform user of invalid selection
		}
	} while (selection !='1' && selection !='2' && selection !='3' && selection !='4' && selection !='5');//if the selection is valid, continue
	return selection;//return the selection
}

//*****************************************************************************************
// Function Name: NewEntry
// Purpose: To allow the user to input information of a new car
// Inputs to Function: None
// Outputs from Function: newCar - The user's information on the new car
// External Inputs to Function: File: cin of new information for the new car
// External Outputs from Function: Cout of prompts to gather information
//*****************************************************************************************
DealerInfo NewEntry()
{
	DealerInfo newCar; // stores user's info
	int oldNum; //finds if the number has been searched before
	system ("CLS");
	Title();
	cout << "New Entry:\n";
	do
	{
		cout << "\nEnter Inventory Number (1000 - 9999): ";
		cin >> newCar.inventoryNum;
		oldNum = Search(newCar.inventoryNum); //check to see if previous cars have that number
		if (oldNum >= 0) //if there is a car that has that number
		{
			cout << "This Inventory number is already taken by a " << cars[oldNum].exColour << " " << cars[oldNum].make << " " << cars[oldNum].model << ".\nPlease use another.\n";
			newCar.inventoryNum = 0; //inform user and set the number to 0, forcing the loop to repeat
		}
	} while (newCar.inventoryNum < 1000 || newCar.inventoryNum > 9999); //continue until there is a valid input
	
	cout << "Enter Auto VIN (17 Character): "; //get the VIN
	cin.ignore(100, '\n');
	cin.getline(newCar.VIN, 20, '\n');
	cout << "Enter Make: "; //get the Make
	//cin >> newCar.make;
	cin.getline(newCar.make, 20, '\n');
	cout << "Enter Model: "; //get the Model
	cin.getline(newCar.model, 20, '\n');
	cout << "Enter Exterior Colour: "; //get the Exterior Colour
	cin.getline(newCar.exColour, 20, '\n');
	cout << "Enter Interior Colour: "; //get the Interior Colour
	cin.getline(newCar.inColour, 20, '\n');
	cout << "Enter Transmission Type: "; //get the Transmission Type
	cin.getline(newCar.transmission, 20, '\n');
	cout << "Enter Retail Price: $"; // Get the Price
	cin >> newCar.price;
	
	newCar = EditInfo(newCar); // ask user if they wish to edit through EditInfo();
	
	system ("CLS");
	return newCar; //return user's info
}

//*****************************************************************************************
// Function Name: DisplayInfo
// Purpose: To allow user to see previously entered cars. It then allows them to edit and delete
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: File: cin of inventory Nums to find, edit/delete.
// External Outputs from Function: Cout of prompts and Vehicle Information 
//*****************************************************************************************
void DisplayInfo()
{
	int numCars = cars.size(); //size of vector
	int infoNum, foundCar; //infoNum is the searched inventory num; foundCar is the position of the found inventory number in the vector
	do
	{
		system ("CLS");
		Title();
		cout << setiosflags(ios::left) << setw(10) << "Inv Num" << setw(20) << "VIN" << setw(20) << "Make" << setw(20) << "Model" << setw(10) << "Price" << line << endl;
		//Headings
		for (int i = 0; i < numCars; i++)//Output each car's important information
		{
			cout << setiosflags(ios::left) << setw(10) << cars[i].inventoryNum << setw(20) << cars[i].VIN << setw(20) << cars[i].make << setw(20) << cars[i].model << setw(10) << setw(1) << "$" << setw(9) << std::fixed << setprecision(2) << cars[i].price << endl;
		}
		
		cout << line << endl << "To view more detailed records, enter the Inventory Number.\nTo return to menu, enter '0'.\n";
		do
		{
			cout << "Selection (1000-9999 OR 0): ";
			cin >> infoNum;
			if (infoNum != 0) // if they have not chosen to exit
			{
				foundCar = Search(infoNum); //search for the number they entered (among inventory numbers)
				if (foundCar == -1 ) //if the search does not find anything
				{
					cout << "There is no car with the inventory number " << infoNum << ".\n"; //inform user
					infoNum = 1; //force the program to repeat the do while loop
				}
			}
		} while ((infoNum < 1000 || infoNum > 9999) && infoNum != 0);//ensure that a valid number is input
		
		if (infoNum != 0) //if the user has not chosen to exit
		{
			cars[foundCar] = EditInfo(cars[foundCar]); //ask user if they would like to edit the found car
			DeleteVehicle(foundCar); //ask user if they would like to delete the car
			Sort();
		}
		
	} while (infoNum != 0); //while the user chooses not to exit
	system("CLS");
}

//*****************************************************************************************
// Function Name: UserSearch
// Purpose: To provide an interfact through which the user can search cars (as opposed to the back end Search();)
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: Cin of searchquery, and what to do with any results
// External Outputs from Function: Cout of prompts
//*****************************************************************************************
void UserSearch()
{
	int searchQuery, searchResult; //the inventoryNum searched for and the result of the search
	system("CLS");
	Title();
	cout << "Please enter the inventory number of the vehicle you wish to find.";
	do
	{
		cout << "\nEnter Number to Search (1000-9999): "; //ensure that a valid inventory number is chosen
		cin >> searchQuery;
	} while (searchQuery < 1000 || searchQuery > 9999);
	
	searchResult = Search(searchQuery); // search for the inventory number
	
	if (searchResult < 0) //if there are no results
	{
		cout << "There is no vehicle with the inventory number " << searchQuery << ".\n"; //inform user
		system ("Pause");
		system ("CLS");
	}
	else //if there are results
	{
		cout << "A result has been found.\n"; //inform user
		system ("PAUSE");
		cars[searchResult] = EditInfo(cars[searchResult]); //allow user to edit result
		DeleteVehicle(searchResult); //allow user to delete result
	}
}

//*****************************************************************************************
// Function Name: Output
// Purpose: To paste all the data onto a binary file
// Inputs to Function: None
// Outputs from Function: None
// External Inputs to Function: None
// External Outputs from Function: Information is written to "CarRecords.dat"
//*****************************************************************************************
void Output()
{
	ofstream output; //define the variable through which the program will write
	output.open(FILE_OUT, ios::out|ios::binary); //set the file as "CarRecords.dat", and ensure that it is output in binary
	for (int i = 0; i < cars.size(); i ++) //for each car in the vector
	{
		output.write((char *) &cars[i], sizeof(DealerInfo)); //output the car's information
	}
	output.close(); //close the connection to the file
}

int main()
{
    //Variable Declarations:
    char userChoice;
	//Function Body
	Input(); //Gather all prior data
	do
	{
		Title(); //Preliminary Setup (Aesthetic)
		Welcome(); //Welcome user
		userChoice = Menu(); //Provide a menu
		
		switch (userChoice) //Based on their choice
		{
			case '1': 	cars.push_back(NewEntry()); //push a new entry into the vector
						break;
			case '2': 	DisplayInfo(); //Display all data currently available to the program
						break;
			case '3':	UserSearch(); //Allow user to search through previous vehicles
						break;
			case '4':	DeleteVehicle(-1); //Allow user to delete vehicles. The -1 will cause the function to prompt the user to select a vehicle number to delte.
						break;			
		}
		Sort(); //After each edit, output the information to make sure it stays organized
		Output(); //Output each time they do anything to ensure that accidental exits won't corrupt data
	} while (userChoice != '5'); //Continue until the user wishes to exit
	
	Output();
	cout << "Your data has been output to " << FILE_OUT << ".\n"; //inform the user about the storage location of the data
	cout << "You may continue next time you use this program.\n"; //inform user that they can continue using their prior data
	cout << "Thank you for using this program.\n"; //Thank the user for using the program
    system("PAUSE");
    return 0;
}
//end function main
