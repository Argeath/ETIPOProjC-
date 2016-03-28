#pragma once

using namespace std;

namespace Engine
{
	struct Resource {
		SDL_Surface* source;
		Utils::Text name;
	};

	class ResourceManager
	{
		vector<Resource*> resources;

	public:
		Resource* getResourceByIndex(int index)
		{
			if(resources.size() > 0)
				return resources[index];
			return nullptr;
		}

		Resource* getResourceByName(Utils::Text name)
		{
			for (vector<Resource*>::iterator i = resources.begin(); i != resources.end(); i++)
				if ((*i)->name == name)
					return *i;

			return nullptr;
		}

		int AddResource(Utils::Text filename, Utils::Text name)
		{
			Resource* res = new Resource;
			res->name = name;
			res->source = LoadSurface(filename);

			if(res->source == nullptr)
			{
				throw new ResourceNotLoadedException(filename);
			}
			resources.push_back(res);
			return resources.size() - 1;
		}

		~ResourceManager() {
			for (vector<Resource*>::iterator i = resources.begin(); i != resources.end(); i++)
				SDL_FreeSurface((*i)->source);

			resources.clear();
		}
	};
}
