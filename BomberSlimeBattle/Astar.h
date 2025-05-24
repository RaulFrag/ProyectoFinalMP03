#pragma once
#include <vector>
#include <queue>
#include <map>
#include <memory>
#include <cmath>
#include <algorithm>

class Astar {
public:
    Astar(int width, int height, const std::vector<int>& map);
    std::vector<std::pair<int, int>> findPath(std::pair<int, int> start, std::pair<int, int> goal);

private:
    struct Node {
        int x, y;
        int g, h;
        Node* parent;

        int f() const { return g + h; }

        bool operator==(const Node& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Comparator {
        bool operator()(const Node* a, const Node* b) const {
            return a->f() > b->f();
        }
    };

    int width, height;
    std::vector<int> map;

    int heuristic(int x1, int y1, int x2, int y2) const;
    bool isValid(int x, int y, int width, int height) const;
    std::vector<std::unique_ptr<Node>> allNodes;
    std::vector<Node*> getNeighbors(Node* current);
};

