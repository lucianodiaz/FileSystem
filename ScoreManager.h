#pragma once
#include <vector>
#include <string>

class ScoreManager
{
private:
	struct Score
	{
		int _score{};
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

	const std::vector<Score> getScores() const;

	void addScore(const char name[256],const int score);

	void modifyScoreByIndex(int index, int newScore);

	void removeScore(int index);

	void showScores();

	void saveScore();

	void loadScore();
	
private:

	void createFile();
	void sortScore();
	std::vector<Score> _scores;
	std::string _fileName;

	inline bool existFile() {
		struct stat buffer;
		return (stat(_fileName.c_str(), &buffer) == 0);
	}
};

