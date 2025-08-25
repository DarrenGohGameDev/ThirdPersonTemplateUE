// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Player/PlayerInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Enums/InputActionEnums.h"
#include "Item/PickableItemClass.h"
#include "Components/BoxComponent.h"
#include "CharacterTrajectoryComponent.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	playerInputComponent = CreateDefaultSubobject<UPlayerInputComponent>(TEXT("PlayerInputComponent"));

	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("TrajectoryComponent"));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//RootComponent = CollisionBox;

	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitPlayerCharacter();
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	const FVector2D MovementVector = (value.Get<FVector2D>() * movementSpeedMultiplier) * actionSpeed;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Forward, MovementVector.Y);

	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Right, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	const FVector2D LookAxisValue = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisValue.X);
	AddControllerPitchInput(LookAxisValue.Y);
}

void APlayerCharacter::EnterCrouch()
{
	Crouch();
	movementSpeedMultiplier = 0.5f;
}

void APlayerCharacter::FinishCrouch()
{
	UnCrouch();
	movementSpeedMultiplier = 1.0f;
}

void APlayerCharacter::EnterSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed * actionSpeed;
}

void APlayerCharacter::ExitSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed * actionSpeed;
}

void APlayerCharacter::Interact()
{
	
	if (InteractableInPlayerRangeArray.IsValidIndex(0))
	{
		//InteractWithItem(InteractableInPlayerRangeArray[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact is being pressed"));
	}
	
}

bool APlayerCharacter::IsItemWithinPlayerFov(AActor* item)
{
	FVector playerForwardVector = this->GetActorForwardVector();
	FVector toItem = (item->GetActorLocation() - this->GetActorLocation());

	float dot = FVector::DotProduct(playerForwardVector, toItem);

	if (dot >= playerFovRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item is in front of player"));
		InteractableInPlayerRangeArray.Add(item);
		return true;
	}

	return false;
}

APickableItemClass* APlayerCharacter::RemoveItemFromPlayerRange(APickableItemClass* item)
{
	//ItemsInPlayerRangeArray.Remove(item);
	return item;
}

void APlayerCharacter::InteractWithItem(APickableItemClass* item)
{
	// for now this is hard codded to work on pick up item
	// need to expend and make this work with all item and being interactable
	// writing for what will work for now 
	item->Interact();
	InteractableInPlayerRangeArray.Remove(item);
	// prob wanna disable instead of destroy down the line for optamization
	item->Destroy();
}

TArray<APickableItemClass*> APlayerCharacter::GetAllItemInPlayerFovInArray()
{
	TArray<APickableItemClass*> allItemInPlayerFov;

	return allItemInPlayerFov;
}

void APlayerCharacter::InitPlayerCharacter()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::WalkInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::CrouchInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::EnterCrouch);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::CrouchInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::FinishCrouch);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::SprintInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::EnterSprint);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::SprintInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::ExitSprint);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::LookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	playerInputComponent->SetupInputBinding(playerController, InputActionEnum::InteractInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
}


