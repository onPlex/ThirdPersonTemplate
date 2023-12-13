// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveUnitCommand.h"

MoveUnitCommand::MoveUnitCommand(AUnit* unit, float x, float y)
{
    _unit = unit;
    _xBefore = 0;
    _yBefore = 0;
    _x = x;
    _y = y;
}

MoveUnitCommand::~MoveUnitCommand()
{

}

void MoveUnitCommand::Execute()
{
    //이동 전 위치를 기억하여 나중에 되돌릴 수 있도록 함.
    _xBefore = _unit->GetActorLocation().X;
    _yBefore = _unit->GetActorLocation().Y;

    FVector newLoc = FVector(_x,_y, _unit->GetActorLocation().Z);
    _unit->SetActorLocation(newLoc);
}

void MoveUnitCommand::Undo()
{
    FVector newLoc = FVector(_xBefore, _yBefore, _unit->GetActorLocation().Z);
    _unit->SetActorLocation(newLoc);
}
