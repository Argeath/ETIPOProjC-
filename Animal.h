#pragma once

namespace Game
{
	class Animal : public Organism
	{
	protected:
		int alreadyBornChilds;
		int timeSinceLastBreed;
	public:

		Animal(World* w) : Organism(w), alreadyBornChilds(0), timeSinceLastBreed(0)
		{
		}

		void action() override;
		void collision(Organism* target, bool isAttacker = false) override;

		int getTimeSinceLastBreed() const
		{
			return timeSinceLastBreed;
		}

		void setTimeSinceLastBreed(int value)
		{
			timeSinceLastBreed = value;
		}

		void increaseTimeSinceLastBreed()
		{
			timeSinceLastBreed++;
		}

		void onDie() override
		{
		}
	};
}

