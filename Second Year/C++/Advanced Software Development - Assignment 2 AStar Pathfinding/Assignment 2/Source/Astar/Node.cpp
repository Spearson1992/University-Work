#include "..\stdafx.h"

namespace AStar
{

    Node* const Node::GetNeighbour(Node::NodePos pos) const
    {
        switch (pos)
        {
        case Node::Top:
            return this->_topNeighbour;
            break;
        case Node::TopRight:
            return this->_topRightNeighbour;
            break;
        case Node::Right:
            return this->_rightNeighbour;
            break;
        case Node::BottomRight:
            return this->_bottomRightNeighbour;
            break;
        case Node::Bottom:
            return this->_bottomNeighbour;
            break;
        case Node::BottomLeft:
            return this->_bottomLeftNeighbour;
            break;
        case Node::Left:
            return this->_leftNeighbour;
            break;
        case Node::TopLeft:
            return this->_topLeftNeighbour;
            break;
        default:
            return nullptr;
            break;
        }
    }
    void Node::SetNeighbour(Node::NodePos pos, Node* nodeIn)
    {
        switch (pos)
        {
        case Node::Top:
            this->_topNeighbour = nodeIn;
            break;
        case Node::TopRight:
            this->_topRightNeighbour = nodeIn;
            break;
        case Node::Right:
            this->_rightNeighbour = nodeIn;
            break;
        case Node::BottomRight:
            this->_bottomRightNeighbour = nodeIn;
            break;
        case Node::Bottom:
            this->_bottomNeighbour = nodeIn;
            break;
        case Node::BottomLeft:
            this->_bottomLeftNeighbour = nodeIn;
            break;
        case Node::Left:
            this->_leftNeighbour = nodeIn;
            break;
        case Node::TopLeft:
            this->_topLeftNeighbour = nodeIn;
            break;
        default:
            break;
        }
    }
}