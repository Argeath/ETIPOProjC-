#pragma once

namespace Utils
{
	class io
	{
	public:
		template <typename T>
		static void write(std::ofstream& o, const T& value)
		{
			o.write((const char *)&value, sizeof(T));
		}

		template <typename T>
		static void read(std::ifstream& i, T& value)
		{
			i.read((char *)&value, sizeof(T));
		}

		static void writeString(std::ofstream& o, char* value)
		{
			o.write(value, strlen(value));
		}

		static void readString(std::ifstream& i, char* value)
		{
			i.read(value, strlen(value));
		}
	};
}

