#include "asset-manager.h"
#include "../external/dirent.h"
#include <fstream>
#include "texture.h"
#include "binary-asset.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

void AssetManager::Init()
{
	CreateFileManifest();
	LoadAssets();
}

void AssetManager::CleanUp()
{
	for (auto resource : m_resourceMap)
	{
		delete resource.second;
	}
	m_resourceMap.clear();
}

Hashcode AssetManager::FnvHash(const char* inputString)
{
	const unsigned int length = static_cast<unsigned int>(strlen(inputString));
	Hashcode hash = kFnvOffsetBasis;

	for (unsigned int i = 0; i < length; ++i)
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
			LoadImageAsset(path);
		}
		else if(extension == "txt" |
				extension == "vs"  |
				extension == "ps")
		{
			LoadTextAsset(path);
		}
		else 
		{
			LoadBinAsset(path);
		}
	}
}

void AssetManager::LoadImageAsset(std::string assetPath)
{
	int x, y, n;
	unsigned char *data = stbi_load(assetPath.c_str(), &x, &y, &n, 4);
	Texture* pTexture = new Texture(data, x, y, n);
	Hashcode hash = FnvHash(assetPath.c_str());
	m_resourceMap.insert(std::pair<Hashcode, void*>(hash, pTexture));
	stbi_image_free(data);
}

void AssetManager::LoadTextAsset(std::string assetPath)
{
	LoadBinAsset(assetPath, true);
}

void AssetManager::LoadBinAsset(std::string assetPath, bool isText)
{
	std::ifstream t(assetPath);
	t.seekg(0, std::ios::end);
	size_t size = t.tellg();
	std::string buffer(size, 0);
	t.seekg(0);
	t.read(&buffer[0], size);

	BinaryAsset* pTextAsset = new BinaryAsset(buffer.c_str(), buffer.size(), isText);
	Hashcode hash = FnvHash(assetPath.c_str());
	m_resourceMap.insert(std::pair<Hashcode, void*>(hash, pTextAsset));
}

