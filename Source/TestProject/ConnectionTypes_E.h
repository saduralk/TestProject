// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ConnectionTypes_E.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UConnectionTypes_E : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EConnectionTypes : uint8
{
	Value1 UMETA(DisplayName = "None"),
	Value2 UMETA(DisplayName = "Online"),
	Value3 UMETA(DisplayName = "LAN"),
};
