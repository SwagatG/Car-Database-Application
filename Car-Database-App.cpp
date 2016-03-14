//*****************************************************************************************
//  Program Filename	: Binary Read/Write Lab
//  Version				: 1.0
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
	char isCorrect, editChoice;
	system ("CLS");
	Title();
	cout << "New Entry:\n";
	do
	{
		cout << "\nEnter Inventory Number (1000 - 9999): ";
		cin >> newCar.inventoryNum;
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
	
	do
	{
		system ("CLS");
		Title();
		cout << "Inventory Number: " << newCar.inventoryNum << endl;
		cout << "Auto VIN: " << newCar.VIN << endl;
		cout << "Make: " << newCar.make << endl;
		cout << "Model: " << newCar.model << endl;
		cout << "Exterior Colour: " << newCar.exColour << endl;
		cout << "Interior Colour: " << newCar.inColour << endl;
		cout << "Transmission Type: " << newCar.transmission << endl;
		cout << "Enter Retail Price: $" << newCar.price << endl << endl;
		cout << "\nWould you like to edit this information?";
		do
		{
			cout << "\nEnter 'y' or 'n': ";
			cin >> isCorrect;
		} while (tolower(isCorrect) != 'n' && tolower(isCorrect) != 'y');
		
		if (tolower(isCorrect) == 'y')
		{
			cout << "Which Item Would you like to edit? Enter...\n\t1 - Inventory Number\n\t2 - VIN\n\t3 - Make\n\t4 - Model\n\t5 - Exterior Colour\n\t6 - Interior Colour\n\t7 - Transmission Type\n\t8 - Retail Price\n";
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
								cin >> newCar.inventoryNum;
							} while (newCar.inventoryNum < 1000 || newCar.inventoryNum > 9999);
							break;
				case '2':	cout << "Enter Auto VIN: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.VIN, 20, '\n');
							break;
				case '3':	cout << "Enter Make: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.make, 20, '\n');
							break;
				case '4':	cout << "Enter model: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.model, 20, '\n');
							break;
				case '5':	cout << "Enter Exterior Colour: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.exColour, 20, '\n');
							break;
				case '6':	cout << "Enter Interior Colour: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.inColour, 20, '\n');
							break;
				case '7':	cout << "Enter Transmission Type: ";
							cin.ignore(100, '\n');
							cin.getline(newCar.transmission, 20, '\n');
							break;
				case '8':	cout << "Enter price: $";
							cin >> newCar.price;
							break;
			}
		}
	}while (tolower(isCorrect) != 'n');
	system ("CLS");
	return newCar;
}

void DisplayInfo()
{
	int numCars = cars.size();
	int infoNum, findCount = 0;
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
			cout << "Selection: ";
			cin >> infoNum;
		} while (infoNum < 1000 || infoNum > 9999 && infoNum != 0);
		
		if (selection != 0)
		{
			for (int = 0; i < numCars; i++)
			{
				if (cars[i].inventoryNum == selection)
				{
					cout << endl;
					cout << "Inventory Number: " << newCar.inventoryNum << endl;
					cout << "Auto VIN: " << newCar.VIN << endl;
					cout << "Make: " << newCar.make << endl;
					cout << "Model: " << newCar.model << endl;
					cout << "Exterior Colour: " << newCar.exColour << endl;
					cout << "Interior Colour: " << newCar.inColour << endl;
					cout << "Transmission Type: " << newCar.transmission << endl;
					cout << "Enter Retail Price: $" << newCar.price << endl << endl;
					cout << "\nWould you like to edit this information?";
					do
					{
						cout << "\nEnter 'y' or 'n': ";
						cin >> isCorrect;
					} while (tolower(isCorrect) != 'n' && tolower(isCorrect) != 'y');
		
					if (tolower(isCorrect) == 'y')
					{
						cout << "Which Item Would you like to edit? Enter...\n\t1 - Inventory Number\n\t2 - VIN\n\t3 - Make\n\t4 - Model\n\t5 - Exterior Colour\n\t6 - Interior Colour\n\t7 - Transmission Type\n\t8 - Retail Price\n";
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
											cin >> newCar.inventoryNum;
										} while (newCar.inventoryNum < 1000 || newCar.inventoryNum > 9999);
										break;
							case '2':	cout << "Enter Auto VIN: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.VIN, 20, '\n');
										break;
							case '3':	cout << "Enter Make: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.make, 20, '\n');
										break;
							case '4':	cout << "Enter model: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.model, 20, '\n');
										break;
							case '5':	cout << "Enter Exterior Colour: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.exColour, 20, '\n');
										break;
							case '6':	cout << "Enter Interior Colour: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.inColour, 20, '\n');
										break;	
							case '7':	cout << "Enter Transmission Type: ";
										cin.ignore(100, '\n');
										cin.getline(newCar.transmission, 20, '\n');
										break;
							case '8':	cout << "Enter price: $";
										cin >> newCar.price;
							break;
			}
		}
	}while (tolower(isCorrect) != 'n');
					break;
				}
			}
		}
		
	} while (infoNum != 0);
	
}

int main()
{
    //Variable Declarations:
    char userChoice;
    ifstream input;
    ofstream output;
	//Function Body
	output.open(FILE_OUT, ios::out|ios::binary);
	output.write((char *) &cars, sizeof(DealerInfo) );
	do
	{
		Title();
		Welcome();
		userChoice = Menu();
		
		switch (userChoice)
		{
			case '1': 	cars.push_back(NewEntry());
						Sort();
						break;
			case '2': 	DisplayInfo();
						break;
			
		}
	} while (userChoice != '4');
	
    system("PAUSE");
    return 0;
}
//end function main

