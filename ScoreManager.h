#pragma once
#include <vector>
#include <string>

struct Score
{
	int _score{};
	char _name[256]{};

};
class ScoreManager
{
public:
	ScoreManager();

	~ScoreManager();

	void addScore(const char name[256],const int score);

	void modifyScoreByIndex(int index, int newScore);

	void removeScore(int index);

	void showScores();

	void saveScore();

	void loadScore();
private:

	void sortScore();
	std::vector<Score> _scores;
	std::string _fileName;
};

