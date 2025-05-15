// Fill out your copyright notice in the Description page of Project Settings.

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "interfaces/OnlineSessionInterface.h"
#include "GameInst_CPP.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

class IOnlineSubsystem;

void UGameInst_CPP::StartMultiplayerGame_Implementation()
{
    IOnlineSubsystem* Subsystem;
    Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            FOnlineSessionSettings SessionSettings;
            SessionSettings.bIsLANMatch = true; // Set to true for LAN, false for online
            SessionSettings.NumPublicConnections = 4; // Maximum players
            SessionSettings.bShouldAdvertise = true; // Advertise the session
            SessionSettings.bUsesPresence = true; // Use presence (e.g., Steam friends)
            SessionSettings.bAllowJoinInProgress = true;
            SessionSettings.bUseLobbiesIfAvailable = true;
            FName SessionName = FName("MySessionName"); // Session name

			if (SessionInterface->GetNamedSession(SessionName))
			{
				FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
				DestroySessionCompleteDelegate.BindUObject(this, &UGameInst_CPP::OnDestroySessionComplete);
				SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);
				SessionInterface->DestroySession(SessionName);
				
				SessionInterface->DestroySession(SessionName);
				return;
			}

            UWorld* World = GetWorld();
            APlayerController* PlayerController = World->GetFirstPlayerController();
            if(PlayerController)
            {
//                SessionInterface->CreateSession(*PlayerController->GetUniqueID(), SessionName, SessionSettings);
            }

            FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
            CreateSessionCompleteDelegate.BindUObject(this, &UGameInst_CPP::OnCreateSessionComplete);

            SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);
            SessionInterface->CreateSession(PlayerController->GetUniqueID(), SessionName, SessionSettings);

//            SessionInterface->StartSession(SessionName);




        }
    }
}

void UGameInst_CPP::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
    if (bSuccess)
    {
        // Session created successfully
        UWorld* context_object = GetWorld();
        if (context_object)
        {
            UGameplayStatics::OpenLevel(context_object, FName("ThirdPersonMap"), true, FString("listen"));
			UE_LOG(LogTemp, Display, TEXT("Session created"));
        }
        else
        {
            UWorld* world_context_object = GEngine->GetWorldFromContextObjectChecked(this);
            UGameplayStatics::OpenLevel(world_context_object, FName("ThirdPersonMap"), true, FString("listen"));

        }
    }
    else
    {
		UE_LOG(LogTemp, Display, TEXT("Session creation failed"));
        // Session creation failed
    }
}

void UGameInst_CPP::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		StartMultiplayerGame_Implementation();
	}
}