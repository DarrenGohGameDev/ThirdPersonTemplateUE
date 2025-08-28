// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldObjectInteractableDetectionComponent.generated.h"

class USphereComponent;
class IPlayerInteractInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONGAMEPLUGIN_API UWorldObjectInteractableDetectionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldObjectInteractableDetectionComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	USphereComponent* interactDetectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	float interactDetectionRange = 100.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	IPlayerInteractInterface* playerPickUpInterface;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
