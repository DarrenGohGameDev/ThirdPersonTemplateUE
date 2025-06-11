// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "Enums/InputActionEnums.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONTEMPLATE_API UPlayerInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInputComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template <typename UserClass>
	void SetupInputBinding(APlayerController* playerController, InputActionEnum inputActionEnum, ETriggerEvent triggerEvent, UserClass* Object, void(UserClass::* Func)())
	{
		UE_LOG(LogTemp, Warning, TEXT("Move is being setup"));
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(playerInputMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(playerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(GetInputActionFromInputActionEnum(inputActionEnum), triggerEvent, Object, Func);
		}
	};

	template <typename UserClass>
	void SetupInputBinding(APlayerController* playerController, InputActionEnum inputActionEnum, ETriggerEvent triggerEvent, UserClass* Object, void (UserClass::* Func)(const FInputActionValue&))
	{
		UE_LOG(LogTemp, Warning, TEXT("Move is being setup"));
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(playerInputMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(playerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(GetInputActionFromInputActionEnum(inputActionEnum), triggerEvent, Object, Func);
		}
	};

	UInputAction* GetInputActionFromInputActionEnum(InputActionEnum inputActionEnum)
	{
		switch (inputActionEnum)
		{
		case InputActionEnum::WalkInputAction:
			return walkInputAction;

		case InputActionEnum::AttackInputAction:
			return attackInputAction;

		case InputActionEnum::LookInputAction:
			return lookInputAction;

		case InputActionEnum::InteractInputAction:
			return interactInputAction;

		case InputActionEnum::CrouchInputAction:
			return crouchInputAction;

		case InputActionEnum::SprintInputAction:
			return sprintInputAction;

		default:
			UE_LOG(LogTemp, Warning, TEXT("inputActionEnum %s inputActionEnum is not found please look into player input component"), *UEnum::GetValueAsString(inputActionEnum));
			return nullptr;
		}
	};

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* playerInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* walkInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* crouchInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* sprintInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* attackInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* lookInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* interactInputAction;
};
