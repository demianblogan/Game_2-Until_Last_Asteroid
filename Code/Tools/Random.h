#pragma once
#include <random>

// Class Random is a utility class for generating random numbers (integer, float, double).
class Random
{
public:
	Random() = delete;

	static int GenerateInt(int min, int max);
	static float GenerateFloat(float min, float max);
	static double GenerateDouble(double min, double max);

private:
	static std::random_device randomDevice;
	static std::mt19937_64 generator;
};