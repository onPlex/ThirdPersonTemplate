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
    //�̵� �� ��ġ�� ����Ͽ� ���߿� �ǵ��� �� �ֵ��� ��.
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
