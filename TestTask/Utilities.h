#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <cmath>
#include <hge.h>

using namespace std;

const int mapSize = 20;

const float Pi = 3.14159265f;

const DWORD White = 0xFFFFFFFF;
const DWORD Orange = 0xFFFFA000;
const DWORD Black = 0x00000000;
const DWORD Red = 0xFFFF0000;
const DWORD Green = 0xFF00FF00;
const DWORD Blue = 0xFF0000FF;

struct Vector2
{
	float x;
	float y;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct iVector2
{
	int i;
	int j;
};

struct iVector3
{
	int i;
	int j;
	int k;
};

inline float DegToRad(float angle)
{
	return angle * Pi / 180.0f;
}

inline bool TestIndexValidity(const iVector2& index)
{
	return (index.i >= 0) && (index.i < mapSize) &&
		(index.j >= 0) && (index.j < mapSize);
}

inline float EuclideanLength(const Vector2& vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

inline float EuclideanLength(const Vector3& vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

namespace GraphFormat
{
	inline iVector2 NodeToIndex(void* node)
	{
		iVector2 result;

		int index = (int)node;
		result.j = index / mapSize;
		result.i = index - result.j * mapSize;

		return result;
	}

	inline void* IndexToNode(const iVector2& index)
	{
		return (void*)(index.j * mapSize + index.i);
	}
}
