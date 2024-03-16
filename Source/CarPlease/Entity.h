// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Processors.h"

/**
 * 
 */
class CARPLEASE_API Entity
{
public:
	Entity();
	~Entity();
	//virtual Processor;

	//virtual Processor GetProcessor();

	virtual bool IsDead();

	virtual float Fitness();
};
