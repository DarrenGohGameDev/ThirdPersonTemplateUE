// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseTalkableCharacter.h"
#include "UI/Chatbox/ChatboxConversation.h"
#include "UI/Chatbox/ChatboxManager.h"
#include "Components/WorldObjectInteractableDetectionComponent.h"

ABaseTalkableCharacter::ABaseTalkableCharacter()
{
	chatBoxConversationComponent = CreateDefaultSubobject<UChatboxConversation>(TEXT("ChatBoxConversationComponent"));
	interactableDetectionComponent = CreateDefaultSubobject< UWorldObjectInteractableDetectionComponent>(TEXT("InteractableDetectionComponent"));
}

void ABaseTalkableCharacter::Interact()
{
	UChatboxManager::onStartConversation.Broadcast(chatBoxConversationComponent->GetConversationArray());
}
