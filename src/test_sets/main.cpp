// main.cpp
// defines application entry point

#include "pch.hh"
#include "sets.hh"
using namespace roulette;

#include <array>
#include <vector>
#include <iostream>
using namespace std;

int main()
{

	for (auto iter : *EuropeanWheel)
	{
		cout << iter << " ";
	}

	cout << endl;

	for (auto iter : *Red)
	{
		cout << iter << " ";
	}

	cin.get();
	return 0;
}
