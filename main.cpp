#include <iostream>
#include <fstream>
#include "ScoreManager.h"

using namespace std;
/***
* 
* Crear un archivo “MyScores.dat” y guardar una estructura Score.
* Posteriormente, leer el archivo e imprimir su contenido por consola.
* La estructura Score tiene un nombre y un puntaje como miembros.
* 
*/

int main()
{

	fstream myFile;

	ScoreManager* scoreManager = new ScoreManager();

	scoreManager->loadScore();

	scoreManager->addScore("Luciano", 1500);
	scoreManager->addScore("Lara",400 );
	scoreManager->addScore( "Fran",3500 );
	scoreManager->addScore("Leo",2000 );

	scoreManager->showScores();


	scoreManager->saveScore();
	/*myFile.open("MyScore.dat", ios::out | ios::binary);
	if (myFile.is_open())
	{
		myFile.write((char*)&s, sizeof(Score));
		myFile.close();
	}*/
	/*Score readScore;
	myFile.open("MyScore.dat", ios::in | ios::binary);
	if (myFile.is_open())
	{
		myFile.read((char*)&readScore, sizeof(Score));
		readScore.print();
		myFile.close();
	}*/
	//Ejercicio
	/*
	const string nombre = "Luciano Andres";
	const string apellido = "Diaz Berberich";
	ofstream myFile;
	myFile.open("MiNombreCompleto.txt");
	myFile<<"Nombre: " << nombre << " " <<endl << "Apellido: " << apellido << endl;
	myFile.close();

	ifstream inputFile;
	inputFile.open("MiNombreCompleto.txt");
	if (!inputFile.is_open()) return -1;
	string line;
	while (getline(inputFile, line))
	{
		cout << line << endl;
	}

	inputFile.close();*/

	//ejemplo profe
	/*ofstream myFile;
	myFile.open("miarchivo.txt");
	myFile << "Hola mundo!" << endl;
	myFile.close();

	ifstream inputFile;
	inputFile.open("miarchivo.txt");
	if (!inputFile.is_open()) return -1;
	string line;
	while (getline(inputFile, line))
	{
		cout << line << endl;
	}

	inputFile.close();*/

	delete scoreManager;
	return 0;
};