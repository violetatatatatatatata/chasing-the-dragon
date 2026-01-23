

Graph::Graph(Grid* _grid)
: graphMultiplierX(_grid->GetGridMultiplierX()), graphMultiplierY(_grid->GetGridMultiplierY()), graphMultiplierZ(_grid->GetGridMultiplierZ())
{
  std::vector<Node*> tmpNodesContainer;
  // Crear primero la lista y rellenarla con los nodos
  for (int i = 0; i < _grid->GetWidth(); i++)
  {
    for (int j = 0; j < _grid->GetHeight(); j++)
    {
      for (int z = 0; z < _grid->GetDepth(); z++)
      {
        if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z)))
        {
          Node* tmpNodeStart = new Node(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z),
            _grid->Weight(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z)),
            _grid->Weight(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z)));
          tmpNodesContainer.push_back(tmpNodeStart);
        }
      }
    }
  }

  // Coger los nodos vecinos y meterlos como vecinos del nodo que se esta mirando
  for (int i = 0; i < _grid->GetWidth(); i++)
  {
    for (int j = 0; j < _grid->GetHeight(); j++)
    {
      for (int z = 0; z < _grid->GetDepth(); z++)
      {
        if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z))) // NODO ACTUAL
        {
          Node* tmpNeighboursNode;
          std::vector<Node*> tmpNeighboursNodes;

          ///// RIGHT 
          if (_grid->IsValidCell(FVector((unsigned int)i - 1, (unsigned int)j, (unsigned int)z))) // RIGHT
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i - 1, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// CENTER
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j - 1, (unsigned int)z))) // DOWN
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j - 1, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j + 1, (unsigned int)z))) // UP
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j + 1, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// LEFT
          if (_grid->IsValidCell(FVector((unsigned int)i + 1, (unsigned int)j, (unsigned int)z))) // LEFT
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i + 1, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// UP
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z + 1))) // UP
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z + 1), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// DOWN
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z - 1))) // DOWN
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z - 1), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

		  // Tras tener un nodo construido con sus vecinos se mete en la lista final de nodos
          GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer)->neighbours = tmpNeighboursNodes;
          nodes.push_back(GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer));
          Node* tmpNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
		  // Esto es por tener listas de nodos concretos como paredes
          switch (_grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z)))
          {
          case Node::NodeTypes::START:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            start = tmpNode;
            break;
          case Node::NodeTypes::EXIT:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            exits.push_back(tmpNode);
            break;
          case Node::NodeTypes::ROOM:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            rooms.push_back(tmpNode);
            break;
          case Node::NodeTypes::STAIRS:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            stairsOrder.push(tmpNode);
            break;
          default:
            break;
          }
        }
        else // En caso de no ser un nodo valido
        {
          Node* tmpNeighboursNode;
          std::vector<Node*> tmpNeighboursNodes;

          ///// RIGHT 
          if (_grid->IsValidCell(FVector((unsigned int)i - 1, (unsigned int)j, (unsigned int)z))) // RIGHT
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i - 1, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// CENTER
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j - 1, (unsigned int)z))) // DOWN
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j - 1, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j + 1, (unsigned int)z))) // UP
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j + 1, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// LEFT
          if (_grid->IsValidCell(FVector((unsigned int)i + 1, (unsigned int)j, (unsigned int)z))) // LEFT
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i + 1, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// UP
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z + 1))) // UP
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z + 1), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          ///// DOWN
          if (_grid->IsValidCell(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z - 1))) // DOWN
          {
            tmpNeighboursNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z - 1), tmpNodesContainer);
            tmpNeighboursNodes.push_back(tmpNeighboursNode);
          }

          GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer)->neighbours = tmpNeighboursNodes;
          nodes.push_back(GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer));
          Node* tmpNode = GetNodeFromVector(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z), tmpNodesContainer);
          switch (_grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z)))
          {
          case Node::NodeTypes::START:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            start = tmpNode;
            break;
          case Node::NodeTypes::EXIT:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            exits.push_back(tmpNode);
            break;
          case Node::NodeTypes::ROOM:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            rooms.push_back(tmpNode);
            break;
          case Node::NodeTypes::STAIRS:
            tmpNode->nodeType = _grid->GetCellType(FVector((unsigned int)i, (unsigned int)j, (unsigned int)z));
            stairsOrder.push(tmpNode);
            break;
          default:
            break;
          }
        }
      }
    }
  }
  while (!stairsOrder.empty())
  {
    stairs.push_back(stairsOrder.top());
    stairsOrder.pop();
  }
  for (int i = 1; i < _grid->GetDepth() - 1; i++)
  {
    if (!(stairs[i + (i - 1)]->pos.X == stairs[i + (i - 2)]->pos.X && stairs[i + (i - 1)]->pos.Y == stairs[i + (i - 2)]->pos.Y)) ////ESTA MAL LAS COMPARACIONES EN EL SEGUNDO
      std::swap(stairs[i + (i - 1)], stairs[i * 2]);
  }
}

Graph::~Graph()
{
  nodes.clear();
}

std::vector<Node*> Graph::GetNodes()
{
  return nodes;
}

Node* Graph::GetCurrentNodePosition(FVector _target)
{
  for (Node* currentNode : nodes)
  {
    if (currentNode->pos == _target)
    {
      return currentNode;
    }
  }
  return nullptr;
}

std::vector<Node*> Graph::GetGoalNodes()
{
  return exits;
}

std::vector<Node*> Graph::GetRoomsNode()
{
  return rooms;
}

std::vector<Node*> Graph::GetCorridors()
{
  return corridors;
}

std::vector<Node*> Graph::GetStairs()
{
  return stairs;
}

Node* Graph::GetStartNode()
{
  return start;
}

void Graph::ChangeWeight(FVector _target)
{
  Node* currentNode = GetCurrentNodePosition(_target);
  currentNode->weight = 100;

  for (Node* neighbour : currentNode->neighbours)
  {
    SetWeightFromCurrentNodePosition(GetCurrentNodePosition(neighbour->pos)->pos);
  }
}

void Graph::SetWeightFromCurrentNodePosition(FVector _target, float _weight)
{
  for (Node* currentNode : nodes)
  {
    if (currentNode->pos == _target)
    {
      currentNode->weight = _weight;
    }
  }
}

void Graph::SetInitialWeight()
{
  for (Node* n : nodes)
  {
    n->weight = n->initialWeight;
  }
}

Node* Graph::GetComeFromNode(Node* _n)
{
  return _n->comeFrom;
}

FVector Graph::Grid2World(FVector _grid)
{
  return FVector(_grid.X * graphMultiplierX, _grid.Y * graphMultiplierY, _grid.Z * graphMultiplierZ);
}

FVector* Graph::Grid2WorldPointer(FVector _grid)
{
  return new FVector(_grid.X * graphMultiplierX, _grid.Y * graphMultiplierY, _grid.Z * graphMultiplierZ);
}

FVector Graph::World2Grid(FVector _world)
{
  return FVector((double)(int)_world.X / graphMultiplierX, (double)(int)_world.Y / graphMultiplierY, (double)(int)_world.Z / graphMultiplierZ);
}

void Graph::AddCorridorToVector(Node* _node)
{
  if (_node->nodeType != Node::NodeTypes::CORRIDOR && _node->nodeType == Node::NodeTypes::NONE)
  {
    _node->nodeType = Node::NodeTypes::CORRIDOR;
    corridors.push_back(_node);
  }
}

void Graph::Reset()
{
  for (Node* node : nodes)
  {
    node->comeFrom = nullptr;
    node->costSoFar = 0;
    node->heuristic = 0;
    node->priority = 0;
    node->weight = node->initialWeight;
  }
}
