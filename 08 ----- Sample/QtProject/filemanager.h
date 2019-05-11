#ifndef __FILEMANAGER_H
#define __FILEMANAGER_H

#include "polygonmesh3d.h"

#include <QtDebug>
#include <QString>

class CFileManager
{
// Construction and destruction function
public:
	CFileManager(){}
	~CFileManager(){}

// public function
public:
	inline bool ReadOffFile(CPolygonMesh3D *pm, QString fn);
	inline bool WriteOffFile(CPolygonMesh3D *pm, QString fn);

};

//////////////////////////////////////////////////////////////////////
// read data from off file
inline bool CFileManager::ReadOffFile(CPolygonMesh3D *pm, QString fn)
{
	// TODO: read data from off file
	qDebug() << ">>>>>>>> Begin to read off file......" << endl;

	FILE* in = fopen(fn.toStdString().c_str(), "r");
	if (in == NULL)
	{
		return false;
	}

	// read head information
	int iNumVertex, iNumFace, iNumEdge, iNumTriangles;
	char *buf[128];
	fscanf(in, "%s", buf);
	fscanf(in, "%d", &iNumVertex);
	fscanf(in, "%d", &iNumFace);
	fscanf(in, "%d", &iNumEdge);

	// calculate the triangles number
	int i, j;
	float x, y, z;
	for (i = 0; i < iNumVertex; i++)
		fscanf(in, "%f %f %f", &x, &y, &z);

	int i0, i1, i2;
	iNumTriangles = 0;
	for (j = 0; j < iNumFace; j++)
	{
		int num;
		fscanf(in, "%d %d %d %d", &num, &i0, &i1, &i2);
		iNumTriangles++;
		for (int k = 0; k < num - 3; k++)
		{
			i1 = i2;
			fscanf(in, "%d ", &i2);
			iNumTriangles++;
		}
	}

	// read vertex and face
	fseek(in, 0, SEEK_SET);
	fscanf(in, "%s", buf);
	fscanf(in, "%d", &iNumVertex);
	fscanf(in, "%d", &iNumFace);
	fscanf(in, "%d", &iNumEdge);

	pm->SetVertexSize(iNumVertex);
	for (i = 0; i < iNumVertex; i++)
	{
		fscanf(in, "%f %f %f", &x, &y, &z);
		pm->SetVertex(i, x, y, z);
	}

	// read triangles
	pm->SetFaceSize(iNumTriangles);
	iNumTriangles = 0;
	for (j = 0; j < iNumFace; j++)
	{
		int num;
		fscanf(in, "%d %d %d %d", &num, &i0, &i1, &i2);
		pm->SetTriangle(iNumTriangles, i0, i1, i2);
		iNumTriangles++;
		for (int k = 0; k < num - 3; k++)
		{
			i1 = i2;
			fscanf(in, "%d ", &i2);
			pm->SetTriangle(iNumTriangles, i0, i1, i2);
			iNumTriangles++;
		}
	}

	// release resource
	fclose(in);
	qDebug() << "<<<<<<<< End of reading off file." << endl << endl;

	return true;
}

//////////////////////////////////////////////////////////////////////
// write data to off file
inline bool CFileManager::WriteOffFile(CPolygonMesh3D *pm, QString fn)
{
	// TODO: write data to off file
	qDebug() << ">>>>>>>> Begin to write off file......" << endl;

	FILE* out = fopen(fn.toStdString().c_str(), "wb");
	if (out == NULL)
	{
		return false;
	}

	// write head information
	fprintf(out, "OFF\n");
	fprintf(out, "%d %d %d\n", pm->iNumVertex, pm->iNumFace, 0);

	// write vertex
	for (int i = 0; i < pm->iNumVertex; i++)
	{
		fprintf(out, "%f %f %f\n", pm->ptrVertex[i].x,
			pm->ptrVertex[i].y, pm->ptrVertex[i].z);
	}

	// write triangles
	int num = 3;
	for (int j = 0; j < pm->iNumFace; j++)
	{
		fprintf(out, "%d %d %d %d\n", num, pm->ptrFace[j].vIdx[0],
			pm->ptrFace[j].vIdx[1], pm->ptrFace[j].vIdx[2]);
	}

	// release resource
	fclose(out);
	qDebug() << "<<<<<<<< End of writing off file." << endl << endl;

	return true;
}

#endif //__FILEMANAGER_H
