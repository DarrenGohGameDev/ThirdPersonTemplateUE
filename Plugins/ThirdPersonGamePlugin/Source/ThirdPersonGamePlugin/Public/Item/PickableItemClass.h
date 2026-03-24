// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItemClass.h"
#include "PickableItemClass.generated.h"

class USphereComponent;
class IPlayerInteractInterface;
class UWorldObjectInteractableDetectionComponent;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API APickableItemClass : public ABaseItemClass
{
	GENERATED_BODY()
	
public :

	APickableItemClass();

	virtual void Interact(APlayerCharacter* interactedPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractDetection")
	UWorldObjectInteractableDetectionComponent* interactableDetectionComponent;

protected :

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float itemFloatingAmplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float itemFloatingTimeConstant = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float itemFloatingRotationRate = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float itemFloatingRunningTimeFloat;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* itemMesh;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float TransformSin();

	void OverlapWithPlayer();

	void ItemPickedUp();

private :

};
