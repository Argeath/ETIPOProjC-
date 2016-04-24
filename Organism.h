#pragma once

namespace Game
{
	class World;

	enum OrganismType
	{
		HUMAN,
		WOLF,
		SHEEP,
		TURTLE,
		FOX,
		ANTELOPE,
		GRASS,
		GUARANA,
		WOLFBERRY,
		SOW_THISTLE,
		NONE
	};

	struct OrganismAppearance
	{
		char sign;
		unsigned long colors;

		OrganismAppearance()
		{
			sign = 'x';
			colors = COLOR_PAIR(1);
		}
	};

	class Organism
	{
	public:
		virtual ~Organism()
		{
		}

		Organism(World* w) : age(0), strength(0), initiative(0), isDieing(false), world(w)
		{
			appearance = OrganismAppearance();
		}

		int age;
		int strength;
		int initiative;
		Utils::Vector2<int> position;
		OrganismAppearance appearance;
		bool isDieing;


		Utils::Direction getRandomDirection(bool mustBeEmpty = false) const;
		void breed(Organism* otherParent = nullptr);

		static Organism* getOrganismByType(OrganismType type, World* world);
		static Utils::Text getOrganismNameByType(OrganismType type);

		virtual void action() = 0;
		virtual void collision(Organism* target, bool isAttacker = false) = 0;
		virtual OrganismType getType() = 0;
		virtual void onDie() = 0;
	protected:
		World* world;
	};
}

