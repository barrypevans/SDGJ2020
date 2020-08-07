#include "asset-manager.h"
#include "../external/dirent.h"

void AssetManager::Init()
{
	CreateFileManifest();
	LoadAssets();
}

void AssetManager::CleanUp()
{

}

Hashcode AssetManager::FnvHash(const char* inputString)
{
	const unsigned int length = strlen(inputString);
	Hashcode hash = kFnvOffsetBasis;

	for (int i = 0; i < length; ++i)
	{
		hash ^= inputString[i];
		hash *= kFnvPrime;
	}

	return hash;
}

void AssetManager::CreateFileManifest()
{
	CreateFileManifest_Recursive("./resources/");
}

void AssetManager::CreateFileManifest_Recursive(std::string path)
{
	if (auto dir = opendir(path.c_str())) {
		while (auto f = readdir(dir)) {
			if (!f->d_name || f->d_name[0] == '.') continue;
			if (f->d_type == DT_DIR)
				CreateFileManifest_Recursive(path + f->d_name + "/");

			if (f->d_type == DT_REG)
				m_assetManifest.push_back(path + f->d_name);
		}
		closedir(dir);
	}
}

void AssetManager::LoadAssets()
{
	for (std::string path : m_assetManifest)
	{
		size_t extIndex = path.find_last_of(".") + 1;
		std::string extension = path.substr(extIndex, path.length() - extIndex);
		
		// normalize to lower case
		for (int i = 0; i < extension.length(); ++i)
			extension[i] = std::tolower(extension[i]);

		if (extension == "jpg" |
			extension == "png" |
			extension == "tga")
		{
			// load image
		}
		else if(extension == "txt" |
				extension == "vs"  |
				extension == "ps")
		{
			// load text file
		}
		else 
		{
			// unknown type, load as generic binary file
		}
	}
}
