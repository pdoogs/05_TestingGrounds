// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	auto AIController = OwnerComp.GetAIOwner();
	auto PatrollingGuard = Cast<APatrollingGuard>(AIController->GetPawn());
	if (!ensure(PatrollingGuard)) return EBTNodeResult::Failed;

	// Get Patrol Points
	auto PatrolPoints = PatrollingGuard->GetPatrolPoints();
	if (!ensure(Index >= 0 && Index < PatrolPoints.Num())) return  EBTNodeResult::Failed;

	// Set Next Waypoint
	auto PatrolActor = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle Index
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}