#pragma once
#include <string>

class BinaryAsset
{
public:
	BinaryAsset(const char* contents, size_t size, bool isText = false);
	~BinaryAsset();

	std::string AsString();

	char* m_pContents;
	size_t m_size;

};

