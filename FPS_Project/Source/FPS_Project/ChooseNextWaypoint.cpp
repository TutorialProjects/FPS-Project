// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UE_LOG(LogTemp,Warning,TEXT("AI: IM GAY LOLZ!"))
	return EBTNodeResult::Succeeded;
}
