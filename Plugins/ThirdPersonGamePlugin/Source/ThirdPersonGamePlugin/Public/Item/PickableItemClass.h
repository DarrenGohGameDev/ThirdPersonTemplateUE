// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItemClass.h"
#include "PickableItemClass.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API APickableItemClass : public ABaseItemClass
{
	GENERATED_BODY()
	
public :

	APickableItemClass();

	virtual void Interact() override;

protected :

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detection")
	USphereComponent* detectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Detection")
	float detectionRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float M_Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float M_TimeConstant = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float M_RotationRate = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemFloatingParameter")
	float M_RunningTimeFloat;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float TransformSin();

	void OverlapWithPlayer();

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

private :

};
