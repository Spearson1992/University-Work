
#include "..\stdafx.h"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>


namespace AStar
{
    AStar::AStar(int columns, int rows)
        :Map(columns,rows)
    {
        openList = std::vector<Node*>();
        closedList = std::vector<Node*>();
        
    }


    AStar::~AStar(void)
    {
    }
    void AStar::CalculatePath()
    {
        if(_startNode == nullptr || _goalNode == nullptr)
            return;
        this->Clear();
        Node *currentNode = _startNode;
        closedList.push_back(_startNode);
        while(true)
        {
            //Draw path and checked node if goal is found
            if(currentNode == _goalNode)
            {
                closedList.push_back(currentNode);
                Node* temp = currentNode;
                for(unsigned int i = 0; i < closedList.size(); i++)
                {
                    if(closedList.at(i)->GetType() != Node::NodeType::Start &&
                        closedList.at(i)->GetType() != Node::NodeType::Goal)
                    {
                        closedList.at(i)->SetType(Node::NodeType::Checked);
                    }
                }
                while (currentNode->GetParent() != nullptr)
                {
                    if(currentNode == _goalNode)
                    {
                        currentNode = currentNode->GetParent();
                        continue;
                    }
                    currentNode->SetType(Node::NodeType::Path);
                    currentNode = currentNode->GetParent();
                    
                }
                openList.clear();
                closedList.clear();
                break;
            }
			//perform neighbour checking
            for(int i = 0; i < 8; i++)
            {
                if(currentNode->GetNeighbour((Node::NodePos) i) != nullptr
                    && currentNode->GetNeighbour((Node::NodePos) i)->GetType() != Node::NodeType::Wall &&
                    (i == Node::NodePos::BottomLeft ||
                    i == Node::NodePos::BottomRight ||
                    i == Node::NodePos::TopLeft ||
                    i == Node::NodePos::TopRight)
                    && !OnClosedList(currentNode->GetNeighbour((Node::NodePos) i)))
                {
                    Node *temp = currentNode->GetNeighbour((Node::NodePos) i);
                    if(OnOpenList(temp))
                    {
                        if(temp->GetCost() > (currentNode->GetCost()+14))
                        {
                            temp->SetParent(currentNode);
                            temp->SetCost(currentNode->GetCost() + 14);
                            temp->SetTotalCost((currentNode->GetCost() + 14) + 
                                               (abs(temp->GetX() - this->GetGoal()->GetX()) * 10 + 
                                               (abs(temp->GetY() - this->GetGoal()->GetY())) * 10));

                        }
                    }
                    else
                    {
                        temp->SetParent(currentNode);
                        temp->SetCost(currentNode->GetCost() + 14);
                        temp->SetTotalCost((currentNode->GetCost() + 14) + 
                            (abs(temp->GetX() - this->GetGoal()->GetX()) * 10 + 
                            (abs(temp->GetY() - this->GetGoal()->GetY())) * 10));
						if(currentNode->GetType() != Node::NodeType::Start)
						{
							if(currentNode->GetParent() == currentNode->GetNeighbour(Node::NodePos::BottomLeft) &&
								(currentNode->GetNeighbour(Node::NodePos::Bottom) != NULL &&
								 currentNode->GetNeighbour(Node::NodePos::Left) != NULL) &&
								(currentNode->GetNeighbour(Node::NodePos::Bottom)->GetType() != Node::NodeType::Wall &&
								 currentNode->GetNeighbour(Node::NodePos::Left)->GetType() != Node::NodeType::Wall))
							{
								openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
							}
							else if (currentNode->GetParent() == currentNode->GetNeighbour(Node::NodePos::BottomRight) &&
								(currentNode->GetNeighbour(Node::NodePos::Bottom) != NULL &&
								 currentNode->GetNeighbour(Node::NodePos::Right) != NULL) &&
								(currentNode->GetNeighbour(Node::NodePos::Right)->GetType() != Node::NodeType::Wall &&
								 currentNode->GetNeighbour(Node::NodePos::Bottom)->GetType() != Node::NodeType::Wall))
							{
								openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
							}
							else if (currentNode->GetParent() == currentNode->GetNeighbour(Node::NodePos::TopLeft) &&
								(currentNode->GetNeighbour(Node::NodePos::Top) != NULL &&
								 currentNode->GetNeighbour(Node::NodePos::Left) != NULL) &&
								(currentNode->GetNeighbour(Node::NodePos::Top)->GetType() != Node::NodeType::Wall &&
								 currentNode->GetNeighbour(Node::NodePos::Left)->GetType() != Node::NodeType::Wall))
							{
								openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
							}
							else if (currentNode->GetParent() == currentNode->GetNeighbour(Node::NodePos::TopRight) &&
								(currentNode->GetNeighbour(Node::NodePos::Top) != NULL &&
								 currentNode->GetNeighbour(Node::NodePos::Right) != NULL) &&
								(currentNode->GetNeighbour(Node::NodePos::Top)->GetType() != Node::NodeType::Wall &&
								 currentNode->GetNeighbour(Node::NodePos::Right)->GetType() != Node::NodeType::Wall))
							{
								openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
							}
						}
						else
						{
							openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
						}
						//openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
                    }
                }
                else if(currentNode->GetNeighbour((Node::NodePos) i) != nullptr
                && currentNode->GetNeighbour((Node::NodePos) i)->GetType() != Node::NodeType::Wall
                && !OnClosedList(currentNode->GetNeighbour((Node::NodePos) i)))
                {
                     Node *temp = currentNode->GetNeighbour((Node::NodePos) i);
                    if(OnOpenList(temp))
                    {
                        if(temp->GetCost() > (currentNode->GetCost()+10))
                        {
                            temp->SetParent(currentNode);
                            temp->SetCost(currentNode->GetCost() + 10);
                            temp->SetTotalCost((currentNode->GetCost() + 10) + 
                                               (abs(temp->GetX() - this->GetGoal()->GetX()) * 10 + 
                                               (abs(temp->GetY() - this->GetGoal()->GetY())) * 10));

                        }
                    }
                    else
                    {
                        temp->SetParent(currentNode);
                        temp->SetCost(currentNode->GetCost() + 10);
                        temp->SetTotalCost((currentNode->GetCost() + 10) + 
                            (abs(temp->GetX() - this->GetGoal()->GetX()) * 10 + 
                            (abs(temp->GetY() - this->GetGoal()->GetY())) * 10));

                        openList.push_back(currentNode->GetNeighbour((Node::NodePos) i));
                    }
                }
            }
            if(openList.size() == 0)
            {
                openList.clear();
                closedList.clear();
                return;
            }
            //Lambda sort expression http://stackoverflow.com/questions/8121837/sorting-a-list-of-a-custom-type
            std::sort(openList.begin(), openList.end(),[] (Node *a, Node *b) { return a->GetTotalCost() < b->GetTotalCost();});
            currentNode = openList.front();
            openList.erase(openList.begin());
            closedList.push_back(currentNode);
            
            
        }
    }
    bool AStar::OnClosedList(Node* test)
    {
        for(unsigned int i = 0; i < closedList.size(); i++)
        {
            if(test == closedList.at(i))
                return true;
        }
        return false;
    }
    bool AStar::OnOpenList(Node* test)
    {
        for(unsigned int i = 0; i < openList.size(); i++)
        {
            if(test == openList.at(i))
                return true;
        }
        return false;
    }
    //returns a pointer to a new AStar object
    AStar* AStar::Load(wchar_t *filePath)
    {
        std::wifstream lFile;
        lFile.open(filePath);
        if(lFile.is_open())
        {
            if(lFile.good())
            {
                std::wstringstream temp;
                lFile >> temp.rdbuf();
                int rows = 0, columns = 0;
                temp >> rows;
                temp >> columns;
                AStar *newA = new AStar(columns, rows);

                for(int i = 0; i < newA->GetSize(); i++)
                {
                    int type;
                    temp >> type;
                    if(type == Node::NodeType::Checked ||
                        type == Node::NodeType::Goal ||
                        type == Node::NodeType::Path ||
                        type == Node::NodeType::Start)
                    {
                        type = 1;
                    }
                    newA->GetNode(i)->SetType((Node::NodeType) type);
                }
                return newA;
            }
        }
        return false;
    }
    bool AStar::Save(wchar_t *filePath)
    {
        std::wofstream lFile;
        lFile.open(filePath);
        if(lFile.is_open())
        {
            if(lFile.good())
            {
                lFile << _rows << " ";
                lFile << _columns << " ";
                for(int i = 0; i < _size; i++)
                {
                    lFile << map[i].GetType() << " ";
                }
                lFile.close();
                return true;
            }
        }
        return false;
    }
}
