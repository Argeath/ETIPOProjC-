#pragma once

namespace Game {
	class World : public Engine::BaseGame
	{
		std::vector<Organism*> organisms;
		std::vector<Organism*> toBorn;
		Organism*** organismMap;

		void render() override;
		void createRandomOrganisms();
		void createOrganism(OrganismType type);
	public:
		World(Engine::Window* window) : BaseGame(window)
		{
			organismMap = new Organism**[MAP_HEIGHT];
			for (int i = 0; i < MAP_HEIGHT; i++) {
				organismMap[i] = new Organism*[MAP_WIDTH];
				for (int ix = 0; ix < MAP_WIDTH; ix++)
					organismMap[i][ix] = nullptr;

			}

			createRandomOrganisms();
		}

		void addOrganism(Organism* organism);
		Organism* getOrganismOnPos(Utils::Vector2<int> pos);
		void moveOrganism(Organism* organism, Utils::Direction dir);

		static bool compareOrganismsByInitiative(const Organism* a, const Organism* b);

		void update() override;
	};
}
