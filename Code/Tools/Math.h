#pragma once
#include <numbers>

// Class Math contains mathematical constants and algorithms.
class Math
{
public:
	Math() = delete;
	static constexpr float PI = float(std::numbers::pi);
};