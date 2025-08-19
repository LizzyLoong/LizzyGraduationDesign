// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "CPP_BaseCharacter.generated.h"

class UCPP_BaseAbility;
struct FS_SkillInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangeEvent, float, OldValue, float, NewValue);
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

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name="BaseCharacter";
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon=nullptr;

	//FCharacterInfo();
};


UCLASS()
class LIZZYGRADES_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_BaseCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterInfo CharacterInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	UFUNCTION(BlueprintCallable,Category="BaseCharacter")
	FS_SkillInfo GameplayAbilityInfo(TSubclassOf<UCPP_BaseAbility>AbilityClass,int Level);






	

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



	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
