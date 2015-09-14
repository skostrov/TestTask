#include "TraversableMap.h"


TraversableMap::TraversableMap(const iVector2& finishPos_, HTEXTURE texture) : Map(finishPos_, texture)
{
}


TraversableMap::~TraversableMap()
{
}

float TraversableMap::LeastCostEstimate(void* startNode, void* finishNode)
{
	iVector2 startTile = GraphFormat::NodeToIndex(startNode);
	iVector2 finishTile = GraphFormat::NodeToIndex(finishNode);

	iVector2 distance = { startTile.i - finishTile.i, startTile.j - finishTile.j };

	return (float)sqrt((float)(distance.i * distance.i) + (float)(distance.j * distance.j));
}

void TraversableMap::AdjacentCost(void* node, std::vector<micropather::StateCost>* adjacent)
{
	iVector2 index = GraphFormat::NodeToIndex(node);

	const iVector2 moves[8] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 },					// Всевозможные направления движений
	{ -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };											// на клетчатой доске

	const float cost[8] = { 1, FLT_MAX, 1, FLT_MAX, 1, FLT_MAX, 1, FLT_MAX };				// Стоимость движения в каждом из
																							// направлений (переходы по диагонали
																							// запрещены)

	for (int k = 0; k < 8; ++k)
	{
		iVector2 neighborIndex = { index.i + moves[k].i, index.j + moves[k].j };

		if ((neighborIndex.i < 0) || (neighborIndex.i >= mapSize) ||						// Тайлы за пределами карты и занятые
			(neighborIndex.j < 0) || (neighborIndex.j >= mapSize) ||						// тайлы также недоступны для перехода
			(grid[neighborIndex.i][neighborIndex.j].IsBlocked()))
		{
			micropather::StateCost nodeCost = { GraphFormat::IndexToNode({ neighborIndex.i, neighborIndex.j }), FLT_MAX };
			adjacent->push_back(nodeCost);
		}
		else
		{
			micropather::StateCost nodeCost = { GraphFormat::IndexToNode({ neighborIndex.i, neighborIndex.j }), cost[k] };
			adjacent->push_back(nodeCost);
		}
	}
}

void TraversableMap::PrintStateInfo(void* node)
{
}

