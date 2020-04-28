#include "Precompiled.h"
#include "MeshIO.h"

using namespace Omega::Graphics;

//Referece
//https://www.modernescpp.com/index.php/c-17-more-details-about-the-library

void MeshIO::Write(FILE* file, const Mesh& mesh)
{
	/*uint32_t numVertices = mesh.vertices.size();
	fprintf_s(file, "%d\n", numVertices);
	for (auto& vertex : mesh.vertices)
	{
		fprintfs_s(file, "?????????", vertex....);
	}*/

	// 100
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
	// 2.3 4.5 7.9 .....
}

void MeshIO::Read(FILE* file, Mesh& mesh)
{
	//Reference:
	//https://stackoverflow.com/questions/116038/how-do-i-read-an-entire-file-into-a-stdstring-in-c/40903508#40903508

	/*int numVertices;
	fscanf_s(file, "%d\n", &numVertices);
	mesh.vertices.resize()
	for (int i = 0; i < numVertices; ++i)
	{

	}*/
}