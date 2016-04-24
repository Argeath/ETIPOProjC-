#pragma once

namespace Game
{
	class SowThistle : public Plant
	{
	public:
		SowThistle(World* w) : Plant(w)
		{
			appearance.sign = 'M';
			appearance.colors = COLOR_PAIR(5) | A_BOLD;
		}

		void action() override
		{
			Plant::action();
			Plant::action();
			Plant::action();
		}

		OrganismType getType() override
		{
			return SOW_THISTLE;
		}
	};
}

