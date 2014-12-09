

#pragma once

#include "Engine/GameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineBlueprintCallProxyBase.h"
#include "Engine.h"
#include "Core.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Sockets/Public/SocketTypes.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Private/OnlineSubsystemUtilsPrivatePCH.h"
#include "Classes/FindSessionsCallbackProxy.h"
#include "NetGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class NETWORK_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintNativeEvent, Category = "Online|Friends")
		void SessionInviteAccepted(const FBlueprintSessionResult& InviteResult);

		UNetGameInstance(const FObjectInitializer& ObjectInitializer);
private:
	// Internal callback when session creation completes, calls StartSession
	void OnSessionUserInviteAccepted(const bool bWasSuccesful, const int32 ControllerId, TSharedPtr<FUniqueNetId> UserId, const FOnlineSessionSearchResult &InviteResult);

	FOnSessionUserInviteAcceptedDelegate SessionInviteAcceptedDelegate;

	FOnJoinSessionCompleteDelegate Delegate;

	void OnCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	
	
};
