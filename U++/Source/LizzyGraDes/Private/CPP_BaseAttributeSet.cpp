// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseAttributeSet.h"
#include "GameplayEffectExtension.h"

void UCPP_BaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(Data.EvaluatedData.Attribute==GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(),0.0f,GetMaxHP()));
	}
	if(Data.EvaluatedData.Attribute==GetMPAttribute())
	{
		SetMP(FMath::Clamp(GetMP(),0.0f,GetMaxMP()));
	}
	if(Data.EvaluatedData.Attribute==GetSPAttribute())
	{
		SetSP(FMath::Clamp(GetSP(),0.0f,GetMaxSP()));
	}
	if(Data.EvaluatedData.Attribute==GetCarriedResourceAttribute())
	{
		SetCarriedResource(FMath::Clamp(GetCarriedResource(),0.0f,GetMaxCarriedResource()));
	}
}
