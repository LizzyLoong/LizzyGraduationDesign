// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "CPP_BaseAbility.h"
#include "CPP_BaseAttributeSet.h"

// Sets default values
ACPP_BaseCharacter::ACPP_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	TObjectPtr<UAbilitySystemComponent> OwnedAbilitySystemComponent=this->FindComponentByClass<UAbilitySystemComponent>();
	if(OwnedAbilitySystemComponent)
	{
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetHPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnHPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMaxHPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMaxHPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMaxMPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMaxMPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetSPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnSPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMaxSPAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMaxSPAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetHRAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnHRAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMRAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMRAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetATKAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnATKAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMAGAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMAGAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetATKspeedAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnATKspeedAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMAGspeedAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMAGspeedAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetATKsuckAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnATKsuckAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMAGsuckAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMAGsuckAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetDEFAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnDEFAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMDEFAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMDEFAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetDEFdecayAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnDEFdecayAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMDEFdecayAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMDEFdecayAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetDEFpenetrateAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnDEFpenetrateAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetMDEFpenetrateAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnMDEFpenetrateAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetCRTAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnCRTAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetCRTdamAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnCRTdamAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetRunAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnRunAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetToughAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnToughAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetHRintenseAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnHRintenseAttributeChanged);
		OwnedAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCPP_BaseAttributeSet::GetExtentAttribute()).AddUObject(this,&ACPP_BaseCharacter::OnExtentAttributeChanged);
	}
}

FS_SkillInfo ACPP_BaseCharacter::GameplayAbilityInfo(TSubclassOf<UCPP_BaseAbility> AbilityClass, int Level)
{
	UAbilitySystemComponent *OwnAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	UCPP_BaseAbility* LearnedAbilityInstance=AbilityClass->GetDefaultObject<UCPP_BaseAbility>();
	if(OwnAbilitySystemComponent && LearnedAbilityInstance)
	{
		return LearnedAbilityInstance->GetAbilityInfo(Level);
	}
	return FS_SkillInfo();
}


// Called every frame
void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

