// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseTalkableCharacter.h"
#include "UI/Chatbox/ChatboxConversation.h"
#include "UI/Chatbox/ChatboxManager.h"
#include "Components/WorldObjectInteractableDetectionComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInteractInterface.h"

ABaseTalkableCharacter::ABaseTalkableCharacter()
{
	chatBoxConversationComponent = CreateDefaultSubobject<UChatboxConversation>(TEXT("ChatBoxConversationComponent"));

	interactableDetectionComponent = CreateDefaultSubobject< UWorldObjectInteractableDetectionComponent>(TEXT("InteractableDetectionComponent"));
	interactableDetectionComponent->SetupAttachment(GetRootComponent());

	interactableDetectionComponent->interactDetectionSphere->SetupAttachment(GetRootComponent());
}

void ABaseTalkableCharacter::Interact()
{
	UChatboxManager::onStartConversation.Broadcast(chatBoxConversationComponent->GetConversationArray());
	interactableDetectionComponent->playerPickUpInterface->RemoveInteractableFromPlayerRange(this);
}

void ABaseTalkableCharacter::BeginPlay()
{
	Super::BeginPlay();
	interactableDetectionComponent->interactDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseTalkableCharacter::OnOverlapEnd);
}

void ABaseTalkableCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UChatboxManager::onLeaveConversation.Broadcast();
}