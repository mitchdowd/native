// Standard Dependencies
#include <cmath>
#include <random>

// Module Dependencies
#include "../../include/math.h"

namespace native
{
	static std::default_random_engine engine;

	double Math::sqrt(double value)
	{
		return (double)std::sqrt((long double)value);
	}

	long double Math::random(long double min, long double outerMax)
	{
		return std::uniform_real_distribution<long double>(min, outerMax)(engine);
	}

	double Math::random(double min, double outerMax)
	{
		return std::uniform_real_distribution<double>(min, outerMax)(engine);
	}

	float Math::random(float min, float outerMax)
	{
		return std::uniform_real_distribution<float>(min, outerMax)(engine);
	}

	int Math::random(int min, int outerMax)
	{
		return int(std::uniform_real_distribution<double>(double(min), double(outerMax))(engine));
	}
}
