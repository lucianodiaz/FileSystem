#include "ScoreManager.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

ScoreManager::ScoreManager() : _fileName("scores.bin")
{
}

ScoreManager::~ScoreManager()
{
	_scores.clear();
}

void ScoreManager::addScore(const char name[256], const int score)
{
	Score newScore;
	strcpy_s(newScore._name,name);
	newScore._score = score;
	_scores.emplace_back(newScore);
	sortScore();
}

void ScoreManager::modifyScoreByIndex(int index, int newScore)
{
	_scores.at(index - 1)._score = newScore;
	sortScore();
}

void ScoreManager::removeScore(int index)
{
	_scores.erase(_scores.begin() + index-1);
}

void ScoreManager::showScores()
{
	int i = 1;
	for (auto&& s : _scores)
	{
		std::cout << i << ". " << s._name << " " << s._score << std::endl;
		i++;
	}
}

void ScoreManager::saveScore()
{
	std::ofstream oFile(_fileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (oFile.fail())
	{
		std::cout << "Cannot open file!" << std::endl;
		return;
	}
	if (oFile.is_open())
	{
		for (auto&& s : _scores)
		{
			oFile.write((char*)&s, sizeof(_scores.size()));
		}
		oFile.close();
	}
	

}

void ScoreManager::loadScore()
{
	std::ifstream iFile(_fileName, std::ios::in | std::ios::binary | std::ios::ate);

	if (!iFile)
	{
		std::cout << "Cannot open file!" << std::endl;
	}

	////for (auto&& s : _scores)
	//{
		 iFile.read(reinterpret_cast<char*>(&_scores) , sizeof(Score));
		/*std::cout << _scores._name;
		std::cout << _scores._score;*/
	//}

	iFile.close();
}

void ScoreManager::sortScore()
{
	std::sort(_scores.begin(), _scores.end(), [](Score& a, Score& b) {return a._score > b._score; });
}
