#pragma once

namespace Game {
	class World : public Engine::BaseGame
	{
		std::vector<Organism*> organisms;
		std::vector<Organism*> toBorn;
		Organism*** organismMap;
		Player* player;

		void render() override;
		void createRandomOrganisms();
		Organism* createOrganism(OrganismType type);

	public:
		int round;
		bool isPlayerMove;

		World(Engine::Window* window) : BaseGame(window), round(0), isPlayerMove(false)
		{
			organismMap = new Organism**[MAP_HEIGHT];
			for (int i = 0; i < MAP_HEIGHT; i++) {
				organismMap[i] = new Organism*[MAP_WIDTH];
				for (int ix = 0; ix < MAP_WIDTH; ix++)
					organismMap[i][ix] = nullptr;

			}

			createPlayer();
			createRandomOrganisms();
		}

		void createPlayer();
		void addOrganism(Organism* organism);
		Organism* getOrganismOnPos(Utils::Vector2<int> pos);
		void moveOrganism(Organism* organism, Utils::Direction dir);

		static bool compareOrganismsByInitiative(const Organism* a, const Organism* b);

		void update(int input) override;
	};
}
