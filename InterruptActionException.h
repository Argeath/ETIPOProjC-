#pragma once

namespace Engine
{
	class InterruptActionException : std::exception
	{
		virtual const char* what() const throw()
		{
			return "Object removed in process.";
		}
	};
}