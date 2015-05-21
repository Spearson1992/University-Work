#ifndef GameLogic_H
#define GameLogic_H

namespace Game
{
	class GameLogic
	{
	private:
		int score;
		int lives;
		bool isMultiball;
		bool isGameOver;
		bool ballReset;

		int multiBallsRemaining;


	public:
		GameLogic();
		//removes a life
		inline void removeLife()
		{
			lives -= 1;
		}
		//Get lives remaining
		inline int GetLives()
		{
			return lives;
		}
		//Add to score
		inline void IncreaseScore(int _score)
		{
			score += _score;
		}
		//Return score
		inline int GetScore()
		{
			return score;
		}

		//Sets game over state
		void GameOver();

		//returns if game is over
		inline bool IsGameOver()
		{
			return isGameOver;
		}

		//begin multiball
		inline void SetMultiball()
		{
			isMultiball = true;
		}
		//stop multiball
		inline void EndMultiball()
		{
			isMultiball = false;
		}

		//get multiball status
		inline bool IsMultiball()
		{
			return isMultiball;
		}
		
	};
}

#endif