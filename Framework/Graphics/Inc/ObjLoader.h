#pragma once

#include "Mesh.h"

namespace Omega::Graphics
{

	class ObjLoader
	{
	public:
		static void Load(const std::filesystem::path& filePath, float scale, Mesh& mesh);
	private:

	};
}