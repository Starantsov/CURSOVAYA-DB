#include <iostream>
#include <string>
#include <Windows.h>
#include "Funcs.h"
#include "cstdlib"
#include "Classes.h"
#include <algorithm>
#include <fstream>

string const DetailInfo::CarModels[6] = { "Bmw","Audi","Mersedes","Mazda", "Ford","Subaru"};
string const DetailInfo::Part[3] = { "Engine","Suspention","Brake system" };




using namespace std;



int main() {
	SetConsoleCP(1251);		  // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251

	short Stats = -1;
	setlocale(NULL, "RUS");
	
	Storage storage;
	
	LoadFromDBFile(storage);

	string input;
	while (true) 
	{		
		bool N = true;
		system("cls");

		if (++Stats == 0) Commands();

		Menu();
		cin >> input;

		//getline(cin,input);
	

		transform(input.begin(), input.end(), input.begin(), ::tolower);

		system("cls");

		if (input == "qq")
		{
			/*system("cls");
			cout << "See you soon.\n\n";
			system("pause");
			*/
			break;
		}
		//добавить синхронизацию с фаилом после
		else if (input == "add")
		{
			storage.AddNewDetail(FillTemp());
			RefreshDBFile(storage);
		}
		//добавить синхронизацию с фаилом после
		else if (input == "sort")
		{
			storage.Sort(Sort(storage));
			RefreshDBFile(storage);
		}
		else if (input == "ls")
		{
			if (storage.AllEmpty())
			{
				system("cls");
				cout << "Database is empty..\n";
				system("pause");
			}
			else {
				system("cls");
				storage.ViewDetailsInfo();
				system("pause");
			}
		}
		else if (input == "find")
		{
			if (!storage.AllEmpty())
			{
			FindElementMenu(storage);
			}
			else
			{
				cout << "Database is empty...\n\n";
				system("pause");
			}
		}
		//добавить синхронизацию с фаилом после
		else if (input == "rm")
		{
			system("cls");
			storage.Remove();
			RefreshDBFile(storage);
			continue;
		}
		else if (input == "author")
		{
			Author();
		}
		
		//добавить синхронизацию с фаилом после
		else if (input == "clear")
		{
			string sure;
			cout << "Are you sure you want to delete all data?\nYou won't be able to reach it after that...\nInput 'Y' if you sure\n";
			cin >> sure;
			if (sure == "y" || sure == "Y")
			{
				storage.Clear();
				RefreshDBFile(storage);
				continue;
			}
			else
			{
				continue;
			}
			
		}
		else if (input.find("file_save'") == 0 || input.find("file_save\"") == 0)
		{
			input = input.substr(10, input.length() - 10);

			SaveToFile(storage, FileSaveMethod::outCustomDir, input);
		}
		else if (input.find("file_add'") == 0 || input.find("file_add\"") == 0)
		{
			input = input.substr(9, (input.length() - 9));

			SaveToFile(storage, FileSaveMethod::appCustomDir, input);
		}
		else if (input == "file_save")
		{
			if (storage.AllEmpty())
			{
				system("cls");
				cout << "Database is empty..\n";
				system("pause");
			}
			else 
			{
				system("cls");
				SaveToFile(storage, FileSaveMethod::out,"");
				system("pause");
			}
			
		}
		else if (input == "file_add")
		{
			if (storage.AllEmpty())
			{
				system("cls");
				cout << "Database is empty..\n";
				system("pause");
			}
			else 
			{
				system("cls");
				SaveToFile(storage, FileSaveMethod::app,"");
				system("pause");
			}

		}
		else if (input == "info")
		{
			Commands();
			system("pause");
		}
		else 
		{			
				cout << "Error!\nInput [info] to the console next time."; system("pause");
		}
		
	}
	return 1;
}