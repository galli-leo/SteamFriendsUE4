SteamFriendsUE4
===============

A Demo of how to integrate the Steam Friends API in UE4

GetFriendsListCallBackProxy: This is a class which is a whole blueprint node and can execute waiting tasks such as networking. It fetches the FriendsList from the Steam Subsystem

NetBlueprintFunctionLibrary: This is a standart blueprint function library. It contains the function to invite a friend.

NetGameInstance: This is a custom Game Instance class. It should join the session of an invite when the invite is accepted. Should work know.
