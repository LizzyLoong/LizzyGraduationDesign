// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CPP_BaseAbility.generated.h"

UENUM(BlueprintType)
enum class ESkillCostType : uint8
{
	MP,
	SP,
	HP,
	MP_And_SP,
};
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Tactical UMETA(DisplayName = "战术技能"),
	Strategy UMETA(DiaplayName = "战略技能"),
	Combat UMETA(DispalyName = "格斗技"),
	Melee UMETA(DispalyName = "普通攻击")
};

USTRUCT(BlueprintType)
struct FS_SkillInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	FString SkillName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	TSubclassOf<UCPP_BaseAbility> AbilityClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	ESkillType AbilityType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	float CD;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	ESkillCostType CostType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	float CostValue;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	TObjectPtr<UTexture2D> Icon=nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	int32 SkillLevel=1;

	FS_SkillInfo();
	// FS_SkillInfo(FString SkillName,TSubclassOf<UCPP_BaseAbility> AbilityClass,float CD,ESkillCostType CostType,float CostValue,UTexture2D* Icon);
	FS_SkillInfo(float CD,ESkillCostType CostType, float CostValue,TSubclassOf<UCPP_BaseAbility> AbilityClass);
};




/**
 * 
 */
UCLASS()
class LIZZYGRADES_API UCPP_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SkillInfo")
	FS_SkillInfo SkillInfo;

	UFUNCTION(BlueprintCallable,Category="SkillInfo")
	FS_SkillInfo GetAbilityInfo(int Level);
	
};
