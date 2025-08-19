// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseAbility.h"

FS_SkillInfo::FS_SkillInfo():
	CD(0),
	CostType(ESkillCostType::MP),
	SkillName("CPP_BaseAbility"),
	AbilityType(ESkillType::Melee),
	SkillLevel(0),
	CostValue(0)
{
}

FS_SkillInfo::FS_SkillInfo(float CD,
	ESkillCostType CostType, float CostValue,
	TSubclassOf<UCPP_BaseAbility> AbilityClass
	):
	CD(CD),
	CostType(CostType),
	CostValue(0),
	AbilityClass(AbilityClass)
{
}

FS_SkillInfo UCPP_BaseAbility::GetAbilityInfo(int Level)
{
	UGameplayEffect* CDEffect=GetCooldownGameplayEffect();
	float CD=0;
	if (CDEffect)
	{
		// 自动给 float CD；赋值
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(Level,CD);
	}
	
	UGameplayEffect* CostEffect=GetCostGameplayEffect();
	ESkillCostType CostType=ESkillCostType::MP;
	float CostValue=0;
	if (CostEffect)
	{
		if(CostEffect->Modifiers.Num()>0)
		{
			// 获取花费的是哪一个类型
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level,CostValue);
			// 获取Attribute的名称
			FString CostTypeName=CostEffectModifierInfo.Attribute.AttributeName;
			// 根据Attribute的名称设置SkillCostType
			if (CostTypeName=="HP")	CostType = ESkillCostType::HP;
			if (CostTypeName=="MP")	CostType = ESkillCostType::MP;
			if (CostTypeName=="SP")	CostType = ESkillCostType::SP;
			return FS_SkillInfo(CD,CostType,CostValue,GetClass());
		}
	}
	return FS_SkillInfo();
}
