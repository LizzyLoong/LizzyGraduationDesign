// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "CPP_BaseAttributeSet.h"


ACPP_BaseCharacter::ACPP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	SetTrees(Trees,dataset,attributes);
}
void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ACPP_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	// SetTrees(Trees,dataset,attributes);
	
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


void ACPP_BaseCharacter::SetCharacterAttributeComment()
{
	TObjectPtr<UAbilitySystemComponent> OwnedAbilitySystemComponent=this->FindComponentByClass<UAbilitySystemComponent>();
	/*
	if(OwnedAbilitySystemComponent)
	{
		//OwnedAbilitySystemComponent->GetAttributeSet(UCPP_BaseAttributeSet)
		const UCPP_BaseAttributeSet* OwnedAttributeSet=OwnedAbilitySystemComponent->GetSet<UCPP_BaseAttributeSet>();
		
	}
	*/
	const UCPP_BaseAttributeSet* OwnedAttributeSet=OwnedAbilitySystemComponent->GetSet<UCPP_BaseAttributeSet>();
	float CurrentATK = OwnedAttributeSet->GetATK();
	float CurrentMAG = OwnedAttributeSet->GetMAG();
	float CurrentDEF = OwnedAttributeSet->GetDEF();
	float CurrentMDEF = OwnedAttributeSet->GetMDEF();

	// Live part
	float SubDEF=CurrentDEF-50;
	float SubMDEF=CurrentMDEF-50;
	if(SubDEF<=0 && SubMDEF<=0)
	{
		LiveComment=ELiveComment::HHP;
	}
	else
	{
		if(SubDEF>SubMDEF)	LiveComment=ELiveComment::HDEF;
		else LiveComment=ELiveComment::HMDEF;
	}
	// Output part
	float SubATK=CurrentATK-100;
	float SubMAG=CurrentMAG-100;
	if(SubATK<=0 && SubMAG<=0)
	{
		OutputComment=CharacterInfo.DamageKind;
	}
	else
	{
		if(SubATK>SubMAG)	OutputComment=EOutputComment::HATK;
		else OutputComment=EOutputComment::HMAG;
	}
}











double ACPP_BaseCharacter::CalculateEntropy(const TArray<FDataRow>& Dataset, int32 TargetIndex)
{
	TMap<FString, int32> Freq;
	for (const auto& Row : Dataset)
	{
		Freq.FindOrAdd(Row.Decisions[TargetIndex])++;
		// Freq[Row.Decisions[TargetIndex]]++;
	}

	double Entropy = 0.0;
	for (const auto& Pair : Freq)
	{
		double Prob = static_cast<double>(Pair.Value) / Dataset.Num();
		Entropy -= Prob * FMath::Log2(Prob);
	}
	return Entropy;
}

double ACPP_BaseCharacter::CalculateInfoGain(const TArray<FDataRow>& Dataset, int32 AttrIdx, int32 TargetIdx)
{
	TMap<FString, TArray<FDataRow>> Subsets;
	for (const auto& Row : Dataset)
	{
		Subsets.FindOrAdd(Row.Conditions[AttrIdx]).Add(Row);
	}

	double SubsetEntropy = 0.0;
	for (const auto& Subset : Subsets)
	{
		double Weight = static_cast<double>(Subset.Value.Num()) / Dataset.Num();
		SubsetEntropy += Weight * CalculateEntropy(Subset.Value, TargetIdx);
	}

	return CalculateEntropy(Dataset, TargetIdx) - SubsetEntropy;
}

int32 ACPP_BaseCharacter::ChooseBestAttribute(const TArray<FDataRow>& Dataset, const TArray<bool>& UsedAttributes,int32 TargetIdx)
{
	double MaxGain = -1;
	int32 BestAttr = -1;

	for (int32 i = 0; i < UsedAttributes.Num(); ++i)
	{
		if (!UsedAttributes[i])
		{
			double Gain = CalculateInfoGain(Dataset, i, TargetIdx);
			if (Gain > MaxGain)
			{
				MaxGain = Gain;
				BestAttr = i;
			}
		}
	}
	return BestAttr;
}

FString ACPP_BaseCharacter::Predict(const TSharedPtr<FTreeNode>& Root, const FDataRow& Sample,const TArray<FString>& Attributes)
{
	if (!Root.IsValid())
	{
		return TEXT("Invalid");
	}
	if (!Root->Decision.IsEmpty())
	{
		return Root->Decision;
	}
	int32 AttrIndex = Attributes.Find(Root->Attribute);
	if (AttrIndex == INDEX_NONE)
	{
		return TEXT("Unknown");
	}
	if (!Sample.Conditions.IsValidIndex(AttrIndex))
	{
		return TEXT("Unknown");
	}
	const FString& AttrValue = Sample.Conditions[AttrIndex];
	const TSharedPtr<FTreeNode>* ChildNodePtr = Root->Children.Find(AttrValue);
	if (!ChildNodePtr || !ChildNodePtr->IsValid())
	{
		return TEXT("Unknown");
	}
	return Predict(*ChildNodePtr, Sample, Attributes);
}

FString ACPP_BaseCharacter::GetPluralityClass(const TMap<FString, int32>& ClassCounts)
{
	if (ClassCounts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty class counts in plurality calculation"));
		return FString();
	}

	FString MajorityClass;
	int32 MaxCount = 0;

	// 遍历统计结果
	for (const auto& Pair : ClassCounts)
	{
		if (Pair.Value > MaxCount)
		{
			MaxCount = Pair.Value;
			MajorityClass = Pair.Key;
		}
		else if (Pair.Value == MaxCount)
		{
			// 处理平票情况（可选：根据业务逻辑调整）
			MajorityClass = FString::Printf(TEXT("%s/%s"), *MajorityClass, *Pair.Key);
		}
	}
	return MajorityClass;
}

TSharedPtr<FTreeNode> ACPP_BaseCharacter::BuildDecisionTree(const TArray<FDataRow>& Dataset,const TArray<FString>& Attributes, TArray<bool> UsedAttributes, int32 TargetIdx)
{
	// 参数有效性验证
    if (Dataset.IsEmpty() || Attributes.IsEmpty() || TargetIdx < 0 || TargetIdx >= Attributes.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid input parameters for decision tree construction"));
        return nullptr;
    }

    // 创建节点（使用虚幻的智能指针系统）
    TSharedPtr<FTreeNode> Node = MakeShared<FTreeNode>();
    
    // 类别计数（使用虚幻的容器）
    TMap<FString, int32> ClassCounts;
    for (const FDataRow& Row : Dataset)
    {
        // 数据有效性检查
        if (Row.Decisions.IsValidIndex(TargetIdx))
        {
            const FString& Decision = Row.Decisions[TargetIdx];
            ClassCounts.FindOrAdd(Decision)++;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid target index in data row"));
        }
    }

    // 终止条件1：所有样本属于同一类别
    if (ClassCounts.Num() == 1)
    {
        Node->Decision = ClassCounts.CreateIterator().Key();
        return Node;
    }

    // 选择最佳划分属性
    const int32 BestAttr = ChooseBestAttribute(Dataset, UsedAttributes, TargetIdx);
    
    // 终止条件2：没有可用属性或选择失败
    if (BestAttr == INDEX_NONE || !Attributes.IsValidIndex(BestAttr))
    {
        Node->Decision = GetPluralityClass(ClassCounts); // 需要实现多数表决辅助函数
        return Node;
    }

    // 设置节点属性
    Node->Attribute = Attributes[BestAttr];
    
    // 更新已用属性（使用Unreal的内存布局优化）
    TArray<bool> NewUsedAttributes = UsedAttributes;
    if (NewUsedAttributes.IsValidIndex(BestAttr))
    {
        NewUsedAttributes[BestAttr] = true;
    }

    // 创建数据子集（使用虚幻的容器和算法）
    TMap<FString, TArray<FDataRow>> Subsets;
    for (const FDataRow& Row : Dataset)
    {
        if (Row.Conditions.IsValidIndex(BestAttr))
        {
            const FString& Key = Row.Conditions[BestAttr];
            Subsets.FindOrAdd(Key).Add(Row);
        }
    }

    // 递归构建子树
    for (auto& SubsetPair : Subsets)
    {
        const FString& AttributeValue = SubsetPair.Key;
        TArray<FDataRow>& SubsetData = SubsetPair.Value;

        if (SubsetData.IsEmpty())
        {
            // 创建叶节点
            TSharedPtr<FTreeNode> LeafNode = MakeShared<FTreeNode>();
            LeafNode->Decision = GetPluralityClass(ClassCounts);
            Node->Children.Add(AttributeValue, LeafNode);
        }
        else
        {
            // 递归调用（使用移动语义优化大数据集）
            TSharedPtr<FTreeNode> ChildNode = BuildDecisionTree(
                SubsetData,
                Attributes,
                NewUsedAttributes,
                TargetIdx
            );
            
            if (ChildNode.IsValid())
            {
                Node->Children.Add(AttributeValue, ChildNode);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to build child node for attribute value: %s"), *AttributeValue);
            }
        }
    }

    return Node;
}

void ACPP_BaseCharacter::SetTrees(TArray<TSharedPtr<FTreeNode>>& Root, TArray<FDataRow> Dataset,TArray<FString> Attributes)
{
	for(int32 TargetIndex = 0; TargetIndex < 3; TargetIndex++)
	{
		TArray<bool> UsedAttributes;
		UsedAttributes.Init(false,5);
		TSharedPtr<FTreeNode> NewTree = BuildDecisionTree(Dataset,Attributes,UsedAttributes,TargetIndex);
		// 空指针安全检查
		if (NewTree.IsValid())
		{
			Root.Add(NewTree);
		}
	}
}





void ACPP_BaseCharacter::SetPredictComment(ACPP_BaseCharacter* TargetActor)
{
	FString OwnLegendComment=EnumToString(this->LegendComment);
	FString OwnOutputComment=EnumToString(this->OutputComment);
	FString OwnLiveComment=EnumToString(this->LiveComment);
	FString TargetOutputComment=EnumToString(TargetActor->OutputComment);
	FString TargetLiveComment=EnumToString(TargetActor->LiveComment);
	this->PredictComment = {
		{OwnLegendComment,OwnOutputComment,OwnLiveComment,TargetOutputComment,TargetLiveComment},
		{}
	};
}

FString ACPP_BaseCharacter::CallPredictAndGetAdvice(int32 TreeIndex, ACPP_BaseCharacter* TargetActor,FDataRow TwoLegendComment)
{
	SetPredictComment(TargetActor);
	return Predict(Trees[TreeIndex],TwoLegendComment,attributes);
}




























