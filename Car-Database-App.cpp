//*****************************************************************************************
//  Program Filename	: Binary Read/Write Lab
//  Version				: 3.0
//  Author				: Swagat Ghimire
//  Purpose				: Documenting information of an Auto Dealership
//  Date				: September 29, 2015
//*****************************************************************************************
//Preprocessor Directives
#include <iostream>
#include <iomanip>
#include <fstream>  //required for file I/O
#include <stdlib.h>
#include <string.h>
#include <vector>
#define FILE_IN "CarRecords.dat"
#define FILE_OUT "CarRecords.dat"

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
	int searchQuery, searchResult; //Used to find the location of the vehicle should it's position be unknown
	char isDelete; //used ensure that the user wishes to delete
	system("CLS");
	Title();
	if (vehicleNum < 0) //if the user hasn't decided on the vehicle to delte, this function will be seeded with -1
	{
		cout << "Please enter the inventory number of the vehicle you wish to find."; //it will then ask them for a invNum
		do
		{
			cout << "\nEnter Number to Search (1000-9999): ";
			cin >> searchQuery;
		} while (searchQuery < 1000 || searchQuery > 9999); //Error Prevention
	
		vehicleNum = Search(searchQuery); //Input the inventoryNum into the search function
	}
	if (vehicleNum == -1) //If it does not find a match
	{
		cout << "There is no vehicle with the inventory number " << searchQuery << ".\n"; //inform user
		system ("Pause");
		system ("CLS");
	}
	else //if there is a match
	{
		cout << "Vehicle Information:\n\n"; //Give user all the vehicle info
		cout << "Inventory Number: " << cars[vehicleNum].inventoryNum << endl;
		cout << "Auto VIN: " << cars[vehicleNum].VIN << endl;
		cout << "Make: " << cars[vehicleNum].make << endl;
		cout << "Model: " << cars[vehicleNum].model << endl;
		cout << "Exterior Colour: " << cars[vehicleNum].exColour << endl;
		cout << "Interior Colour: " << cars[vehicleNum].inColour << endl;
		cout << "Transmission Type: " << cars[vehicleNum].transmission << endl;
		cout << "Enter Retail Price: $" << cars[vehicleNum].price << endl << endl;
		cout << "\nWould you like to delete this car?"; //ask that they wish to delete
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
	DealerInfo OldCar = ChangedCar; //Store old info (used to ensure they can input the same inventoryNum if they messed up)
	char isCorrect, editChoice; //to determine if they wish to edit at all, and what they want to edit
	int oldNum; //
	do
	{
		system ("CLS");
		Title();
		cout << "Inventory Number: " << ChangedCar.inventoryNum << endl;
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
			cout << "\nEnter 'y' or 'n': ";
			cin >> isCorrect;
		} while (tolower(isCorrect) != 'n' && tolower(isCorrect) != 'y');
		
		if (tolower(isCorrect) == 'y')
		{
			cout << "\nWhich Item Would you like to edit? Enter...\n\t1 - Inventory Number\n\t2 - VIN\n\t3 - Make\n\t4 - Model\n\t5 - Exterior Colour\n\t6 - Interior Colour\n\t7 - Transmission Type\n\t8 - Retail Price\n";
			do
			{
				cout << "\nSelection: ";
				cin >> editChoice;
				if (editChoice !='1' && editChoice !='2' && editChoice !='3' && editChoice !='4' && editChoice !='5' && editChoice !='6' && editChoice !='7' && editChoice !='8')
				{
					cout << "Invalid Selection.\n";
				}
			} while (editChoice !='1' && editChoice !='2' && editChoice !='3' && editChoice !='4' && editChoice !='5' && editChoice !='6' && editChoice !='7' && editChoice !='8');
			
			switch (editChoice)
			{
				case '1':	do
							{
								cout << "\nEnter Inventory Number (1000 - 9999): ";
								cin >> ChangedCar.inventoryNum;
								oldNum = Search(ChangedCar.inventoryNum);
								if (oldNum >= 0)
								{
									if (cars[oldNum].inventoryNum != OldCar.inventoryNum)
									{
										cout << "This Inventory number is already taken by a " << cars[oldNum].exColour << " " << cars[oldNum].make << " " << cars[oldNum].model << ".\nPlease use another.\n";
										ChangedCar.inventoryNum = 0;
									}
								}
							} while (ChangedCar.inventoryNum < 1000 || ChangedCar.inventoryNum > 9999);
							break;
				case '2':	cout << "Enter Auto VIN: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.VIN, 20, '\n');
							break;
				case '3':	cout << "Enter Make: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.make, 20, '\n');
							break;
				case '4':	cout << "Enter model: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.model, 20, '\n');
							break;
				case '5':	cout << "Enter Exterior Colour: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.exColour, 20, '\n');
							break;
				case '6':	cout << "Enter Interior Colour: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.inColour, 20, '\n');
							break;
				case '7':	cout << "Enter Transmission Type: ";
							cin.ignore(100, '\n');
							cin.getline(ChangedCar.transmission, 20, '\n');
							break;
				case '8':	cout << "Enter price: $";
							cin >> ChangedCar.price;
							break;
			}
		}
	} while (tolower(isCorrect) != 'n');
	
	return ChangedCar;
}

char Menu()
{
	char selection = '0';
	cout << "Menu\n\t1)Enter a New Vehicle\n\t2)Display Vehicle Inventory\n\t3)Search for Vehicle (By Inventory Number)\n\t4)Delete A Vehicle\n\t5)Exit This Program\n";
	do
	{
		cout << "\nSelection: ";
		cin >> selection;
		if (selection !='1' && selection !='2' && selection !='3' && selection !='4'&& selection !='5')
		{
			cout << "Invalid Selection.\n";
		}
	} while (selection !='1' && selection !='2' && selection !='3' && selection !='4' && selection !='5');
	return selection;
}

DealerInfo NewEntry()
{
	DealerInfo newCar;
	int oldNum;
	system ("CLS");
	Title();
	cout << "New Entry:\n";
	do
	{
		cout << "\nEnter Inventory Number (1000 - 9999): ";
		cin >> newCar.inventoryNum;
		oldNum = Search(newCar.inventoryNum);
		if (oldNum >= 0)
		{
			cout << "This Inventory number is already taken by a " << cars[oldNum].exColour << " " << cars[oldNum].make << " " << cars[oldNum].model << ".\nPlease use another.\n";
			newCar.inventoryNum = 0;
		}
	} while (newCar.inventoryNum < 1000 || newCar.inventoryNum > 9999);
	
	cout << "Enter Auto VIN (17 Character): ";
	cin.ignore(100, '\n');
	cin.getline(newCar.VIN, 20, '\n');
	cout << "Enter Make: ";
	//cin >> newCar.make;
	cin.getline(newCar.make, 20, '\n');
	cout << "Enter Model: ";
	cin.getline(newCar.model, 20, '\n');
	cout << "Enter Exterior Colour: ";
	cin.getline(newCar.exColour, 20, '\n');
	cout << "Enter Interior Colour: ";
	cin.getline(newCar.inColour, 20, '\n');
	cout << "Enter Transmission Type: ";
	cin.getline(newCar.transmission, 20, '\n');
	cout << "Enter Retail Price: $";
	cin >> newCar.price;
	
	newCar = EditInfo(newCar);
	
	system ("CLS");
	return newCar;
}

void DisplayInfo()
{
	int numCars = cars.size();
	int infoNum, foundCar;
	do
	{
		system ("CLS");
		Title();
		cout << setiosflags(ios::left) << setw(10) << "Inv Num" << setw(20) << "VIN" << setw(20) << "Make" << setw(20) << "Model" << setw(10) << "Price" << line << endl;
	
		for (int i = 0; i < numCars; i++)
		{
			cout << setiosflags(ios::left) << setw(10) << cars[i].inventoryNum << setw(20) << cars[i].VIN << setw(20) << cars[i].make << setw(20) << cars[i].model << setw(10) << setw(1) << "$" << setw(9) << std::fixed << setprecision(2) << cars[i].price << endl;
		}
		
		cout << line << endl << "To view more detailed records, enter the Inventory Number.\nTo return to menu, enter '0'.\n";
		do
		{
			cout << "Selection (1000-9999 OR 0): ";
			cin >> infoNum;
			if (infoNum != 0)
			{
				foundCar = Search(infoNum);
				if (foundCar == -1 )
				{
					cout << "There is no car with the inventory number " << infoNum << ".\n";
					infoNum = 1;
				}
			}
		} while ((infoNum < 1000 || infoNum > 9999) && infoNum != 0);
		
		if (infoNum != 0)
		{
			cars[foundCar] = EditInfo(cars[foundCar]);
			DeleteVehicle[foundCar];
		}
		
	} while (infoNum != 0);
	system("CLS");
}

void UserSearch()
{
	int searchQuery, searchResult;
	DealerInfo foundData;
	system("CLS");
	Title();
	cout << "Please enter the inventory number of the vehicle you wish to find.";
	do
	{
		cout << "\nEnter Number to Search (1000-9999): ";
		cin >> searchQuery;
	} while (searchQuery < 1000 || searchQuery > 9999);
	
	searchResult = Search(searchQuery);
	
	if (searchResult < 0)
	{
		cout << "There is no vehicle with the inventory number " << searchQuery << ".\n";
		system ("Pause");
		system ("CLS");
	}
	else
	{
		cout << "A result has been found.\n";
		system ("PAUSE");
		foundData = EditInfo(cars[searchResult]);
		cars[searchResult] = foundData;
		DeleteVehicle(searchResult);
	}
}

void Output()
{
	ofstream output;
	output.open(FILE_OUT, ios::out|ios::binary);
	for (int i = 0; i < cars.size(); i ++)
	{
		output.write((char *) &cars[i], sizeof(DealerInfo));
	}
	output.close();
}

int main()
{
    //Variable Declarations:
    char userChoice;
	//Function Body
	Input();
	do
	{
		Title();
		Welcome();
		userChoice = Menu();
		
		switch (userChoice)
		{
			case '1': 	cars.push_back(NewEntry());
						break;
			case '2': 	DisplayInfo();
						break;
			case '3':	UserSearch();
						break;
			case '4':	DeleteVehicle(-1);
						break;			
		}
		Sort();
		Output(); //Output each time they do anything to ensure that accidental exits won't corrupt data.
	} while (userChoice != '5');
	
	Output();
	cout << "Your data has been output to " << FILE_OUT << ".\n";
	cout << "You may continue next time you use this program.\n";
    system("PAUSE");
    return 0;
}
//end function main

