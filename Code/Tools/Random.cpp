#include "Random.h"

std::random_device Random::randomDevice;
std::mt19937_64 Random::generator(Random::randomDevice());

int Random::GenerateInt(int min, int max)
{
	if (min > max)
		std::swap(min, max);

	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

float Random::GenerateFloat(float min, float max)
{
	if (min > max)
		std::swap(min, max);

	// std::uniform_real_distribution doesn't count max value when generating a random number. To fix this, I use
	// std::nextafter to get next value after "max" value.
	std::uniform_real_distribution<float> distribution(min, std::nextafter(max, std::numeric_limits<float>::max()));
	return distribution(generator);
}

double Random::GenerateDouble(double min, double max)
{
	if (min > max)
		std::swap(min, max);

	// std::uniform_real_distribution doesn't count max value when generating a random number. To fix this, I use
	// std::nextafter to get next value after "max" value.
	std::uniform_real_distribution<double> distribution(min, std::nextafter(max, std::numeric_limits<double>::max()));
	return distribution(generator);
}
