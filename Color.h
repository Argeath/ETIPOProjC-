#pragma once

namespace Utils {

	class Color {
	public:

		static int czarny;
		static int prawieCzarny;
		static int zielony;
		static int trawiasty;
		static int czerwony;
		static int niebieski;
		static int fioletowy;
		static int zolty;
		static int rozowy;
		static int brazowy;
		static int szary;
		static int pomaranczowy;

		static void init(SDL_Surface *screen);
	};
}