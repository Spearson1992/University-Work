#ifndef Map_h
#define Map_h
namespace AStar
{
    
    class Map
    {
    protected:
        //Do not delete any Objects this array points to it takes care of it's own memory mangement
        Node* map;
        int _columns, _rows, _size;
        Node *_startNode, *_goalNode;
        void CalculateNeighbours();
    public:
        Map(int columns, int rows);
        ~Map();
        
        void Clear();
        inline void SetStart(Node* start) { _startNode = start;}
        inline void SetGoal(Node* goal) { _goalNode = goal;}
        inline Node* GetStart() {return _startNode;}
        inline Node* GetGoal() {return _goalNode;}
        inline int GetSize() {return _size;}
        inline Node* GetNode(int i) {return map+i;}
        inline int GetColumns() {return _columns;}
        inline int GetRows() {return _rows;}
    };
}
#endif
