// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if (OwnerComp.GetAIOwner() == nullptr) { UE_LOG(LogTemp,Warning,TEXT("1: no ai owner")) EBTNodeResult::Failed; }
	auto AIController = OwnerComp.GetAIOwner();
	if (AIController->GetPawn() == nullptr) { UE_LOG(LogTemp, Warning, TEXT("2: no get pawn")) return EBTNodeResult::Failed; }
	auto ControlledPawn = AIController->GetPawn();
	if (Cast<APatrollingGuard>(ControlledPawn) == nullptr) { UE_LOG(LogTemp, Warning, TEXT("3: no cast to guard")) return EBTNodeResult::Failed; }
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);

	auto PatrolPoints = PatrollingGuard->GetActorList();

	if (OwnerComp.GetBlackboardComponent() == nullptr) { UE_LOG(LogTemp, Warning, TEXT("4: no blackboard")) return EBTNodeResult::Failed; }
	 auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	 auto index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	 if (PatrolPoints[index] == nullptr) { UE_LOG(LogTemp, Warning, TEXT("5: no patrol point[0]")) return EBTNodeResult::Failed; }
		 BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[index]);
		 index += 1;
		 index %= PatrolPoints.Num();
		 BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, index);
	 return EBTNodeResult::Succeeded;
}


