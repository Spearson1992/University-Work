#ifndef Node_h
#define Node_h
namespace AStar
{
    struct Node
        {
        public:
            static enum NodeType
            {
                Wall,
                Walkable,                
                Start,
                Goal,
                Path,
                Checked
            };

            static enum NodePos
            {
                Top,
                TopRight,
                Right,
                BottomRight,
                Bottom,
                BottomLeft,
                Left,
                TopLeft
            };

            
        
            void SetNeighbour(NodePos pos, Node* nodeIn);

            Node* const GetNeighbour(NodePos pos) const;

            inline void SetCost(int newCost)
            {_cost = newCost;}

            inline int GetCost() const
            {return _cost;}

            inline void SetTotalCost(int newCost)
            {_totalCost = newCost;}

            inline int GetTotalCost() const
            {return _totalCost;}

            inline NodeType GetType()
            {return this->_type;}

            inline void SetType(NodeType type)
            {this->_type = type;}

            inline void SetX(int x)
            {this->_x = x;}

            inline int GetX()
            {return _x;}

            inline void SetY(int y)
            {_y = y;}

            inline int GetY()
            {return _y;}

            inline Node* GetParent()
            {return _parent;}
            
            inline void SetParent(Node* parent)
            {this->_parent = parent;}

        private:
            //Pointers to each of the Node's neighbours
            //If any are null the node has no neighbour in that position
            Node *_topNeighbour;
            Node *_topRightNeighbour;
            Node *_rightNeighbour;
            Node *_bottomRightNeighbour;
            Node *_bottomNeighbour;
            Node *_bottomLeftNeighbour;
            Node *_leftNeighbour;
            Node *_topLeftNeighbour;

            //The cost to get to this Node from the start
            int _cost;
            //The total cost from here to the goal node
            int _totalCost;
            //Defines the type of the node e.g. walkable or a wall
            NodeType _type;
            //x and y position of the node in the grid
            int _x,_y;
            //parent node
            Node *_parent;
         };
}
#endif