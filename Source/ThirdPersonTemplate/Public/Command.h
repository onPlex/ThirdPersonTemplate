// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class THIRDPERSONTEMPLATE_API Command
{
public:
	Command();
	~Command();

public: 
    virtual void Execute() = 0;
	virtual void Undo() = 0;
};
