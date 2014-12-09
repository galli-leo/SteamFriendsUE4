// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
//#include "Online/OnlineSubsystem/Public/OnlineSubsystem.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "Runtime/MoviePlayer/Public/MoviePlayerSettings.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Online.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"

#include "NetBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UNetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintCallable, Category = LoadingScreen)
		static void ShowLoadingScreen(UUserWidget* LoadingScreenWidget);
		
		UFUNCTION(BlueprintCallable, Category = "Online|Friends")
		static bool InviteFriend(FString UniqueNetId, FName SessionName);
	
};
