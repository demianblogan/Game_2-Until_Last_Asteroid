#pragma once
#include <numbers>

// Class Math contains any math constants and math algorithms.
class Math
{
public:
	Math() = delete;
	static constexpr float PI = float(std::numbers::pi);
};