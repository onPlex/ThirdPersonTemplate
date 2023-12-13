// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Command.h"
#include "Unit.h"
#include "CoreMinimal.h"

/**
 * 
 */
class THIRDPERSONTEMPLATE_API MoveUnitCommand : public Command
{
public:
	MoveUnitCommand(AUnit* unit, float x, float y);
	~MoveUnitCommand();

public:

	virtual void Execute() override;
	virtual void Undo() override;

private:

    class AUnit* _unit;
	float _xBefore, _yBefore;
	float _x, _y;
};
