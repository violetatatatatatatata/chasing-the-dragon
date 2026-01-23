#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "Node.h"

/**
 * 
 */
class TEST_SCP_API Graph
{

private:
  std::vector<Node*> nodes;
  Node* start;
  std::vector<Node*> exits;
  std::vector<Node*> rooms;
  std::vector<Node*> corridors;
  std::vector<Node*> stairs;
  int graphMultiplierX;
  int graphMultiplierY;
  int graphMultiplierZ;

  Node* GetNodeFromVector(FVector _pos, std::vector<Node*> _nodeContainer);

public:
	Graph();
  Graph(Grid* _grid);
	~Graph();

  std::vector<Node*> GetNodes();
  Node* GetCurrentNodePosition(FVector _target);
  std::vector<Node*> GetGoalNodes();
  std::vector<Node*> GetRoomsNode();
  std::vector<Node*> GetCorridors();
  std::vector<Node*> GetStairs();
  std::priority_queue<Node*, std::vector<Node*>, Node::OrderZ> stairsOrder;
  Node* GetStartNode();
  void ChangeWeight(FVector _target);
  void SetWeightFromCurrentNodePosition(FVector _target, float _weight = 100.0f);
  void SetInitialWeight();
  Node* GetComeFromNode(Node* _n);
  FVector Grid2World(FVector _grid);
  FVector* Grid2WorldPointer(FVector _grid);
  FVector World2Grid(FVector _world);
  void AddCorridorToVector(Node* _node);

  void Reset();

};