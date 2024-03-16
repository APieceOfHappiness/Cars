// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

bool Entity::IsDead()
{
	return false;
}

float Entity::Fitness()
{
	return -1.0f;
}
