

#pragma once

#include "OnlineBlueprintCallProxyBase.h"
#include "OnlineSessionInterface.h"
#include "OnlineSubsystem.h"
#include "Engine.h"

#include "OnlineBlueprintCallProxyBase.h"
#include "OnlineSubsystemUtils.h"
#include "GetFriendsListBlueprintCallProxy.generated.h"





USTRUCT(BlueprintType)
struct FBlueprintFriend
{
	GENERATED_USTRUCT_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
		FString DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
		FString RealName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
		FString Presence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Online|Friend")
		FString UniqueNetId;
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlueprintGetFriendsListDelegate, const TArray<FBlueprintFriend>&, Results);

UCLASS()
class  UGetFriendsListBlueprintCallProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintAssignable)
		FBlueprintGetFriendsListDelegate OnSuccess;

	// Called when there was an error creating the session
	UPROPERTY(BlueprintAssignable)
		FBlueprintGetFriendsListDelegate OnFailure;
		

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Online|Friends")
		static UGetFriendsListBlueprintCallProxy* GetFriendsList(UObject* WorldContextObject, class APlayerController* PlayerController);

	// UOnlineBlueprintCallProxyBase interface
	virtual void Activate() override;

	TWeakObjectPtr<APlayerController> PlayerControllerWeakPtr;

	UObject* WorldContextObject;

	UGetFriendsListBlueprintCallProxy(const FObjectInitializer& ObjectInitializer);
	
private:
	// Internal callback when session creation completes, calls StartSession
	void OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);

	FOnReadFriendsListCompleteDelegate ReadCompleteDelegate;
	
};
