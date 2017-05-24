// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if (OwnerComp.GetAIOwner()->GetPawn() == nullptr) { UE_LOG(LogTemp, Warning, TEXT("1: no get pawn")) return EBTNodeResult::Failed; }
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControlledPawn->FindComponentByClass<UPatrolRoute>() == nullptr) { UE_LOG(LogTemp, Warning, TEXT("2: no patrol route component")) return EBTNodeResult::Failed; }
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (PatrolRoute->GetActorList().Num() <= 0) { UE_LOG(LogTemp, Warning, TEXT("3: no actor list")) return EBTNodeResult::Failed; }
	auto PatrolPoints = PatrolRoute->GetActorList();

	 auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	 auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	 if (PatrolPoints[index] == nullptr) { UE_LOG(LogTemp, Warning, TEXT("4: no patrol point[0]")) return EBTNodeResult::Failed; }
		 BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[index]);
		 index += 1;
		 index %= PatrolPoints.Num();
		 BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index);
	 return EBTNodeResult::Succeeded;
}


