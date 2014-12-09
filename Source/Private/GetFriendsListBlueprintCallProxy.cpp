

#include "Network.h"
#include "GetFriendsListBlueprintCallProxy.h"

FOnlineSubsystemTestBPCallHelperr::FOnlineSubsystemTestBPCallHelperr(const TCHAR* CallFunctionContext, UWorld* World, FName SystemName)
	: OnlineSub(Online::GetSubsystem(World, SystemName))
	, FunctionContext(CallFunctionContext)
{
	if (OnlineSub == nullptr)
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid or uninitialized OnlineSubsystem"), FunctionContext), ELogVerbosity::Warning);
	}
}

void FOnlineSubsystemTestBPCallHelperr::QueryIDFromPlayerControllerTest(APlayerController* PlayerController)
{
	UserID.Reset();

	if (APlayerState* PlayerState = (PlayerController != NULL) ? PlayerController->PlayerState : NULL)
	{
		UserID = PlayerState->UniqueId.GetUniqueNetId();
		if (!UserID.IsValid())
		{
			FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Cannot map local player to unique net ID"), FunctionContext), ELogVerbosity::Warning);
		}
	}
	else
	{
		FFrame::KismetExecutionMessage(*FString::Printf(TEXT("%s - Invalid player state"), FunctionContext), ELogVerbosity::Warning);
	}
}

UGetFriendsListBlueprintCallProxy::UGetFriendsListBlueprintCallProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ReadCompleteDelegate(FOnReadFriendsListCompleteDelegate::CreateUObject(this, &ThisClass::OnReadFriendsListComplete))
{
}


UGetFriendsListBlueprintCallProxy* UGetFriendsListBlueprintCallProxy::GetFriendsList(UObject* WorldContextObject, class APlayerController* PlayerController)
{
	UGetFriendsListBlueprintCallProxy* Proxy = NewObject<UGetFriendsListBlueprintCallProxy>();
	Proxy->PlayerControllerWeakPtr = PlayerController;
	
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}

void UGetFriendsListBlueprintCallProxy::Activate()
{
	FString ta = FString(TEXT("Hello World"));
	FOnlineSubsystemTestBPCallHelperr Helper(TEXT("CreateSession"), GEngine->GetWorldFromContextObject(WorldContextObject));
	Helper.QueryIDFromPlayerControllerTest(PlayerControllerWeakPtr.Get());

	if (Helper.IsValid())
	{
		auto Friends = Helper.OnlineSub->GetFriendsInterface();
		if (Friends.IsValid())
		{
			ULocalPlayer* Player = Cast<ULocalPlayer>(PlayerControllerWeakPtr->Player);
			Friends->AddOnReadFriendsListCompleteDelegate(Player->ControllerId, ReadCompleteDelegate);
			Friends->ReadFriendsList(Player->ControllerId, EFriendsLists::ToString(EFriendsLists::Default));
			

			return;
		}
	}
	

	// Fail immediately
	TArray<FBlueprintFriend> Fail;
	
	OnFailure.Broadcast(Fail);
}

void UGetFriendsListBlueprintCallProxy::OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr)
{
	if (bWasSuccessful)
	{
		FOnlineSubsystemTestBPCallHelperr Helper(TEXT("CreateSession"), GEngine->GetWorldFromContextObject(WorldContextObject));
		Helper.QueryIDFromPlayerControllerTest(PlayerControllerWeakPtr.Get());

		if (Helper.IsValid())
		{
			auto Friends = Helper.OnlineSub->GetFriendsInterface();
			if (Friends.IsValid())
			{
				TArray<FBlueprintFriend>FriendsArr;
				ULocalPlayer* Player = Cast<ULocalPlayer>(PlayerControllerWeakPtr->Player);
				TArray< TSharedRef<FOnlineFriend> > OutFriends;
				
				Friends->GetFriendsList(LocalUserNum, ListName,OutFriends);
				for (int32 i = 0; i < OutFriends.Num(); i++)
				{
					TSharedRef<FOnlineFriend> Friend = OutFriends[i];
					FBlueprintFriend BPFriend = FBlueprintFriend();
					
					BPFriend.Presence = EOnlinePresenceState::ToString(Friend->GetPresence().Status.State);
					BPFriend.DisplayName = Friend->GetDisplayName();
					BPFriend.RealName = Friend->GetRealName();
					BPFriend.UniqueNetId = Friend->GetUserId()->ToString();
					FriendsArr.Add(BPFriend);
					
					
				}
				Friends->ClearOnReadFriendsListCompleteDelegate(LocalUserNum, ReadCompleteDelegate);
				OnSuccess.Broadcast(FriendsArr);


				
			}
		}
	}
	else
	{
		TArray<FBlueprintFriend> Fail;
		

		OnFailure.Broadcast(Fail);
	}
}