// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<AActor*> PatrolPoints;

public:
	const TArray<AActor*> & GetPatrolPoints() const { return PatrolPoints; }

		
	
};