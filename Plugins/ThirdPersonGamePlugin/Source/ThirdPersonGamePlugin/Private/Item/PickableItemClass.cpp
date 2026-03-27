// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickableItemClass.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInteractInterface.h"
#include "Components/WorldObjectInteractableDetectionComponent.h"
#include "Character//PlayerCharacter.h"

APickableItemClass::APickableItemClass()
{
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	itemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = itemMesh;

	interactableDetectionComponent = CreateDefaultSubobject<UWorldObjectInteractableDetectionComponent>(TEXT("InteractableDetectionComponent"));
	interactableDetectionComponent->SetupAttachment(RootComponent);

	interactableDetectionComponent->interactDetectionSphere->SetupAttachment(RootComponent);
	bReplicates = true;
}

void APickableItemClass::BeginPlay()
{
	Super::BeginPlay();
}

void APickableItemClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	itemFloatingRunningTimeFloat += DeltaTime;

	AddActorWorldOffset(FVector(0.f, 0.f, TransformSin()));
	AddActorWorldRotation(itemFloatingAmplitude * FRotator(itemFloatingRotationRate * DeltaTime));
}

float APickableItemClass::TransformSin()
{
	return itemFloatingAmplitude * FMath::Sin(itemFloatingRunningTimeFloat * itemFloatingTimeConstant);
}

void APickableItemClass::Interact(APlayerCharacter* interactedPlayer)
{
	if (!interactedPlayer)
		return;

	//// ✅ VERY IMPORTANT: only local player sends request
	//if (!interactedPlayer->IsLocallyControlled())
	//	return;

	UE_LOG(LogTemp, Warning, TEXT("Item is being Picked up"));
	interactedPlayer->Server_RequestPickup(this);
}

void APickableItemClass::OverlapWithPlayer()
{

}

void APickableItemClass::ItemPickedUp()
{
	if (!HasAuthority())
		return;

	interactableDetectionComponent->playerPickUpInterface->RemoveInteractableFromPlayerRange(this);
	this->Destroy();
}
