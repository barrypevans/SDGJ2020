#pragma once
#include "component.h"
#include <vector>
#include "renderable-digit.h"
class NumberRenderer : public Component
{
public:
	virtual void Init() override;
	virtual void Update() override;
	void SetNumber(int value);
	std::vector<RenderableDigit*> m_digits;
	const float kDigitSize = .5f;
	int targetValue;
	int viewValue;
};