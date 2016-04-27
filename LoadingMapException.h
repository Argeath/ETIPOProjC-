#pragma once

namespace Engine
{
	class LoadingMapException : public std::exception
	{
		Utils::Text str;

	public:
		const char* what() const throw() override
		{
			return str;
		}

		LoadingMapException(Utils::Text t) : str(t)
		{
		}
	};
}

