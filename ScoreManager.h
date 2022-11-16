#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

template <class T = int> 
class ScoreManager
{
private:
	struct Score
	{
		T _score{};
		char _name[256]{};

		bool operator==(const Score& s) {
			return _score == s._score && (std::strcmp(_name, s._name) == 0);
		}
		bool operator!=(const Score& s) {
			return _score != s._score || (std::strcmp(_name, s._name) != 0);
		}

	};
public:
	//esta clase no deberia ser copiada
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

	ScoreManager();
	ScoreManager(std::string newName);

	~ScoreManager();

	std::vector<Score> getScores() { return _scores; }

	void addScore(const char name[256], const T score);

	void modifyScoreByIndex(int index, T newScore);

	void removeScore(int index);

	void showScores();

	void saveScore();

	void loadScore();

private:

	void createFile();
	void sortScore();
	std::vector<Score> _scores;
	std::string _fileName;

	const inline bool existFile() const {
		struct stat buffer;
		return (stat(_fileName.c_str(), &buffer) == 0);
	}
};


/**
* Construct by default here create a file called score.bin by default if not exist previously
*/
template<class T>
ScoreManager<T>::ScoreManager<T>() : _fileName("scores.bin")
{

	if (!existFile())
	{
		createFile();
	}

}

/**
* construct of ScoreManager Here create a file if not exist previously
*
* @param string 'newName' of file you want to create
*/
template<class T>
ScoreManager<T>::ScoreManager<T>(std::string newName) : _fileName(newName)
{
	if (!existFile())
	{
		createFile();
	}
}
template<class T>
ScoreManager<T>::~ScoreManager<T>()
{
	_scores.clear();
}

template<class T>
void ScoreManager<T>::addScore(const char name[256], const T score)
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

template<class T>
void ScoreManager<T>::modifyScoreByIndex(int index, T newScore)
{
	_scores.at(index - 1)._score = newScore;
	sortScore();
}

template<class T>
void ScoreManager<T>::removeScore(int index)
{
	_scores.erase(_scores.begin() + index - 1);
}

template<class T>
void ScoreManager<T>::showScores()
{
	int i = 1;
	for (auto&& s : _scores)
	{
		std::cout << i << ". " << s._name << " " << s._score << std::endl;
		i++;
	}
}

template<class T>
void ScoreManager<T>::saveScore()
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

template<class T>
void ScoreManager<T>::loadScore()
{
	std::ifstream iFile(_fileName, std::ios::binary | std::ios::ate);

	if (!iFile.is_open())
	{
		std::cout << "Cannot open file!" << std::endl;
	}
	size_t bufferSize = iFile.tellg();
	iFile.seekg(0, iFile.beg);
	std::vector<char> buffer(bufferSize);
	iFile.getline(buffer.data(), bufferSize, '\n');

	auto currentItem = buffer.begin();

	while (currentItem != buffer.end())
	{
		auto iHead = currentItem;

		while (*iHead != '\0')
		{
			iHead++;
		}
		auto nameBegin = currentItem;
		auto nameEnd = iHead;

		currentItem = ++iHead;

		Score rScore;
		rScore._name = std::string(nameBegin, nameEnd).c_str();
		rScore._score = *reinterpret_cast<T*>(&currentItem);

		_scores.emplace_back(rScore);

		currentItem += sizeof(T);
	}

	/*Score rScore;

	while (!iFile.eof())
	{
		iFile.read(reinterpret_cast<char*>(&rScore), sizeof(Score));

		if (rScore._name != "" && rScore._score > 0)
		{
			_scores.emplace_back(rScore);
		}
	}*/


	iFile.close();

}

template<class T>
void ScoreManager<T>::createFile()
{
	std::ofstream file(_fileName);
}

template<class T>
void ScoreManager<T>::sortScore()
{
	std::sort(_scores.begin(), _scores.end(), [](Score& a, Score& b) {return a._score > b._score; });
}

template<>
void ScoreManager<char>::sortScore()
{
	std::sort(_scores.begin(), _scores.end(), [](Score& a, Score& b) {return a._score < b._score; });
}
