// Fill out your copyright notice in the Description page of Project Settings.

#include "Network.h"
#include "NetBlueprintFunctionLibrary.h"


void UNetBlueprintFunctionLibrary::ShowLoadingScreen(UUserWidget* LoadingScreenWidget)
{
	FLoadingScreenAttributes LoadingScreen;

	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	TSharedRef< SWidget> LoadingScreenSlateWidget = Cast<UWidget>(LoadingScreenWidget)->TakeWidget();
	FString str = FString(TEXT("Lol"));
	LoadingScreen.WidgetLoadingScreen = LoadingScreenSlateWidget;//FLoadingScreenAttributes::NewTestLoadingScreenWidget(); // <-- test screen that comes with UE

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	
}

bool UNetBlueprintFunctionLibrary::InviteFriend(FString UniqueNetId, FName SessionName)
{
	
	IOnlineSessionPtr Sessions = Online::GetSessionInterface();
	IOnlineFriendsPtr Friends = Online::GetFriendsInterface();
	TArray< TSharedRef<FOnlineFriend> > OutFriends;
	Friends->GetFriendsList(0, EFriendsLists::ToString( EFriendsLists::Default), OutFriends);
	TSharedPtr<FUniqueNetId> FriendId;
	for (int32 i = 0; i < OutFriends.Num(); i++)
	{
		TSharedRef<FOnlineFriend> Friend = OutFriends[i];
		if (Friend->GetUserId()->ToString() == UniqueNetId)
		{
			FriendId = Friend->GetUserId();
		}


	}
	const FUniqueNetId& CFriendId = *FriendId.Get();
	//FUniqueNetId FriendId = ;
	return Sessions->SendSessionInviteToFriend(0, SessionName, CFriendId);
}