#pragma once
#include <iostream>
#include <string>
#include "Classes.h"
#include <fstream>

void PauseConsole()
{
	cout << "\nPress any key to continue...";
	cin.ignore(); // Wait for any key
	cin.get();

}
void ChooseFrom() {
	cout << "Choose car brand that your detail suitable for:\n";
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << ". " << DetailInfo::CarModels[i] << endl;
	}
}
void Menu()
{

	cout << "Input [info] to see all commands\n";
	cout << "$ ";
}
void Commands()
{
	cout << "Input one of those commands\n";
	cout << "--------------------------------\n";
	cout << "[add]    - add new detail\n";
	cout << "[ls]     - list all details\n";
	cout << "[rm]     - remove certain detail\n";
	cout << "[clear]  - CAREFUL!!! - clears all database\n";
	cout << "[sort]   - sort all elements list\n";
	cout << "[find]   - find certain detail\n";	
	cout << "[file_save'exaple.txt'] - saves current database to file you want, after cleaning it\n"; 
	cout << "[file_add'exaple.txt'] - saves current database to file you want\n";
	cout << "[file_save] - saves current database to the file 'text.txt', after cleaning it\n";
	cout << "[file_add] - adds current database to the file 'text.txt'\n";
	cout << "[author] - author's name\n";
	cout << "[qq]  - quit program\n";	
	cout << "--------------------------------\n\n\n";
}

DetailForSale FillTemp()//Заполнение и возврат заполенного
{
	string name; double cost;
	string choise, gowith, description;
	int Choise = 0;
	DetailForSale TEMP;

	system("cls");

	cout << "Enter the detail name\n";
	cin >> name;
	system("cls");

	ChooseFrom();

	while (true)
	{
		cin >> choise;
		if (isdigit(choise[0]))
		{
			Choise = stoi(choise);
			if (Choise <= 3 && Choise > 0)
			{
				break;
			}
			else {
				system("cls");
				cout << "Error!Choose existing brand...\n";
				system("pause");
				system("cls");
				ChooseFrom();

			}
		}
		else
		{
			system("cls");
			cout << "Error!Choose existing brand...\n";
			system("pause");
			system("cls");
			ChooseFrom();

		}

	}
	

	switch (Choise)
	{
	case 1:
		gowith = DetailInfo::CarModels[0];
		break;
	case 2:
		gowith = DetailInfo::CarModels[1];
		break;
	case 3:
		gowith = DetailInfo::CarModels[2];
		break;

	}


	system("cls");

	cout << "More info:\n";
	getchar();
	getline(cin, description);
	system("cls");

	
	
	while (true)
	{
		string Cost;
		cout << "Cost: ";

		cin >> Cost;

		if (isdigit(Cost[0])) {
			cost = stoi(Cost);
			if(cost > 0) break;
		}
		else {

			system("cls");
			cout << "Enter the number!!!\n";
			system("pause");
			system("cls");
			cout << "Value: ";
		}
	}

	system("cls");
	
	try
	{
		TEMP.SetFullInfo(name, gowith, description, cost);
		cout << "Succesfully appended your detail to database.\n\n";
		TEMP.SeeFullInfo();
		cout << endl;
		PauseConsole();
		return TEMP;
	}
	catch (exception)
	{
		cout << "Some error, restart filling..\n";
		PauseConsole();
		FillTemp();
	}	
}
void FindElementMenu(Storage storage)
{
	list<DetailForSale> temp;
	system("cls");
	temp = storage.FindCertainDetailByName();
	system("cls");

	if (temp.size() == 0)
	{
		cout << "Specific detail has't been found!!!\n";
	}
	else
	{
		int count = 0;
		cout << "Found " << temp.size() << " details with that name\n\n";
		for (auto T : temp)
		{
			count++;
			cout << "№ - " << count<< " \n";
			T.SeeFullInfo();
			cout << "\n\n";
		}
	}
	PauseConsole();
	cin.get();
}
Fields Sort(Storage storage)
{
	if (storage.AllEmpty() || storage.GotOne())
	{
		cout << "You don't have enough sort.Try to add for starters...\n";
		system("pause");
		return Fields::Error;
	}else
	{
		int Input;
		cout << "Select sorting method:\n";
		cout << " 1.Sort by name.\n";
		cout << " 2.Sort by cost.\n";
		cout << " 3.Sort by quantity.\n";


		while (true)
		{
			string input;
			cin >> input;

			if (isdigit(input[0])) {
				Input = stoi(input);

				if (Input > 0 && Input < 4) break;
				else {
					system("cls");
					cout << "Input number from 1 to 3...\n";
					system("pause");
					system("cls");

					cout << "Select sorting method:\n";
					cout << " 1.Sort by name.\n";
					cout << " 2.Sort by cost.\n";
					cout << " 3.Sort by quantity.\n";
				}
			}
			else {
				system("cls");
				cout << "Enter the number!!!\n";
				system("pause");
				system("cls");
				cout << "Select sorting method:\n";
				cout << " 1.Sort by name.\n";
				cout << " 2.Sort by cost.\n";
				cout << " 3.Sort by quantity.\n";
			}
		}

		switch (Input)
		{
		case 1:
			return Fields::Name;
			break;
		case 2:
			return Fields::Cost;
			break;
		case 3:
			return Fields::Quantity;
			break;
		}

	}

	
}
void Author()
{
	system("cls");
	cout << "\n \n \n \n \n \n \n \n \n \n ";
	cout << "\t \t \t---------------------------------------------------------------------" << endl;
	cout << "\t \t \t The main purpose of that program is processing data base " << endl;
	cout << "\t \t \t----------That purpose was realized by Nazar Starantsov--------------" << endl;
	cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
	PauseConsole();
	system("cls");
}

void RefreshDBFile(Storage& storage)//Запись всего в фаил БД
{
	ofstream file;
	
	file.open("storage.bd", ios::out);
	

	if (!file.is_open())
	{
		cout << "Произошла ошибка при загрузке базы данных.\nДля корректной работы проверьте существует ли фаил 'storage.bd'...\n";
		cout << "Если фаил отсутствует, создайте его и поместите в папку с программой\n";
		system("pause");
	}
	else
	{

		storage.SaveToFileCurrent(file, WhichFile::DataBaseFile);
		if (file.is_open())
		{
			file.close();
		}
		

	}
	
}

void LoadFromDBFile(Storage& storage) //Загрузка всего в список из фаила БД
{
	bool space = false;
		ifstream file;
		file.open("storage.bd");

		string name, cost, quantity, gowith, moreinfo;
		double Cost;
		int Quantity;


		if (!file.is_open())
		{			
			cout << "Произошла ошибка при загрузке базы данных.\nДля корректной работы проверьте существует ли фаил 'storage.bd'...\n";
			cout << "Если фаил отсутствует, создайте его и поместите в папку с программой\n";
			system("pause");
		}
		else
		{
			string CheckSpace;
			
			while (!file.eof()) 
			{						
					getline(file, name); if (name == "") { space = true; }
					getline(file, gowith);
					getline(file, moreinfo);
					getline(file, cost);
					getline(file, quantity);
				    getline(file, CheckSpace);
				try 
				{
					Cost = stod(cost);
					Quantity = stoi(quantity);

					if (!space)
					{
						DetailForSale temp(name, gowith, moreinfo, Cost, Quantity);
						storage.AddNewDetail(temp);
					}
				
				}
				catch (invalid_argument) 
				{
					cout << "Format exception found in file.";
					cout << "(Value should be double, Cost integer)\n\n\n";
					system("pause");
				}

			}
			cout << "Success...\n";
		}
}

void SaveToFile(Storage storage, FileSaveMethod m, string path) {

	ofstream file;
	string PATH = "text.txt";
	switch (m) {

	case FileSaveMethod::app:
		file.open(PATH,ios::app);
		break;

	case FileSaveMethod::out:
		file.open(PATH,ios::out);
		break;		

	case FileSaveMethod::appCustomDir:
		PATH = path.substr(0, path.length()-1);
		file.open(PATH, ios::app);
		break;

	case FileSaveMethod::outCustomDir:
		PATH = path.substr(0,path.length()-1);
		file.open(PATH, ios::out);
		break;
	}
	

	if (!file.is_open()) {
		cout << "The '" <<PATH<< "' file can't be opened\n";
	}
	else {
		storage.SaveToFileCurrent(file, WhichFile::AnyFile);
		if (file.is_open())
		{
			file.close();
		}
		cout << "Success...File saved to '"<<PATH <<"'\n";
	}
	
	
}
