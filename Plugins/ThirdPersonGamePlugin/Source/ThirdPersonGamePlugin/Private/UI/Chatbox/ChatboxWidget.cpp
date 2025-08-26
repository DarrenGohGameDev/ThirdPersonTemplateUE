// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chatbox/ChatboxWidget.h"
#include "Components/VerticalBox.h"
#include "Components/EditableTextBox.h"
#include "UI/Chatbox/ChatboxData.h"

UChatboxWidget::UChatboxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // You can initialize variables here
}

void UChatboxWidget::StartChatting(TArray<FChatboxData> chatboxData)
{
    ToggleChatbox(true);
    currentConversationArray = chatboxData;
}

void UChatboxWidget::StopChatting()
{
    ToggleChatbox(false);
	currentConversationCounter = 0;
}

void UChatboxWidget::NextChat()
{
	if (currentConversationCounter < currentConversationArray.Num())
	{
		currentConversationCounter++;
		FString speakerName = currentConversationArray[currentConversationCounter].speakerName;
		FString msg = currentConversationArray[currentConversationCounter].message;
		SetChatboxText(speakerName,msg);
	}
	else if (currentConversationCounter >= currentConversationArray.Num())
	{
		StopChatting();
	}
}

void UChatboxWidget::SetChatboxText(FString tittle, FString msg)
{
	chatboxTittleText->SetText(FText::FromString(tittle));
    chatboxMessageText->SetText(FText::FromString(msg));
}

void UChatboxWidget::ToggleChatbox(bool toggle)
{
    chatbox->SetVisibility(toggle ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}