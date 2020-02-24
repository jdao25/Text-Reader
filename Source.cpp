#include <iostream>
// #include "stdafx.h"
#include <sapi.h>
#include <fstream>
#include <string>
#include <conio.h>


bool checkFile()
{
	std::ifstream infile;
	infile.open("read.txt");

	if (!infile)
	{
		infile.close();

		std::ofstream outfile;
		outfile.open("read.txt");
		outfile.close();
	}
	else
		infile.close();
	
	return true;
}


int wordCount()
{
	std::ifstream infile;
	infile.open("read.txt");

	int count = 0;
	std::string word;
	
	while (infile >> word)
		count++;

	infile.close();

	return count;
}


std::wstring string_to_wstring_converter(const std::string& line)
{
	std::wstring wLine;
	wLine.assign(line.begin(), line.end());

	return wLine;
}

std::wstring add_gender(const std::wstring& line)
{
	return L"<voice required = 'Gender=female'>" + line;
	 
}


int readFile()
{
	ISpVoice* pVoice = nullptr;

	if (FAILED(::CoInitialize(nullptr)))
		return 0;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice,
		(void **)&pVoice);

	if (SUCCEEDED(hr))
	{
		if (checkFile())
		{
			//pVoice->SetRate(1);
			if (wordCount() <= 0)
				pVoice->Speak(L"<voice required = 'Gender=female'>The file is currently empty.", 0, nullptr);
			else
			{
				std::ifstream infile;
				infile.open("read.txt");

				std::string word;
				pVoice->SetRate(-1);
				while (std::getline(infile, word))
					pVoice->Speak(add_gender((string_to_wstring_converter(word))).c_str(), SPF_ASYNC, nullptr);

				infile.close();
			}
		}
	}

	::CoUninitialize();
	return 1;
}


int about()
{
	ISpVoice* pVoice = nullptr;

	if (FAILED(::CoInitialize(nullptr)))
		return 0;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL, IID_ISpVoice,
		(void **)&pVoice);

	if (SUCCEEDED(hr))
	{
		std::string text =
			" <voice required = 'Gender=female'>Developer: <pitch middle = '-10'/> Johnny Dow."
			" <pitch middle = '10'/>Purpose:  This application will read words from a text file for you.";
		std::wstring wtext(text.begin(), text.end());
		pVoice->SetRate(1);
		pVoice->Speak(wtext.c_str(), SPF_IS_XML, nullptr);
	}

	::CoUninitialize();
	return 1;
}


bool checkIfExist()
{
	bool isExist = false;

	std::ifstream infile("read.txt");

	if (infile)
		isExist = true;

	infile.close();

	return isExist;
}


int main(int argc, char* argv[])
{
	bool isFinished = false;
	while (!isFinished)
	{
		system("cls");

		std::cout
			<< " What would you like to do:" << std::endl
			<< " 1.  Read Text File" << std::endl
			<< " 2.  Add Content to Text File" << std::endl
			<< " 3.  Remove Text File" << std::endl
			<< " 4.  About" << std::endl
			<< " 5.  exit" << std::endl
			<< std::endl
			<< " " << std::endl;

		char key;
		key = _getch();

		if (key != '\0')
		{
			switch (int(key))
			{
			case 27:
			case 53:
				isFinished = true;
				system("cls");
				break;

			case 49:
				system("cls");
				readFile();
				break;

			case 50:
				
				if (checkFile())
					system("notepad read.txt");
				break;

			case 51:
				if (checkIfExist())
				{
					remove("read.txt");
					std::cout << " File \"read.txt\" has been removed.\n ";
					Sleep(1000);
				}
				else
				{
					std::cerr << " There are no file named \"read.txt\"." << std::endl;
					Sleep(1000);
				}

				break;

			case 52:
				std::cout
					<< " Developer:  Johnny Dao" << std::endl
					<< " Purpose:  This program will physically read to you." << std::endl
					<< "           This is an example of a Text-to-speech program." << std::endl;
				
				about();
				break;

			default:
				std::cerr << " Option does not exist." << std::endl;
				std::cout << " ";
				Sleep(1000);
			}
		}
	}
}