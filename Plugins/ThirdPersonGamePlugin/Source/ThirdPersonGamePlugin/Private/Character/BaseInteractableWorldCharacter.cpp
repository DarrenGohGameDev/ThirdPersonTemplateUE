// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseInteractableWorldCharacter.h"
#include "Components/SphereComponent.h"
#include "Character//PlayerCharacter.h"

ABaseInteractableWorldCharacter::ABaseInteractableWorldCharacter()
{
	interactDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	interactDetectionSphere->SetSphereRadius(interactDetectionRange);
	interactDetectionSphere->SetupAttachment(RootComponent);
}

void ABaseInteractableWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	interactDetectionSphere->SetSphereRadius(interactDetectionRange);
}

void ABaseInteractableWorldCharacter::Interact(APlayerCharacter* interactedPlayer)
{

}
