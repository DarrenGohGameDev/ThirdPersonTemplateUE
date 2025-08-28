// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chatbox/ChatboxConversation.h"
#include "UI/Chatbox/ChatboxManager.h"
#include "UI/Chatbox/ChatboxData.h"

// Sets default values for this component's properties
UChatboxConversation::UChatboxConversation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TArray<FChatboxData> UChatboxConversation::GetConversationArray()
{
	return conversationArray;
}
