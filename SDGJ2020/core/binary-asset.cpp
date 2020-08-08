#include "binary-asset.h"
#include <stdlib.h>
#include <string.h>
#include "assert.h"

BinaryAsset::BinaryAsset(const char* contents, size_t size, bool isText) : m_size(size)
{
	ASSERT(contents, "Error: null contents provided to text asset.");
	
	// add one byte for null terminator
	if (isText)
		size += 1;

	m_pContents = (char*)malloc(size + 1);
	ASSERT(m_pContents, "Error: Failed to allocate memory for text asset.");
	memcpy(m_pContents, contents, size);
	
	// null terminate string
	if (isText)
		m_pContents[size] = 0;
}

BinaryAsset::~BinaryAsset()
{
	free(m_pContents);
}

std::string BinaryAsset::AsString()
{
	return std::string(m_pContents);
}
