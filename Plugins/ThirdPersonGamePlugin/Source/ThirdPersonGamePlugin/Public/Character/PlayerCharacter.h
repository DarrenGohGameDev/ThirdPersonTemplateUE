// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UPlayerInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UCharacterTrajectoryComponent;

/**
 * 
 */
UCLASS()
class THIRDPERSONGAMEPLUGIN_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public :

	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

protected :

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "InputComponent")
	UPlayerInputComponent * playerInputComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterTrajectoryComponent* TrajectoryComponent;

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void EnterCrouch();

	void FinishCrouch();

	void EnterSprint();

	void ExitSprint();

	void Interact();

	//virtual void Jump() override;

private :

	void InitPlayerCharacter();

};
