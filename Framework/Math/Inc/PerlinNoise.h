#pragma once
//References:
//https://solarianprogrammer.com/2012/07/18/perlin-noise-cpp-11/
//https://www.scratchapixel.com/code.php?id=57&origin=/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2
//https://youtu.be/6-0UaeJBumA
//https://www.redblobgames.com/maps/terrain-from-noise/

namespace Omega::Math
{
	class PerlinNoise
	{
	public:
		/// <summary>
		///Initialize with the reference values for the permutation vector 
		/// </summary>
		/// <returns></returns>
		PerlinNoise();
		/// <summary>
		///Generate a new permutation vector based on the value of seed 
		/// </summary>
		/// <param name="seed"></param>
		/// <returns></returns>
		PerlinNoise(const uint32_t seed = 256);

		PerlinNoise(const PerlinNoise&) = delete;
		PerlinNoise& operator=(const PerlinNoise&) = delete;

		/// <summary>
		/// Get a noise value, for 2D images z can have any value 
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <returns></returns>
		float Noise(float x, float y, float z);
	private:
		constexpr float fade(float t) const
		{
			return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
		}

		constexpr float gradient(int hash, float x, float y, float z) const
		{
			int h = hash & 15;
			// Convert lower 4 bits of hash into 12 gradient directions
			float u = (h < 8) ? x : y;
			float v = (h < 4) ? y : (h == 12 || h == 14) ? x : z;
			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		std::vector<int> mPermutation;
	};
}