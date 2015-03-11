

#include "Network.h"
#include "NetGameInstance.h"

UNetGameInstance::UNetGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, SessionInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &ThisClass::OnSessionUserInviteAccepted))
	, Delegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCompleted))
{
	FString test = "";
	
}

void UNetGameInstance::OnSessionUserInviteAccepted(const bool bWasSuccesful, const int32 ControllerId, TSharedPtr<FUniqueNetId> UserId, const FOnlineSessionSearchResult &InviteResult)
{
	if (bWasSuccesful)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		const FBlueprintSessionResult& Result = FBlueprintSessionResult();
		FOnlineSessionSearchResult RResult = InviteResult;
		auto& IResult = RResult;
		//Result.OnlineResult = IResult;
		//this->SessionInviteAccepted(Result);
		auto Sessions = Online::GetSessionInterface();
		Sessions->AddOnJoinSessionCompleteDelegate(Delegate);
		Sessions->JoinSession(0, GameSessionName, InviteResult);
		GEngine->AddOnScreenDebugMessage(-1, 3000, FColor::Cyan, "InviteAccepted");
		FFrame::KismetExecutionMessage(TEXT("Yeeee Invite succesful"), ELogVerbosity::Warning);
	}
	else
	{
		FFrame::KismetExecutionMessage(TEXT("FUUU Invite not succesful"), ELogVerbosity::Warning);
	}
}

void UCCGameInstance::Init()
 {
     IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
     if (OnlineSub)
     {
         IOnlineSessionPtr SessionInt = OnlineSub->GetSessionInterface();
         if (SessionInt.IsValid())
         {
             int32 ControllerId = 0;
             if (ControllerId != 255)
             {
                 SessionInt->AddOnSessionInviteAcceptedDelegate(ControllerId, OnSessionUserInviteAccepted);
             }
         }
     }
 }

void UNetGameInstance::SessionInviteAccepted_Implementation(const FBlueprintSessionResult &InviteResult)
{
	
}

void UNetGameInstance::OnCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	FFrame::KismetExecutionMessage(TEXT("Yeeee Join succesful"), ELogVerbosity::Warning);

	
	auto Sessions = Online::GetSessionInterface();
	if (Sessions.IsValid())
	{
		Sessions->ClearOnJoinSessionCompleteDelegate(Delegate);

		if (Result == EOnJoinSessionCompleteResult::Success)
		{
			// Client travel to the server
			FString ConnectString;
			if (Sessions->GetResolvedConnectString(GameSessionName, ConnectString) && PC->IsValidLowLevel())
			{
				//UE_LOG(Network, Log, TEXT("Join session: traveling to %s"), *ConnectString);
					
				PC->ClientTravel(ConnectString, TRAVEL_Absolute);
					
				return;
			}
		}
	}
	

	
}
