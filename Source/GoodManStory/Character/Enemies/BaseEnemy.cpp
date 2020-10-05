// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "Components/SphereComponent.h"

ABaseEnemy::ABaseEnemy() noexcept
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(ABaseCharacter::CollisionComponentName);    
	RootComponent = CollisionComponent;
	
	MeshComponent->SetupAttachment(RootComponent);
}
