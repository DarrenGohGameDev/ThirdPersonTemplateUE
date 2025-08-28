// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WorldObjectInteractableDetectionComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInteractInterface.h"

// Sets default values for this component's properties
UWorldObjectInteractableDetectionComponent::UWorldObjectInteractableDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	interactDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractDetectionSphere"));
	interactDetectionSphere->SetSphereRadius(interactDetectionRange);
	interactDetectionSphere->SetupAttachment(this);
}


// Called when the game starts
void UWorldObjectInteractableDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	interactDetectionSphere->SetSphereRadius(interactDetectionRange);

	interactDetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UWorldObjectInteractableDetectionComponent::OnOverlapBegin);
	interactDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UWorldObjectInteractableDetectionComponent::OnOverlapEnd);
	
}

void UWorldObjectInteractableDetectionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->IsInteractableWithinPlayerFov(this->GetOwner());
	}
}

void UWorldObjectInteractableDetectionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	playerPickUpInterface = Cast<IPlayerInteractInterface>(OtherActor);
	if (playerPickUpInterface)
	{
		playerPickUpInterface->RemoveInteractableFromPlayerRange(this->GetOwner());
		playerPickUpInterface = nullptr;
	}
}

