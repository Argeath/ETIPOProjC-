#pragma once

namespace Game
{
	class Grass : public Plant
	{
	public:
		Grass(World* w) : Plant(w) {
			appearance.colors = COLOR_PAIR(2);
		}

		OrganismType getType() override { return GRASS; }
	};
}