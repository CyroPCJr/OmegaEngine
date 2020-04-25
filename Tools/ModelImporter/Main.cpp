#include <Graphics/Inc/Graphics.h>
#include <Math/Inc/EngineMath.h>

#include <assimp/Importer.hpp> //
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cstdio>

using namespace Omega::Graphics;

struct Arguments
{
	const char* inputFileName = nullptr;
	const char* outputFileName = nullptr;
	float scale = 1.0f;
	bool animOnly = false;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	// We need at least 3 arguments.
	if (argc < 3)
	{
		return std::nullopt;
	}

	Arguments args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];

	for (int i = 1; i + 2 < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 's':
				args.scale = static_cast<float>(atof(argv[i + 1]));
				break;
			default:
				break;
			}
		}
	}
	return args;
}

void PrintUsage()
{
	printf_s("== ModelImporter Help ==\n\n"
		"Usage:\n"
		"	ModelImporter.exe [Options] <InputFile> <OutputFile>\n\n"
		"Options:\n"
		"	-s	Scale applied to the model.\n");
}

void SaveModel(const Arguments& args, const Model& model)
{
	// For homework. This is basically the opposite of LoadModel..
}

int main(int argc, char* argv[])
{

	const auto argsOpt = ParseArgs(argc, argv);
	if (!argsOpt.has_value())
	{
		PrintUsage();
		return -1;
	}

	const auto& args = argsOpt.value();

	// Create an instance of the importer class to do the parsing for us.
	Assimp::Importer importer;
	// scene
	// +- mesh[][][][][]
	// +- material[][][][][]
	// +- animation[][][][][_]
	// 
	// +- mRootNode (scene graph)
	//        +- Node
	//            +- Node
	//            +- Node
	//                +- Node ...
	//        +- Node
	//            +- Node ...
	//        +- Node

	// Try to import the model into a scene.
	const aiScene* scene = importer.ReadFile(args.inputFileName,
		aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);

	if (!scene)
	{
		printf_s("Error: %s\n", importer.GetErrorString());
		return -1;
	}

	Model model;

	if (scene->HasMeshes())
	{
		const uint32_t numMeshes = scene->mNumMeshes;
		model.meshData.resize(numMeshes);
	}

	SaveModel(args, model);

	printf_s("All done!\n");

	return 0;
}