#pragma once

namespace Game
{
	class World : public Engine::BaseGame
	{
		std::vector<Organism*> organisms;
		std::vector<Organism*> toBorn;
		Organism*** organismMap;

		void render() override;
		void createRandomOrganisms();
		Organism* createOrganism(OrganismType type);

	public:
		int round;
		bool isPlayerMove;
		Player* player;

		World(Engine::Window* window) : BaseGame(window), round(0), isPlayerMove(false), player(nullptr)
		{
			organismMap = new Organism**[size.y];
			for (int i = 0; i < size.y; i++)
			{
				organismMap[i] = new Organism*[size.x];
				for (int ix = 0; ix < size.x; ix++)
					organismMap[i][ix] = nullptr;
			}
		}

		World(Engine::Window* window, Utils::Vector2<int> s) : BaseGame(window), round(0), isPlayerMove(false), player(nullptr)
		{
			size = s;
			organismMap = new Organism**[size.y];
			for (int i = 0; i < size.y; i++)
			{
				organismMap[i] = new Organism*[size.x];
				for (int ix = 0; ix < size.x; ix++)
					organismMap[i][ix] = nullptr;
			}
		}


		void init() override;
		void createPlayer();
		void addOrganism(Organism* organism);
		Organism* getOrganismOnPos(Utils::Vector2<int> pos) const;
		void moveOrganism(Organism* organism, Utils::Direction dir) const;

		void save(std::ofstream& _out) override;
		static World* load(std::ifstream& _in, Engine::Window* window);

		static bool compareOrganismsByInitiative(const Organism* a, const Organism* b);


		void update(int input) override;
	};
}

