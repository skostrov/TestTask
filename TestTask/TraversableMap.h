#pragma once

#include "Utilities.h"
#include "Map.h"
#include "micropather.h"


class TraversableMap : public Map, public micropather::Graph
{

public:

	TraversableMap(HTEXTURE texture);
	~TraversableMap();

private:

	float LeastCostEstimate(void* startNode, void* finishNode) override;
	void AdjacentCost(void* node, std::vector<micropather::StateCost>* adjacent) override;
	void PrintStateInfo(void* node) override;

};

