// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chatbox/ChatboxWidget.h"
#include "Components/EditableTextBox.h"
#include "UI/Chatbox/ChatboxData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Chatbox/ChatboxManager.h"
#include "Character/PlayerCharacter.h"


UChatboxWidget::UChatboxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    // You can initialize variables here
}

void UChatboxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UChatboxManager::onStartConversation.AddUObject(this, &UChatboxWidget::StartChatting);
	UChatboxManager::onLeaveConversation.AddUObject(this, &UChatboxWidget::StopChatting);
	UChatboxManager::onNextChat.AddUObject(this, &UChatboxWidget::NextChat);

	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(PC->GetPawn()))
		{
			chatboxOwner = Player;
		}
	}

	ToggleChatbox(false);
	ResetChatbox();
}

void UChatboxWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UChatboxManager::onStartConversation.RemoveAll(this);
	UChatboxManager::onLeaveConversation.RemoveAll(this);
	UChatboxManager::onNextChat.RemoveAll(this);
}

void UChatboxWidget::StartChatting(APlayerCharacter * player ,TArray<FChatboxData> chatboxData)
{
	if (chatboxOwner != player)
		return;

	ToggleChatbox(true);
	currentConversationArray = chatboxData;
	ResetChatbox();
	NextChat(player);
}

void UChatboxWidget::StopChatting(APlayerCharacter* player)
{
	if (chatboxOwner != player)
		return;

	ToggleChatbox(false);
	ResetChatbox();
}

void UChatboxWidget::NextChat(APlayerCharacter* player)
{
	if (chatboxOwner != player)
		return;

	if (this->GetVisibility() != ESlateVisibility::Visible)
		return;

	currentLetterIndex = 0;

	if (currentConversationCounter >= currentConversationArray.Num())
	{
		StopChatting(player);
		return;
	}

	FString speakerName = currentConversationArray[currentConversationCounter].speakerName;
	FString msg = currentConversationArray[currentConversationCounter].message;
	SetChatboxText(speakerName, msg);
	currentConversationCounter++;
}

void UChatboxWidget::SetChatboxText(FString tittle, FString msg)
{
	chatboxTittleText->SetText(FText::FromString(tittle));
	StartTypeWriterEffectOnChatboxText(msg);
}

void UChatboxWidget::ToggleChatbox(bool toggle)
{
    this->SetVisibility(toggle ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
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
		UGameplayStatics::PlaySound2D(this, typeWritterEffectSfx, typeWriterEffectSfxVolume);
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

void UChatboxWidget::ResetChatbox()
{
	currentConversationCounter = 0;
	chatboxTittleText->SetText(FText::GetEmpty());
	chatboxMessageText->SetText(FText::GetEmpty());
}
