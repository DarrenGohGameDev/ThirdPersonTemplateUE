// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PickableItemClass.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInteractInterface.h"

APickableItemClass::APickableItemClass()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;

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

	M_RunningTimeFloat += DeltaTime;

	AddActorWorldOffset(FVector(0.f, 0.f, TransformSin()));
	AddActorWorldRotation(M_Amplitude * FRotator(M_RotationRate * DeltaTime));
}

float APickableItemClass::TransformSin()
{
	return M_Amplitude * FMath::Sin(M_RunningTimeFloat * M_TimeConstant);
}

void APickableItemClass::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Item is being Picked up"));
}

void APickableItemClass::OverlapWithPlayer()
{

}

void APickableItemClass::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPlayerInteractInterface* playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->IsInteractableWithinPlayerFov(this);
	}
}

void APickableItemClass::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IPlayerInteractInterface* playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->RemoveInteractableFromPlayerRange(this);
	}
}
