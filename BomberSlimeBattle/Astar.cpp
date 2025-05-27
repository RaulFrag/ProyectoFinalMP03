#include "Astar.h"

Astar::Astar(int width, int height, const std::vector<int>& map)
    : width(width), height(height), map(map) {}

int Astar::heuristic(int x1, int y1, int x2, int y2) const {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

bool Astar::isValid(int x, int y, int width, int height) const {
    return x >= 0 && x < width&& y >= 0 && y < height;
}

std::vector<Astar::Node*> Astar::getNeighbors(Node* current) {
    std::vector<Node*> neighbors;
    std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    for (const auto& dir : directions) {
        int nx = current->x + dir.first;
        int ny = current->y + dir.second;

        if (isValid(nx, ny, 20, 20)) {
            auto node = std::make_unique<Node>();
            node->x = nx;
            node->y = ny;
            node->g = 0;
            node->h = 0;
            node->parent = current;
            allNodes.push_back(std::move(node));
            neighbors.push_back(allNodes.back().get());
        }
    }
    return neighbors;
}

std::vector<std::pair<int, int>> Astar::findPath(std::pair<int, int> start, std::pair<int, int> goal) {
    allNodes.clear();

    std::priority_queue<Node*, std::vector<Node*>, Comparator> openList;
    std::map<std::pair<int, int>, int> visitedCost;

    auto startNode = std::make_unique<Node>();
    startNode->x = start.first;
    startNode->y = start.second;
    startNode->g = 0;
    startNode->h = heuristic(start.first, start.second, goal.first, goal.second);
    startNode->parent = nullptr;

    openList.push(startNode.get());
    allNodes.push_back(std::move(startNode));

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal.first && current->y == goal.second) {
            std::vector<std::pair<int, int>> path;
            while (current) {
                path.emplace_back(current->x, current->y);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto neighbors = getNeighbors(current);
        for (auto neighbor : neighbors) {
            neighbor->g = current->g + 1;
            neighbor->h = heuristic(neighbor->x, neighbor->y, goal.first, goal.second);

            auto pos = std::make_pair(neighbor->x, neighbor->y);
            if (visitedCost.count(pos) == 0 || neighbor->g < visitedCost[pos]) {
                visitedCost[pos] = neighbor->g;
                openList.push(neighbor);
            }
        }
    }

    return {};
}
