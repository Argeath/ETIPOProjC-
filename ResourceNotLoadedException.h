#pragma once

namespace Engine
{
	class ResourceNotLoadedException : public std::exception
	{
		Utils::Text filepath;

	public:
		ResourceNotLoadedException() { filepath = "unknown"; }

		ResourceNotLoadedException(Utils::Text file)
		{
			filepath = file;
		}

		const char* what() const throw() override
		{
			return T("Resource (") + filepath  + T(") could not be loaded.");
		}
	};
}
