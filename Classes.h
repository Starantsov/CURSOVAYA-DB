#pragma once
#include <ostream>
#include <string>
#include <list>
#include "Funcs.h"
#include <algorithm>
#include <fstream>

using namespace std;

struct DetailInfo {
	static const string CarModels[6];
	static const string Part[3];
};
enum WhichFile {
	DataBaseFile,
	AnyFile
};
enum Fields{
	Name,
	GoWith,
	MoreInfo,
	Cost,
	Quantity,
	Error
};

enum FileSaveMethod {
	app,
	out,
	appCustomDir,
	outCustomDir
};

class Detail
{
protected:
	string Name;
	string GoWith;
	string MoreInfo;

public:
	Detail()
	{
		Name = "";
		GoWith = "";
		MoreInfo = "";		
	}

	Detail(string name, string goWith, string moreInfo)
	{
		Name = name;
		GoWith = goWith;
		MoreInfo = moreInfo;		
	}
	string GetName() { return Name; };

};

class DetailForSale : public Detail {
private:
	double Cost;
	int Quantity;

public: 
	DetailForSale() {
		Detail::Detail();
		Cost = 0;
		Quantity = 0;
	}
	DetailForSale(double cost)
	{
		Detail::Detail();
		Cost = cost;
		Quantity = 0;
	}
	DetailForSale(string name, string goWith, string moreInfo, double cost) : Detail(name, goWith, moreInfo)
	{
		Cost = cost;
		Quantity = 0;		
	}
	DetailForSale(string name, string goWith, string moreInfo, double cost, int quantity) : Detail(name, goWith, moreInfo)
	{
		Cost = cost;
		Quantity = quantity;
	}
	double getCost() { return Cost; }
	int getQuantity() { return Quantity; }
	void SetFullInfo(string name, string goWith, string moreInfo, double cost)
	{
		Name = name;
		GoWith = goWith;
		MoreInfo = moreInfo;
		Cost = cost;
		Quantity = 0;
	}
	void SeeFullInfo()
	{
		cout << "Detail name: " << this->Name;		
		cout << "\nDetail suitable for car brand: " << this->GoWith;	
		if (this->MoreInfo != "") cout << "\nMore information: " << this->MoreInfo;
		else cout << "\nMore information: none";
		cout << "\nValue: " << this->Cost;
		cout << "\nAvailable: " << this->Quantity;
	}
	void SaveFullInfo(ofstream& myfile)
	{
		
		myfile << "Detail name: " << this->Name;
		myfile << "\nDetail suitable for car brand: " << this->GoWith;
		if (this->MoreInfo != "") myfile << "\nMore information: " << this->MoreInfo;
		else myfile << "\nMore information: none";
		myfile << "\nValue: " << this->Cost;
		myfile << "\nAvailable: " << this->Quantity<<"\n";
		myfile << "---------------------------------------------\n";
			

	}
	void SaveFullInfoToDB(ofstream& myfile)
	{

		myfile << this->Name << endl;
		myfile << this->GoWith << endl;
		myfile << this->MoreInfo << endl;
		myfile << this->Cost << endl;
		myfile << this->Quantity << endl;
		myfile << "---------------------------------------------\n";
		

	}

};

class Storage{
private:
	list<DetailForSale> Details;

public:	
	Storage() {	}

	bool AllEmpty()
	{		
		return Details.empty();
	}
	bool GotOne()
	{
		if (Details.size() == 1)return true;
		else return false;
	}
	void ViewDetailsInfo()//Вывод всех деталей на экран+
	{
		for (auto D : Details)
		{
			D.SeeFullInfo();
			cout << "\n\n";
		}
	}
	void Clear()
	{
		Details.clear();
	}

	list<DetailForSale> FindCertainDetailByName()//Поиск по имени детали+
	{
		string name;
		cout << "Input name to find: ";
		cin >> name;
		
		list<DetailForSale> FoundDetails;
		
		for (auto &D : Details)
		{
			if (D.GetName() == name) 
			{ 
				FoundDetails.push_back(D);
			}	
		}
		
		return FoundDetails;
	}
	
	void AddNewDetail(DetailForSale temp)//Добавление новой детали+
	{			
		Details.push_back(temp);		
	}
	
	void Remove()//Удаление нужной детали
	{
		string name,input;

		if (Details.size())
		{
			bool success = false;
			cout << "Input name to delete: ";
			cin >> name;
			system("cls");
			for (auto it = Details.begin(); it != Details.end(); ++it)
			{
				if (it->GetName() == name) {
					success = true;
					cout << "Detail '" << name << "' is found.\n\n";
					it->SeeFullInfo();
					cout << "\n\nDelete it? '(y/n)'\n";
					cin >> input;
					if (input == "y")
					{
						Details.erase(it);
						system("cls");
						cout << "Detail was deleted...\n";
						system("pause");
						return;
					}
					else if (input == "n")
					{
						return;
					}
				}
				
			}
			if (!success)
			{
				cout << "Nothing found...\n";
				system("pause");
				system("cls");
			}
		}
		else {
			cout << "You don't have any details to remove...\n";
			system("pause");
			system("cls");
		}
	}

	
	void Sort(Fields field)//Сортировка списка+
	{
			
		switch (field)
		{
			case Fields::Name: {
				Details.sort([](Detail & left, Detail & right) {
					return (left.GetName() < right.GetName());
				});
				break;
			}

			case Fields::Cost: {
				Details.sort([](DetailForSale & left, DetailForSale & rigth) {
					return (left.getCost() < rigth.getCost());
				});
				break;
			}
			case Fields::Quantity: {
				Details.sort([](DetailForSale & left, DetailForSale & rigth) {
					return (left.getQuantity() < rigth.getQuantity());
				});
				break;
			}
		}
	}

	void SaveToFileCurrent(ofstream& file, WhichFile f)//Сохранение в фаил
	{		
		if (!file.is_open()) {
			cout << "That file can't be opened\n";
		}
		else
		{
			for (auto D : Details)
			{
				switch (f) 
				{
				case WhichFile::AnyFile:
					D.SaveFullInfo(file);
					break;
				case WhichFile::DataBaseFile:
					D.SaveFullInfoToDB(file);
					break;
				}
			}
			file.close();
		}
		
	}
	
};

