#include "pch.h"
#include "Player.h"

#include "AStarAI.h"
#include "BFSAI.h"
#include "RightHandAI.h"

using namespace std;

Player::~Player() {
    delete pathFindingAI;
}

void Player::Initialize(PathFindingType type) {
    if(PathFindingType::RightHand == type) {
        pathFindingAI = new RightHandAI();
    }
    if (PathFindingType::BFS == type) {
        pathFindingAI = new BFSAI();
    }
    if (PathFindingType::AStar == type) {
        pathFindingAI = new AStarAI();
    }

    _points = pathFindingAI->FindPath();
}

void Player::Update() {
    if(!_points.empty()) {
        posX = _points.back().x;
        posY = _points.back().y;

        _points.pop_back();
    }
}