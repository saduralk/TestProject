// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ConnectionTypes_E.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInst_CPP.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGameInst_CPP : public UGameInstance
{
	GENERATED_BODY()



public:
	void BeginPlay();

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);

	UFUNCTION()
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void StartMultiplayerGame();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Multiplayer")
	EConnectionTypes ConnectionType;
	
};


