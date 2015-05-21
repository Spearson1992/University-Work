#ifndef AStar_h
#define AStar_h

#include <vector>
#include "Node.h"
#include "Map.h"

namespace AStar
{
    class AStar : public Map
    {
    public:
        AStar(int columns, int rows);
        ~AStar(void);
        void CalculatePath();
        bool Save(wchar_t *filePath);
        AStar* Load(wchar_t *filePath);
    private:
        std::vector<Node*> openList;
        std::vector<Node*> closedList;
        bool OnClosedList(Node* test);
        bool OnOpenList(Node* test);
    };
}
#endif
