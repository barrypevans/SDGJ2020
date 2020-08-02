#pragma once

class ISystem
{
public:
	virtual void Init() = 0;
	virtual void CleanUp() = 0;
	virtual void Update(){};
};