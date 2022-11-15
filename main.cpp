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
	ScoreManager* scoreManager = new ScoreManager("sarasa.bin");

	scoreManager->loadScore();

	auto a = scoreManager->getScores();

	scoreManager->addScore("Luciano", 1500);
	scoreManager->addScore("Lara",400 );
	scoreManager->addScore("Fran",3500 );
	scoreManager->addScore("Leo",2000 );
	scoreManager->addScore("agus", 800);
	scoreManager->addScore("agus", 800);// No hace el push por ser dato repetido
	scoreManager->addScore("Lara", 700);// esta permitido que hayan personas con el mismo nombre y distinto score

	scoreManager->showScores();


	scoreManager->saveScore();

	delete scoreManager;
	return 0;
};