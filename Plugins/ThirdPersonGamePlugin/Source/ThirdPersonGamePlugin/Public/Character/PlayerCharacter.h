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
class UChatboxWidget;
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

	virtual bool IsInteractableWithinPlayerFov(AActor* item) override;

	UFUNCTION(Server, Reliable)
	void Server_RequestPickup(APickableItemClass* Item);

	virtual AActor* RemoveInteractableFromPlayerRange(AActor* item) override;

protected :

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "InputComponent")
	UPlayerInputComponent * playerInputComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCharacterTrajectoryComponent* TrajectoryComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category="HUD")
	TSubclassOf<UChatboxWidget> chatboxWidgetClass;

	UChatboxWidget* playerChatboxWidget;

	UPROPERTY(EditAnywhere, Category = "InteractSystem")
	float playerFovRange = 1.f;

	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void EnterCrouch();

	void FinishCrouch();

	void EnterSprint();

	void ExitSprint();

	void Interact();

	void NextChat();

	virtual void InteractWithInteractable(IInteractable * item) override;

	//virtual void InteractWithPickable(APickableItemClass* item);

	virtual TArray<IInteractable*>  GetAllInteractableInPlayerFovInArray() override;

private :

	void InitPlayerCharacter();

};
