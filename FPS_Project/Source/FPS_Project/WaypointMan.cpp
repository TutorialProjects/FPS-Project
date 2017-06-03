// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_Project.h"
#include "WaypointMan.h"
#include "Gun.h"


// Sets default values
AWaypointMan::AWaypointMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ChildRef_Gun = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActorRef_Gun"));
	ChildRef_Gun->SetupAttachment(GetMesh(),TEXT("GripPoint_Rotated"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Mr. Spring"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("T3H CaM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 0.f;
	CameraComp->SetupAttachment(SpringArm);
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->FieldOfView = 90.f;
	GunActor = Cast<AGun>(ChildRef_Gun->GetChildActor());


}

// Called when the game starts or when spawned
void AWaypointMan::BeginPlay()
{
	Super::BeginPlay();
	SpringArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("HeadPoint"));
	ChildRef_Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint_Rotated"));
	if (GunActor == nullptr){ GunActor = Cast<AGun>(ChildRef_Gun->GetChildActor()); }
	if (GunActor != nullptr) { GunActor->AnimInstance = GetMesh()->GetAnimInstance();}
	if (InputComponent != NULL) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AWaypointMan::PullTrigger);
	}
	
}

// Called every frame
void AWaypointMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWaypointMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//GrabbedInputComponent = PlayerInputComponent;

}

void AWaypointMan::PullTrigger() {
	if (!GunActor) { return; }
	GunActor->OnFire();

}
