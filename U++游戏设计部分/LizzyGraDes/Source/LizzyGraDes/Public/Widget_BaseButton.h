// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Widget_BaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonDoubleClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);


UCLASS()
class LIZZYGRADES_API UWidget_BaseButton : public UButton
{
	GENERATED_BODY()
	
public:
	UWidget_BaseButton();



	// 单击事件代理
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonClicked OnSingleClicked;

	// 双击事件代理
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
	FOnButtonDoubleClicked OnDoubleClicked;


/*
	// 设置双击检测的时间阈值（毫秒）
	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetDoubleClickThreshold(float NewThreshold);



protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	// 处理按钮点击
	void HandleButtonClick();
    
	// 处理单机事件
	void HandleSingleClick();
    
	// 重置点击状态
	void ResetClickState();

	// 双击检测的时间阈值（秒）
	UPROPERTY(EditAnywhere, Category = "Button", meta = (ClampMin = "0.05", ClampMax = "1.0"))
	float DoubleClickThreshold;

	// 上次点击时间
	float LastClickTime;

	// 是否正在等待第二次点击
	bool bWaitingForSecondClick;
    
	// 是否已处理单击
	bool bSingleClickHandled;
    
	// 定时器句柄
	FTimerHandle ClickTimerHandle;
*/
};
