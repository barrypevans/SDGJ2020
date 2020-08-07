#pragma once
#include <map>

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

	}

private:

	static Hashcode FnvHash(const char* inputString);

	std::map<Hashcode, void*> m_resourceMap;
};