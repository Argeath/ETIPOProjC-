#pragma once

#ifdef DEBUG_MODE
	namespace Engine {
		class DebugElement
		{
		public:
			virtual ~DebugElement() {}

			virtual void debug() = 0;
		};

		class Debug {
			std::list<DebugElement*> debugElements;

		public:
			void drawDebugElements();
		};
	}
#endif