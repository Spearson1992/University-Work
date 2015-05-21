
#include "..\stdafx.h"
#include <fstream>
#include <iostream>


namespace AStar
{
    Map::Map(int columns, int rows)
        :_columns(columns), _rows(rows), _size(columns * rows)
    {
        map = new Node[columns*rows];
        this->_startNode = NULL;
        this->_goalNode = NULL;
        for(int i = 0; i < _size; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                map[i].SetNeighbour((Node::NodePos) j, NULL);
            }
            map[i].SetType((Node::NodeType) 1);
            map[i].SetCost(0);
            map[i].SetTotalCost(0);
            map[i].SetParent(NULL);
        }
        for(int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                map[i*columns + j].SetX(j);
                map[i*columns + j].SetY(i);
            }
        }
        CalculateNeighbours();
        std::ofstream myStream;
        myStream.open("Log.txt");
        for(int i = 0; i < _size; i++)
        {
            myStream << map[i].GetX() << map[i].GetY() << std::endl;
            for(int j = 0; j < 8; j++)
            {
                if(map[i].GetNeighbour((Node::NodePos) j))
                myStream <<"Neighbour " << j <<"X: " << map[i].GetNeighbour((Node::NodePos) j)->GetX() <<" Y: " << map[i].GetNeighbour((Node::NodePos) j)->GetY() << std::endl;
            }
        }
        myStream.close();
    }


    Map::~Map()
    {
        delete [] map;
    }

    void Map::CalculateNeighbours()
    {
        typedef Node::NodePos NodePos;
        
        for (int i = 0; i < _rows; i++)
        {
            for(int j = 0; j < _columns; j++)
            {
                if(i == 0 && j == 0)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomRight, map + (((i+1)*_columns) + (j+1)));
                }
                else if (i == 0 && j < _columns-1)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomLeft, map + (((i+1) * _columns)+(j-1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomRight, map + (((i+1)*_columns) + (j+1)));
                }
                else if(i == 0 && j == _columns -1)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomLeft, map + (((i+1) * _columns)+(j-1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                }
                else if(i ==  _rows -1 && j ==0)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopRight, map+(((i-1)*_columns)+(j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                }
                else if(i == _rows -1 && j == _columns -1)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::TopLeft, map+(((i-1)*_columns)+(j-1)));                  
                }
                else if (i == _rows -1 && j < _columns -1)
                {
                    
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopRight, map+(((i-1)*_columns)+(j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::TopLeft, map+(((i-1)*_columns)+(j-1)));
                }
                else if(j ==0)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopRight, map+(((i-1)*_columns)+(j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomRight, map + (((i+1)*_columns) + (j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                }
                else if (i == _rows - 1)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopLeft, map+(((i-1)*_columns)+(j-1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::TopRight, map+(((i-1)*_columns)+(j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                }
                else if( j == _columns - 1)
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopLeft, map+(((i-1)*_columns)+(j-1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                    map[i * _columns + j].SetNeighbour(NodePos::BottomLeft, map + (((i+1) * _columns)+(j-1)));
                }
                else
                {
                    map[i * _columns + j].SetNeighbour(NodePos::Top, map+((i-1)*_columns)+j);
                    map[i * _columns + j].SetNeighbour(NodePos::TopRight, map+(((i-1)*_columns)+(j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Right, map+(i*_columns)+(j+1));
                    map[i * _columns + j].SetNeighbour(NodePos::BottomRight, map + (((i+1)*_columns) + (j+1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Bottom, map+((i+1)*_columns) + j);
                    map[i * _columns + j].SetNeighbour(NodePos::BottomLeft, map + (((i+1) * _columns)+(j-1)));
                    map[i * _columns + j].SetNeighbour(NodePos::Left, map+(i *_columns)+(j-1));
                    map[i * _columns + j].SetNeighbour(NodePos::TopLeft, map+(((i-1)*_columns)+(j-1)));
                }
            }
        }
    }
    void Map::Clear()
    {
        for(int i = 0; i < _size; i++)
        {
            if(map[i].GetType() != Node::NodeType::Wall &&
                map[i].GetType() != Node::NodeType::Goal &&
                map[i].GetType() != Node::NodeType::Start)
            {
                map[i].SetType((Node::NodeType) 1);
            }
            map[i].SetCost(0);
            map[i].SetTotalCost(0);
            map[i].SetParent(NULL);
        }
    }
}
