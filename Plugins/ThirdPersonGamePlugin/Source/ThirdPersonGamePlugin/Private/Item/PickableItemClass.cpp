// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickableItemClass.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInteractInterface.h"

APickableItemClass::APickableItemClass()
{
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	itemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = itemMesh;

	detectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	detectionSphere->SetSphereRadius(detectionRange);
	detectionSphere->SetupAttachment(RootComponent);
}

void APickableItemClass::BeginPlay()
{
	Super::BeginPlay();

	detectionSphere->SetSphereRadius(detectionRange);

	detectionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickableItemClass::OnOverlapBegin);
	detectionSphere->OnComponentEndOverlap.AddDynamic(this, &APickableItemClass::OnOverlapEnd);
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

void APickableItemClass::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Item is being Picked up"));
	ItemPickedUp();
}

void APickableItemClass::OverlapWithPlayer()
{

}

void APickableItemClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->IsInteractableWithinPlayerFov(this);
	}
}

void APickableItemClass::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->RemoveInteractableFromPlayerRange(this);
		playerPickUpInterface = nullptr;
	}
}

void APickableItemClass::ItemPickedUp()
{
	playerPickUpInterface->RemoveInteractableFromPlayerRange(this);
	this->Destroy();
}
