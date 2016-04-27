#pragma once

namespace Engine
{
	class InterruptActionException : std::exception
	{
	public:
		const char* what() const throw() override
		{
			return "Object removed in process.";
		}
	};
}

