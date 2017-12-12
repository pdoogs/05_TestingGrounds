// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO protect against empty patrol routes

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController->GetPawn())) { return EBTNodeResult::Failed; }

	auto PatrolRoute = AIController->GetPawn()->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) return EBTNodeResult::Failed;

	// Get Patrol Points
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (!ensure(Index >= 0 && Index < PatrolPoints.Num())) return  EBTNodeResult::Failed;

	// Set Next Waypoint
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle Index
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}