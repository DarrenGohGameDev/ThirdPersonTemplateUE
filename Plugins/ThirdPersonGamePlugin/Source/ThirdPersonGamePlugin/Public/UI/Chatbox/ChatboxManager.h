// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/Delegate.h"
#include "UI/Chatbox/ChatboxData.h"
#include "ChatboxManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartConversation,TArray<FChatboxData>);

DECLARE_MULTICAST_DELEGATE(FOnLeaveConversation);

DECLARE_MULTICAST_DELEGATE(FOnNextChat);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONGAMEPLUGIN_API UChatboxManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UChatboxManager();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static FOnStartConversation onStartConversation;

	static FOnLeaveConversation onLeaveConversation;

	static FOnNextChat onNextChat;

protected:

	virtual void BeginPlay() override;

};
