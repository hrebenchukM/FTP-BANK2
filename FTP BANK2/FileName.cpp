#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{

	string inputCode;
	string inputData;//20240319


	cout << "Input code of money like(USD,EUR): ";
	cin >> inputCode;
	cout << "Input data like(20240319=19.03.2024): ";
	cin >> inputData;

	setlocale(0, "ru");
	//SetConsoleOutputCP(1251);
	//SetConsoleCP(1251);

	// the URL to download from 
	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
	string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode="+inputCode+"&date="+inputData+"&json"; //
	//string srcURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?valcode=USD&date=20240319&json"; // 

	// the destination file 
	string destFile = "file.txt";
	//// URLDownloadToFile returns S_OK on success 
	if (S_OK == URLDownloadToFileA(NULL, srcURL.c_str(), destFile.c_str(), 0, NULL))
	{
		cout << "Saved to " << destFile << "\n";


		
		string str;
		ifstream in("file.txt", ios::in);
		
		if (in) { 

			do {
				getline(in, str);
				//cout << str+"," << endl;

				int start, end;
				string info;
				int count = 0;
				

				if (str.find("rate") != -1) {
					start = str.find("rate") + 5; 
					end = str.find(",", start); 
					
					info=str.substr(start, end - start);;
					cout << "Kурс в грн=" << info << endl;
				}
				if (str.find("cc") != -1) {
					start = str.find("cc") + 4;
					end = str.find(",", start);
				

					info = str.substr(start, end - start);;
					cout<< "Валюта="<<info << endl;

				}
				if (str.find("exchangedate") != -1) {
					start = str.find("exchangedate") + 14;
					end = str.find(",", start);

					
					info = str.substr(start, end - start);;
					cout << "Дата=" << info<<endl;

				}





			} while (in);
			in.close();
		}
	}
	else cout << "Fail!\n";




	/*
	1. С клавиатуры вводим следующие данные:
	  дата
	  Валюта
	  Вывести актуальную информацию!
	  формат вывода - Дата: 19.03.2024г, Валюта - USD, 1$ = 38.9744 грн.

	*/


}