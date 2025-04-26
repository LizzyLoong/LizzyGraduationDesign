// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "CPP_BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxMPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxSPChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHRChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMRChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATKChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMAGChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATKspeedChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMAGspeedChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnATKsuckChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMAGsuckChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDEFChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMDEFChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDEFdecayChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMDEFdecayChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDEFpenetrateChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMDEFpenetrateChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCRTChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCRTdamChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRunChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnToughChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHRintenseChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExtentChangeEvent,float,OldValue,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTestChangeEvent,float,OldValue,float,NewValue);








USTRUCT(Blueprintable)
struct FDataRow
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Decisions;
};

USTRUCT(Blueprintable)
struct FTreeNode
{
	GENERATED_BODY()
	FString Attribute;
	TMap<FString, TSharedPtr<FTreeNode>> Children;
	FString Decision;
};






UENUM(BlueprintType)
enum class ELegendComment:uint8
{
	HOTPT UMETA(DisplayName = "输出"),
	HLIVE UMETA(DisplayName = "生存")
};
inline FString EnumToString(ELegendComment EnumValue)
{
	const UEnum* EnumPtr = StaticEnum<ELegendComment>();
	if (!EnumPtr)
	{
		return FString("Invalid Enum");
	}
	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
}
UENUM(BlueprintType)
enum class EOutputComment:uint8
{
	HATK UMETA(DisplayName = "物理伤害"),
	HMAG UMETA(DisplayName = "魔法伤害"),
	HHRT UMETA(DisplayName = "真实伤害"),
};
inline FString EnumToString(EOutputComment EnumValue)
{
	const UEnum* EnumPtr = StaticEnum<EOutputComment>();
	if (!EnumPtr)
	{
		return FString("Invalid Enum");
	}
	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
}
UENUM(BlueprintType)
enum class ELiveComment:uint8
{
	HDEF UMETA(DisplayName = "护甲偏高"),
	HMDEF UMETA(DisplayName = "魔抗偏高"),
	HHP UMETA(DisplayName = "均衡"),
};
inline FString EnumToString(ELiveComment EnumValue)
{
	const UEnum* EnumPtr = StaticEnum<ELiveComment>();
	if (!EnumPtr)
	{
		return FString("Invalid Enum");
	}
	return EnumPtr->GetNameStringByValue(static_cast<int64>(EnumValue));
}











USTRUCT(BlueprintType)
struct FCharacterInformation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterInfo")
	ELegendComment	LegendComment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterInfo")
	EOutputComment	DamageKind;
};

UCLASS()
class LIZZYGRADES_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_BaseCharacter();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterInfo")
	FCharacterInformation CharacterInfo;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterComment")
	ELegendComment LegendComment;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterComment")
	EOutputComment OutputComment;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="CharacterComment")
	ELiveComment LiveComment;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

public:

	
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 这个函数是设置这个对象本身的AttributeComment的函数
	// 是用来给LegendComment、OutputComment和LiveComment赋值的函数
	UFUNCTION(BlueprintCallable)
	void SetCharacterAttributeComment();

	
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	double CalculateEntropy(const TArray<FDataRow>& Dataset, int TargetIndex);
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	double CalculateInfoGain(const TArray<FDataRow>& Dataset, int AttrIdx, int TargetIdx);
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	int32 ChooseBestAttribute(const TArray<FDataRow>& Dataset, const TArray<bool>& UsedAttributes, int32 TargetIdx);
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	FString Predict(const TSharedPtr<FTreeNode>& Root, const FDataRow& Sample, const TArray<FString>& Attributes);
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	FString GetPluralityClass(const TMap<FString, int32>& ClassCounts);
	// UFUNCTION(BlueprintCallable,Category="AttributeComment基础")
	TSharedPtr<FTreeNode> BuildDecisionTree(const TArray<FDataRow>& Dataset, const TArray<FString>& Attributes, TArray<bool> UsedAttributes, int32 TargetIdx);

	
	
	TArray<FDataRow> dataset = {
        {{"HOTPT","HATK","HDEF","HATK","HDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HDEF","HMAG","HDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HOTPT","HATK","HDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HATK","HDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HATK","HDEF"}, {"Decay","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HMDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HATK","HLIVE","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HMDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HOTPT","HMAG","HLIVE","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HOTPT","HHRT","HDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HMDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HOTPT","HHRT","HLIVE","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HATK","HDEF","HATK","HDEF"}, {"Decay","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HATK","HMDEF"}, {"ATK","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HATK","HLIVE"}, {"ATK","DEF","OTPT"}},
        {{"HLIVE","HATK","HDEF","HMAG","HDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HATK","HDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HATK","HDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HMDEF"}, {"ATK","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HMAG","HLIVE"}, {"ATK","MDEF","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HMDEF","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HATK","HDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HATK","HMDEF"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HATK","HLIVE"}, {"ATK","DEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HMDEF"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HMAG","HLIVE"}, {"ATK","MDEF","LIVE"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HMDEF"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HATK","HLIVE","HHRT","HLIVE"}, {"ATK","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HDEF"}, {"MAG","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HMDEF"}, {"Decay","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HATK","HLIVE"}, {"MAG","DEF","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HDEF"}, {"MAG","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HMDEF"}, {"Decay","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HMAG","HLIVE"}, {"MAG","MDEF","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HMDEF","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HDEF"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HMDEF"}, {"Decay","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HATK","HLIVE"}, {"MAG","DEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HDEF"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HMDEF"}, {"Decay","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HMAG","HLIVE"}, {"MAG","MDEF","LIVE"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HDEF"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HMDEF"}, {"Decay","HP","OTPT"}},
        {{"HLIVE","HMAG","HLIVE","HHRT","HLIVE"}, {"MAG","HP","OTPT"}},
        {{"HLIVE","HHRT","HDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HMDEF","HHRT","HLIVE"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HMDEF"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HATK","HLIVE"}, {"about","DEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HMDEF"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HMAG","HLIVE"}, {"about","MDEF","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HMDEF"}, {"about","HP","LIVE"}},
        {{"HLIVE","HHRT","HLIVE","HHRT","HLIVE"}, {"about","HP","LIVE"}}
    };

	TArray<FString> attributes = {
		"LegendComment", "SelfOutputComment", "SelfLiveComment",
		"TargetOutputComment", "TargetLiveComment"
	};
	FDataRow sample = {
		{"HOTPT","HATK","HDEF","HATK","HDEF"},
		{}
	};
	
	TArray<TSharedPtr<FTreeNode>> Trees;

	// UFUNCTION(BlueprintCallable)
	void SetTrees(TArray<TSharedPtr<FTreeNode>>& Root,TArray<FDataRow> Dataset,TArray<FString> Attributes);



	
	UPROPERTY(BlueprintReadWrite,Category="CharacterComment")
	FDataRow PredictComment;
	UPROPERTY(BlueprintReadWrite,Category="Fight基础")
	ACPP_BaseCharacter* AttackTargetActor;
	UFUNCTION(BlueprintCallable,Category="PredictComment")
	void SetPredictComment(ACPP_BaseCharacter* TargetActor);
	UFUNCTION(BlueprintCallable,Category="PredictComment")
	FString CallPredictAndGetAdvice(int32 TreeIndex,ACPP_BaseCharacter* TargetActor,FDataRow TwoLegendComment);
















	
public:
	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnTestChangeEvent TestChangeEvent;
	void OnTestAttributeChanged(const FOnAttributeChangeData& Data)
	{
		TestChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}
	
	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnHPChangeEvent HPChangeEvent;
	void OnHPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		HPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMaxHPChangeEvent MaxHPChangeEvent;
	void OnMaxHPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MaxHPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}
	
	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMPChangeEvent MPChangeEvent;
	void OnMPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMaxMPChangeEvent MaxMPChangeEvent;
	void OnMaxMPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MaxMPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnSPChangeEvent SPChangeEvent;
	void OnSPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		SPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMaxMPChangeEvent MaxSPChangeEvent;
	void OnMaxSPAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MaxSPChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnHRChangeEvent HRChangeEvent;
	void OnHRAttributeChanged(const FOnAttributeChangeData& Data)
	{
		HRChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}
	
	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMRChangeEvent MRChangeEvent;
	void OnMRAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MRChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnATKChangeEvent ATKChangeEvent;
	void OnATKAttributeChanged(const FOnAttributeChangeData& Data)
	{
		ATKChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMAGChangeEvent MAGChangeEvent;
	void OnMAGAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MAGChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnATKspeedChangeEvent ATKspeedChangeEvent;
	void OnATKspeedAttributeChanged(const FOnAttributeChangeData& Data)
	{
		ATKspeedChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMAGspeedChangeEvent MAGspeedChangeEvent;
	void OnMAGspeedAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MAGspeedChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnATKsuckChangeEvent ATKsuckChangeEvent;
	void OnATKsuckAttributeChanged(const FOnAttributeChangeData& Data)
	{
		ATKsuckChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMAGsuckChangeEvent MAGsuckChangeEvent;
	void OnMAGsuckAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MAGsuckChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnDEFChangeEvent DEFChangeEvent;
	void OnDEFAttributeChanged(const FOnAttributeChangeData& Data)
	{
		DEFChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMDEFChangeEvent MDEFChangeEvent;
	void OnMDEFAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MDEFChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnDEFdecayChangeEvent DEFdecayChangeEvent;
	void OnDEFdecayAttributeChanged(const FOnAttributeChangeData& Data)
	{
		DEFdecayChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMDEFdecayChangeEvent MDEFdecayChangeEvent;
	void OnMDEFdecayAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MDEFdecayChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnDEFpenetrateChangeEvent DEFpenetrateChangeEvent;
	void OnDEFpenetrateAttributeChanged(const FOnAttributeChangeData& Data)
	{
		DEFpenetrateChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnMDEFpenetrateChangeEvent MDEFpenetrateChangeEvent;
	void OnMDEFpenetrateAttributeChanged(const FOnAttributeChangeData& Data)
	{
		MDEFpenetrateChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnCRTChangeEvent CRTChangeEvent;
	void OnCRTAttributeChanged(const FOnAttributeChangeData& Data)
	{
		CRTChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnCRTdamChangeEvent CRTdamChangeEvent;
	void OnCRTdamAttributeChanged(const FOnAttributeChangeData& Data)
	{
		CRTdamChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnRunChangeEvent RunChangeEvent;
	void OnRunAttributeChanged(const FOnAttributeChangeData& Data)
	{
		RunChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnToughChangeEvent ToughChangeEvent;
	void OnToughAttributeChanged(const FOnAttributeChangeData& Data)
	{
		ToughChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnHRintenseChangeEvent HRintenseChangeEvent;
	void OnHRintenseAttributeChanged(const FOnAttributeChangeData& Data)
	{
		HRintenseChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}

	UPROPERTY(BlueprintAssignable,Category="AttributeChange")
	FOnExtentChangeEvent ExtentChangeEvent;
	void OnExtentAttributeChanged(const FOnAttributeChangeData& Data)
	{
		ExtentChangeEvent.Broadcast(Data.OldValue,Data.NewValue);
	}
	
};



