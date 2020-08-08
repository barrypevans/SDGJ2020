#include "binary-asset.h"
#include <stdlib.h>
#include <string.h>
#include "assert.h"

BinaryAsset::BinaryAsset(const char* contents, size_t size, bool isText) : m_size(size)
{
	ASSERT(contents, "Error: null contents provided to text asset.");

	m_pContents = (char*)malloc(size+1);
	ASSERT(m_pContents, "Error: Failed to allocate memory for text asset.");
	memcpy(m_pContents, contents, size+1);
}

BinaryAsset::~BinaryAsset()
{
	free(m_pContents);
}

std::string BinaryAsset::AsString()
{
	return std::string(m_pContents);
}
