// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNewWaypoint.h"
#include "PatrolComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/AIModule/Classes/AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNewWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto PatrolComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolComponent>();

	if (!ensure(PatrolComponent)) { return EBTNodeResult::Failed; }


	auto PatrolPoints = PatrolComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) { UE_LOG(LogTemp, Warning, TEXT("no patrol point selected on a PatrolComponent")) }

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	//TODO proytect against empty patropoints
		return EBTNodeResult::Succeeded;
}
