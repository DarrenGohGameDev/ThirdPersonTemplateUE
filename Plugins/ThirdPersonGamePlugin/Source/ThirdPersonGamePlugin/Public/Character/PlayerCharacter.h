// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "Interface/PlayerInteractInterface.h"
#include "PlayerCharacter.generated.h"

class UPlayerInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterTrajectoryComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API APlayerCharacter : public ABaseCharacter  , public IPlayerInteractInterface
{
	GENERATED_BODY()
	
public :

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual bool IsItemWithinPlayerFov(AActor* item) override;

	virtual AActor* RemoveItemFromPlayerRange(AActor* item) override;

protected :

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "InputComponent")
	UPlayerInputComponent * playerInputComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterTrajectoryComponent* TrajectoryComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "InteractSystem")
	float playerFovRange = 1.f;

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void EnterCrouch();

	void FinishCrouch();

	void EnterSprint();

	void ExitSprint();

	void Interact();

	virtual void InteractWithInteractable(IInteractable * item) override;

	virtual TArray<APickableItemClass*>  GetAllItemInPlayerFovInArray() override;

private :

	void InitPlayerCharacter();

};
