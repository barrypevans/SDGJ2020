#pragma once
#include <map>
#include <vector>
#include <string>

#include "ISystem.h"
typedef unsigned long long Hashcode;

class AssetManager : public ISystem
{
public:
	// Inherited via ISystem
	virtual void Init() override;
	virtual void CleanUp() override;

	// Please provide an asset path relative to the resource folder.
	template<class AssetType>
	AssetType* GetAsset(const char* assetPath)
	{
		Hashcode hash = FnvHash(assetPath);

		auto it = m_resourceMap.find(hash);
		if (it == m_resourceMap.end())
			return nullptr;

		return reinterpret_cast<AssetType*>(m_resourceMap[hash]);
	}

private:

	static const Hashcode kFnvOffsetBasis = 14695981039346656037;
	static const Hashcode kFnvPrime = 1099511628211;
	static Hashcode FnvHash(const char* inputString);

	void CreateFileManifest();
	void CreateFileManifest_Recursive(std::string filePath);

	void LoadAssets();

	void LoadImageAsset(std::string assetPath);
	void LoadTextAsset(std::string assetPath);
	void LoadBinAsset(std::string assetPath, bool isText = false);

	std::map<Hashcode, void*> m_resourceMap;
	std::vector<std::string> m_assetManifest;
};

static AssetManager* g_pAssetManager;