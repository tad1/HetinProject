#pragma once
#include "Time.h"

enum Grade {F,D,C,B,A,S};


/// <summary>
/// Class that storage score info
/// </summary>
class Score {
	int score;
	Grade grade;
	Grade previousGrade;
	int combo;
	float comboTime;
	float comboTimer;
public:
	int getScore() {
		return score;
	}

	int getCombo() {
		return combo;
	}

	float getComboTimeNormalized() {
		return comboTimer / comboTime;
	}

	void addScore(int value) {
		score += value * combo;
		combo++;
		comboTimer = comboTime;
	}

	char* getGrade() {
		switch (grade) {
		case S:return "S";
		case A:return"A";
		case B:return "B";
		case C:return "C";
		case D:return "D";
		case F:return "F";
		}
	}

	/// <summary>
	/// Return true if grade has just changed
	/// </summary>
	bool gradeChanged() {
		return grade != previousGrade;
	}

	/// <summary>
	/// Calculate grade, based on score
	/// </summary>
	/// <returns></returns>
	Grade calcGrade() {

		if (score > 5000) {
			return S;
		}
		else if (score > 2000) {
			return A;
		}
		else if (score > 1000) {
			return B;
		}
		else if (score > 500) {
			return C;
		}
		else if (score > 100) {
			return D;
		}
		return F;
	}

	void removeScore(int value) {
		score -= value;
	}

	void update() {

		comboTimer -= Time.deltaTime;
		if (comboTimer <= 0) {
			comboTimer = 0;
			combo = 1;
		}
		previousGrade = grade;
		grade = calcGrade();
	}

	void Reset() {
		score = 0;
		combo = 1;
		comboTimer = 0;
		previousGrade = grade = F;
	}

	Score() {
		comboTime = 4.0f; //2 seconds
		Reset();
	}
};

static Score mainScore;