#include "Precompiled.h"
#include "PerlinNoise.h"
#include "EngineMath.h"

using namespace Omega;
using namespace Omega::Math;

PerlinNoise::PerlinNoise()
{// Initialize the permutation vector with the reference values
	mPermutation = {
		151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
		8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
		35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
		134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
		55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
		18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
		250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
		189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
		43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
		97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
		107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
	// Duplicate the permutation vector
	mPermutation.insert(mPermutation.end(), mPermutation.begin(), mPermutation.end());
}

PerlinNoise::PerlinNoise(const uint32_t seed)
{
	mPermutation.resize(256);

	// Fill p with values from 0 to 255
	std::iota(mPermutation.begin(), mPermutation.end(), 0);

	// Initialize a random engine with seed
	std::default_random_engine engine(seed);

	// Suffle  using the above random engine
	std::shuffle(mPermutation.begin(), mPermutation.end(), engine);

	// Duplicate the permutation vector
	mPermutation.insert(mPermutation.end(), mPermutation.begin(), mPermutation.end());
}

float PerlinNoise::Noise(float x, float y, float z)
{
	// Find the unit cube that contains the point
	const int cubeX = static_cast<int>(floorf(x)) & 255;
	const int cubeY = static_cast<int>(floorf(y)) & 255;
	const int cubeZ = static_cast<int>(floorf(z)) & 255;

	// Find relative x, y,z of point in cube
	x -= floorf(x);
	y -= floorf(y);
	z -= floorf(z);

	// Compute fade curves for each of x, y, z
	const float u = fade(x);
	const float v = fade(y);
	const float w = fade(z);

	// Hash coordinates of the 8 cube corners
	const int A = mPermutation[cubeX] + cubeY;
	const int AA = mPermutation[A] + cubeZ;
	const int AB = mPermutation[A + 1] + cubeZ;
	const int B = mPermutation[cubeX + 1] + cubeY;
	const int BA = mPermutation[B] + cubeZ;
	const int BB = mPermutation[B + 1] + cubeZ;

	// Add blended results from 8 corners of cube
	float res = Lerp<float>(w,

		Lerp<float>(v,
			Lerp<float>(u, gradient(mPermutation[AA], x, y, z),
				gradient(mPermutation[BA], x - 1.0f, y, z)),
			Lerp<float>(u,
				gradient(mPermutation[AB], x, y - 1.0f, z),
				gradient(mPermutation[BB], x - 1.0f, y - 1.0f, z))),

		Lerp<float>(v,
			Lerp<float>(u,
				gradient(mPermutation[AA + 1], x, y, z - 1),
				gradient(mPermutation[BA + 1], x - 1.0f, y, z - 1.0f)),
			Lerp<float>(u, gradient(mPermutation[AB + 1], x, y - 1.0f, z - 1.0f),
				gradient(mPermutation[BB + 1], x - 1.0f, y - 1.0f, z - 1.0f))));
	return (res + 1.0f) / 2.0f;
}
