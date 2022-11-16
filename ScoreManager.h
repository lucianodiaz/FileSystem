#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

template <class T = unsigned int> 
class ScoreManager
{
private:
	struct Score
	{
		char _name[256]{};
		T _score{};
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

	std::vector<Score> getScores() { return m_scores; }

	void addScore(const char name[256], const T score);

	void modifyScoreByIndex(int index, T newScore);

	void removeScore(int index);

	void showScores();

	void saveScore();

	void loadScore();

private:

	void createFile();
	void sortScore();
	std::vector<Score> m_scores;
	std::string m_fileName;

	const inline bool existFile() const {
		struct stat buffer;
		return (stat(m_fileName.c_str(), &buffer) == 0);
	}
};


/**
* Construct by default here create a file called score.bin by default if not exist previously
*/
template<class T>
ScoreManager<T>::ScoreManager<T>() : m_fileName("scores.bin")
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
ScoreManager<T>::ScoreManager<T>(std::string newName) : m_fileName(newName)
{
	if (!existFile())
	{
		createFile();
	}
}
template<class T>
ScoreManager<T>::~ScoreManager<T>()
{
	m_scores.clear();
}

template<class T>
void ScoreManager<T>::addScore(const char name[256], const T score)
{
	Score newScore;
	strcpy_s(newScore._name, name);
	newScore._score = score;
	if (!std::count(m_scores.begin(), m_scores.end(), newScore))
	{
		m_scores.emplace_back(newScore);
	}

	sortScore();
}

template<class T>
void ScoreManager<T>::modifyScoreByIndex(int index, T newScore)
{
	m_scores.at(index - 1)._score = newScore;
	sortScore();
}

template<class T>
void ScoreManager<T>::removeScore(int index)
{
	m_scores.erase(m_scores.begin() + index - 1);
}

template<class T>
void ScoreManager<T>::showScores()
{
	int i = 1;
	for (auto&& s : m_scores)
	{
		std::cout << i << ". " << s._name << " " << s._score << std::endl;
		i++;
	}
}

template<class T>
void ScoreManager<T>::saveScore()
{
	std::ofstream oFile(m_fileName, std::ios::out | std::ios::binary | std::ios::trunc);
	if (oFile.fail())
	{
		std::cout << "Cannot open file!" << std::endl;
		return;
	}
	if (oFile.is_open())
	{
		for (auto&& s : m_scores)
		{
			oFile.write((char*)&s, sizeof(Score));
			/*oFile.write(s._name, (sizeof(s._name) + 1) * sizeof(char));
			oFile.write(reinterpret_cast<char*>(&s._score), sizeof s._score);*/
		}
		oFile.close();
	}


}

template<class T>
void ScoreManager<T>::loadScore()
{
	std::ifstream iFile(m_fileName, std::ios::in | std::ios::binary | std::ios::beg);
	if (!iFile.is_open())
	{
		std::cout << "ERROR: Load operation failed. Could not open the score file!" << std::endl;
		return;
	}
	Score rScore;
	
	while (!iFile.eof())
	{
		iFile.read(reinterpret_cast<char*>(&rScore), sizeof(Score));
		if (rScore._name != "" && rScore._score > 0)
		{
			if (!std::count(m_scores.begin(), m_scores.end(), rScore))
			{
				m_scores.emplace_back(rScore);
			}
		}
	}
	

	/*while (!iFile.eof())
	{
		iFile.read(reinterpret_cast<char*>(&rScore), sizeof(Score));
	
		if (rScore._name != "" && rScore._score > 0)
		{
			m_scores.emplace_back(rScore);
		}
	}*/


	iFile.close();

}

template<class T>
void ScoreManager<T>::createFile()
{
	std::ofstream file(m_fileName);
}

template<class T>
void ScoreManager<T>::sortScore()
{
	std::sort(m_scores.begin(), m_scores.end(), [](Score& a, Score& b) {return a._score > b._score; });
}

template<>
void ScoreManager<char>::sortScore()
{
	std::sort(m_scores.begin(), m_scores.end(), [](Score& a, Score& b) {return a._score < b._score; });
}
