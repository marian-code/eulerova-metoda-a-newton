// eulerova metoda a newton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

//napisane vo Visual Studio 2015 - (kompilátor: Visual C++ 14.0)

const int n = 50;

double f(double x_n, double h, int i, double riesenie[][n+1])
{
	return x_n * (3.0 * h - 1.0) + h*cos(x_n) + riesenie[1][i] + h*riesenie[0][i + 1];
}

double df(double x_n, double h, int i, double riesenie[][n + 1])//derivacia je spocitana analyticky
{
	return (3.0 * h - 1.0) - h*sin(x_n);
}

double newton(int i, double h, double riesenie[][n + 1])//Newton - Raphson method
{
	double x_n_plus, x_n=0;
	int k=0;

	//pociatocny odhad riesenia je hodnota v predchadajucom kroku
	x_n_plus = riesenie[1][i];

	while (abs(x_n_plus - x_n) > 5E-15)
	{
		x_n = x_n_plus;
		x_n_plus = x_n - f(x_n, h, i, riesenie) / df(x_n, h, i, riesenie);
		cout << x_n << endl;
		if (k > 1000)
		{
			cerr << "Newton prevdepodobne nekonverguje" << endl;
		}
		k++;
	}

	riesenie[1][i + 1] = x_n_plus;

	return 0;
}

int main()
{
	int i, j;
	double h = 0.01;
	double riesenie[2][n + 1] = { 0 };

	for (i = 0; i < n + 1; i++)
	{
		riesenie[0][i] = i*h+3;
	}

	//pociatocna podmienka!!!!!!!!!!!!
	riesenie[1][0] = 2.0;

	//euler implicitny
	for (i = 0; i < n; i++)
	{
		newton(i, h, riesenie);
	}
	
	ofstream outfile1; //zápis do suboru csv na odovzdanie ulohy
	outfile1.open("priloha2.csv");
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			if (j<n) outfile1 << fixed << setprecision(13) << riesenie[i][j] << ",";
			else outfile1 << fixed << setprecision(13) << riesenie[i][j];
		}
		outfile1 << "\n";
	}
	outfile1.close();

	ofstream outfile2; //zápis do suboru txt - prehladny vypis na citanie
	outfile2.open("rozdelenie.txt");
	for (i = 0; i < n + 1; i++)
	{
		for (j = 0; j < 2; j++)
		{
			outfile2 << fixed << setprecision(5) << riesenie[j][i] << "\t";
		}
		outfile2 << endl;
	}
	outfile2.close();

	//system("notepad.exe rozdelenie.dat");

	//system("PAUSE");

    return 0;
}

