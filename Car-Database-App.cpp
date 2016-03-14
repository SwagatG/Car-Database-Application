//*****************************************************************************************
//  Program Filename	: Binary Read/Write Lab
//  Version				: 2.0
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
struct DealerInfo
{
	int inventoryNum;
	char VIN[18];
	char make[20];
	char model[20];
	char exColour[20];
	char inColour[20];
	char transmission[20];
	float price;
};
vector<DealerInfo> cars;

const string line = string(80, '_');

//*****************************************************************************************
// Function Name:
// Purpose: Purpose of function
// Inputs to Function: parameters
// Outputs from Function: return value
// External Inputs to Function: e.g. cin, file, etc.
// External Outputs from Function: e.g. cout, stderr, file, etc.
//*****************************************************************************************

void Input()
{
    int count = 0;
    bool isEnd;
    ifstream input;
    DealerInfo currentCar;
	input.open(FILE_IN, ios::in|ios::binary);
 
	//Check to be sure file is opened.  One way, use the fail function.
	if(!input )
	{
		cout << "Can't find input file " << FILE_IN << ".\n";
		cout << "Starting a new record.\n";
		system("Pause");
		system("CLS");
	}
	else
	{ 
 		while (!input.eof())
 		{
			input.read((char *) &currentCar, sizeof(DealerInfo));
			cars.push_back(currentCar);
		}
		cars.pop_back();
	}
	input.close();
}	

void Title()
{
	cout << "Car Dealership Inventory" << endl << line << endl;
}

void Welcome()
{
	cout << "Welcome to the Car Dealership Inventory Program." << endl << endl;
}

void Sort()
{
	DealerInfo temp;
	int max, checks;
	int arraySize = cars.size();
	for (int i = 0; i < arraySize; i++)
	{
		int checks = arraySize -1 - i;
		max = 0;
		for (int j = 0; j <= checks; j++)
		{
			if (cars[j].inventoryNum > cars[max].inventoryNum)
			{
				max = j;
			}
		}
		temp = cars[max];
		cars[max] = cars[checks];
		cars[checks] = temp;
	}
}

int Search(int InvNum)
{
	int result, isResult = 0;
	for (int i = 0; i < cars.size(); i ++)
	{
		if (cars[i].inventoryNum == InvNum)
		{
			result = i;
			isResult += 1;
			break;
		}
	}
	if (isResult > 0)
	{
		return result;
	}
	else
	{
		return -1;
	}
}

DealerInfo EditInfo(DealerInfo ChangedCar)
{
	DealerInfo OldCar = ChangedCar;
	char isCorrect, editChoice;
	int oldNum;
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
	}while (tolower(isCorrect) != 'n');
	return ChangedCar;
}

char Menu()
{
	char selection = '0';
	cout << "Menu\n\t1)Enter a New Vehicle\n\t2)Display Vehicle Inventory\n\t3)Search for Vehicle (By Inventory Number)\n\t4)Exit This Program\n";
	do
	{
		cout << "\nSelection: ";
		cin >> selection;
		if (selection !='1' && selection !='2' && selection !='3' && selection !='4')
		{
			cout << "Invalid Selection.\n";
		}
	} while (selection !='1' && selection !='2' && selection !='3' && selection !='4');
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
		}
		Sort();
	} while (userChoice != '4');
	
	Output();
	cout << "Your data has been output to " << FILE_OUT << ".\n";
	cout << "You may continue next time you use this program.\n";
    system("PAUSE");
    return 0;
}
//end function main

