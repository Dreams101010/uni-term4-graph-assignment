#ifndef H_GraphNode
#define H_GraphNode

#include <optional>

enum GraphNodeColor { WHITE, GRAY, BLACK };

struct GraphNode
{
	int index;
	GraphNodeColor color = WHITE;
	std::optional<int> parentIndex = std::optional<int>();
	std::optional<int> distanceFromRoot = std::optional<int>();
};

#endif // !1