#include "ScoreManager.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

ScoreManager::ScoreManager() : _fileName("scores.bin")
{

	if (!existFile())
	{
		createFile();
	}
	
}

ScoreManager::ScoreManager(std::string newName) : _fileName(newName)
{
	if (!existFile())
	{
		createFile();
	}
}

ScoreManager::~ScoreManager()
{
	_scores.clear();
}

const std::vector<ScoreManager::Score> ScoreManager::getScores() const
{
	return _scores;
}

void ScoreManager::addScore(const char name[256], const int score)
{
	Score newScore;
	strcpy_s(newScore._name, name);
	newScore._score = score;
	if (!std::count(_scores.begin(), _scores.end(), newScore))
	{
		_scores.emplace_back(newScore);
	}
	
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
			oFile.write((char*)&s, sizeof(Score));
		}
		oFile.close();
	}
	

}

void ScoreManager::loadScore()
{
	std::ifstream iFile(_fileName, std::ios::in | std::ios::binary | std::ios::beg);

	if (!iFile)
	{
		std::cout << "Cannot open file!" << std::endl;
	}

	Score rScore;
	
	while (!iFile.eof())
	{
		iFile.read(reinterpret_cast<char*>(&rScore), sizeof(Score));
		
		if (rScore._name != "" && rScore._score > 0)
		{
			_scores.emplace_back(rScore);
		}
	}
	

	iFile.close();
	
}

void ScoreManager::createFile()
{
	std::ofstream file(_fileName);
}

void ScoreManager::sortScore()
{
	std::sort(_scores.begin(), _scores.end(), [](Score& a, Score& b) {return a._score > b._score; });
}
