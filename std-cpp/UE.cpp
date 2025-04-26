

USTRUCT()
struct FDataRow
{
	GENERATED_BODY()
	TArray<FString> Conditions;
	TArray<FString> Decisions;
};

USTRUCT()
struct FTreeNode
{
	GENERATED_BODY()
	FString Attribute;
	TMap<FString, TSharedPtr<FTreeNode>> Children;
	FString Decision;
};



double ACPP_BaseCharacter::CalculateEntropy(const TArray<FDataRow>& Dataset, int32 TargetIndex)
{
	TMap<FString, int32> Freq;
	for (const auto& Row : Dataset)
	{
		Freq[Row.Decisions[TargetIndex]]++;
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
		UE_LOG(LogTemp, Error, TEXT("Invalid decision tree root node!"));
		return TEXT("Invalid");
	}
	if (!Root->Decision.IsEmpty())
	{
		return Root->Decision;
	}
	int32 AttrIndex = Attributes.Find(Root->Attribute);
	if (AttrIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute %s not found in attributes list"), *Root->Attribute);
		return TEXT("Unknown");
	}
	if (!Sample.Conditions.IsValidIndex(AttrIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sample data missing attribute at index %d"), AttrIndex);
		return TEXT("Unknown");
	}
	
	const FString& AttrValue = Sample.Conditions[AttrIndex];
	const TSharedPtr<FTreeNode>* ChildNodePtr = Root->Children.Find(AttrValue);
	if (!ChildNodePtr || !ChildNodePtr->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("No child node found for attribute value: %s"), *AttrValue);
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

    // 选择最佳划分属性（虚幻风格参数传递）
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
void ACPP_BaseCharacter::SetTrees(TArray<TSharedPtr<FTreeNode>>& Root, TArray<FDataRow> Dataset,TArray<FString> Attributes)
{
	for(int32 TargetIndex = 0; TargetIndex < 3; ++TargetIndex)
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


FString str = Predict(Trees[0],sample,attributes);






