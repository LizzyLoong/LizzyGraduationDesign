// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CPP_BaseAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class LIZZYGRADES_API UCPP_BaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	// UCPP_BaseAttributeSet();

	// 后处理函数
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	

	//生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, HP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MaxHP);
	//法力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MaxMP);
	//能量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData SP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, SP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MaxSP;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MaxSP);

	
	//生命恢复
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData HR;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, HR);
	//法力恢复
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MR;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MR);

	//攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, ATK);
	//法强
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MAG;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MAG);
	//攻击速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData ATKspeed;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, ATKspeed);
	//冷却缩减
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MAGspeed;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MAGspeed);
	//生命偷取
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData ATKsuck;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, ATKsuck);
	//全能吸血
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MAGsuck;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MAGsuck);
	
	//护甲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, DEF);
	//魔抗
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MDEF;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MDEF);
	//护甲衰减
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData DEFdecay;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, DEFdecay);
	//魔抗衰减
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MDEFdecay;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MDEFdecay);
	//护甲穿透
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData DEFpenetrate;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, DEFpenetrate);
	//魔抗穿透
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MDEFpenetrate;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MDEFpenetrate);

	//暴击率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData CRT;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, CRT);
	//暴击伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData CRTdam;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, CRTdam);
	//移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData Run;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, Run);
	//韧性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData Tough;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, Tough);
	//生命恢复强度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData HRintense;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, HRintense)
	//攻击距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData Extent;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, Extent);
	//Test
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData Test;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, Test);

	// 琉晶矿（已弃用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData CarriedResource;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, CarriedResource);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色基础属性集")
	FGameplayAttributeData MaxCarriedResource;
	ATTRIBUTE_ACCESSORS(UCPP_BaseAttributeSet, MaxCarriedResource);
	
	
};
