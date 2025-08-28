// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chatbox/ChatboxWidget.h"
#include "Components/VerticalBox.h"
#include "Components/EditableTextBox.h"
#include "UI/Chatbox/ChatboxData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Chatbox/ChatboxManager.h"

UChatboxWidget::UChatboxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // You can initialize variables here
}

void UChatboxWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UChatboxManager::onStartConversation.AddUObject(this, &UChatboxWidget::StartChatting);
}

void UChatboxWidget::NativeDestruct()
{
	Super::NativeDestruct();
	UChatboxManager::onStartConversation.RemoveAll(this);
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
		SetChatboxText(speakerName, msg);
	}
	else if (currentConversationCounter >= currentConversationArray.Num())
	{
		StopChatting();
	}
}

void UChatboxWidget::SetChatboxText(FString tittle, FString msg)
{
	chatboxTittleText->SetText(FText::FromString(tittle));
	StartTypeWriterEffectOnChatboxText(msg);
}

void UChatboxWidget::ToggleChatbox(bool toggle)
{
    chatbox->SetVisibility(toggle ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UChatboxWidget::StartTypeWriterEffectOnChatboxText(FString msg)
{
	currentTypeWriterEffectText.Empty();
	typeWriterEffectLetterArray.Empty();
	StopTypeWriterEffect();
	for (int i = 0; i < msg.Len(); i++)
	{
		typeWriterEffectLetterArray.Add(msg.Mid(i,1));
	}

	GetWorld()->GetTimerManager().SetTimer(typeWriterEffectTimer, this, &UChatboxWidget::ShowNextLetter, typeWriterEffectSpeed, true);
}

void UChatboxWidget::ShowNextLetter()
{
	if (currentLetterIndex < typeWriterEffectLetterArray.Num())
	{
		currentTypeWriterEffectText.Append(typeWriterEffectLetterArray[currentLetterIndex]);
		chatboxMessageText->SetText(FText::FromString(currentTypeWriterEffectText));
		currentLetterIndex++;
		UGameplayStatics::PlaySound2D(this, typeWritterEffectSfx);
	}
	else
	{
		StopTypeWriterEffect();
	}
}

void UChatboxWidget::StopTypeWriterEffect()
{
	GetWorld()->GetTimerManager().ClearTimer(typeWriterEffectTimer);
}
