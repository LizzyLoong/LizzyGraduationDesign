// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_BaseButton.h"
#include "TimerManager.h"


UWidget_BaseButton::UWidget_BaseButton()
{

}

/*
UClickableButton::UClickableButton()
{
    // 默认双击阈值为300ms
    DoubleClickThreshold = 0.3f;
    LastClickTime = 0.0f;
    bWaitingForSecondClick = false;
    bSingleClickHandled = false;
}

void UClickableButton::SetDoubleClickThreshold(float NewThreshold)
{
    // 将毫秒转换为秒
    DoubleClickThreshold = FMath::Clamp(NewThreshold / 1000.0f, 0.05f, 1.0f);
}

TSharedRef<SWidget> UClickableButton::RebuildWidget()
{
    TSharedRef<SWidget> Widget = Super::RebuildWidget();
    
    // 绑定点击事件
    if (GetCachedWidget().IsValid())
    {
        SetOnClicked(FOnClicked::CreateUObject(this, &UClickableButton::HandleButtonClick));
    }
    
    return Widget;
}

FReply UClickableButton::HandleButtonClick()
{
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    const float TimeSinceLastClick = CurrentTime - LastClickTime;
    
    // 如果是第一次点击或超过阈值
    if (!bWaitingForSecondClick || TimeSinceLastClick > DoubleClickThreshold)
    {
        // 重置状态
        ResetClickState();
        
        // 设置第一次点击状态
        bWaitingForSecondClick = true;
        LastClickTime = CurrentTime;
        
        // 设置定时器，在阈值后处理单击
        GetWorld()->GetTimerManager().SetTimer(
            ClickTimerHandle,
            this,
            &UClickableButton::HandleSingleClick,
            DoubleClickThreshold,
            false
        );
    }
    // 在阈值内第二次点击 - 双击事件
    else if (bWaitingForSecondClick && TimeSinceLastClick <= DoubleClickThreshold)
    {
        // 清除单击定时器
        GetWorld()->GetTimerManager().ClearTimer(ClickTimerHandle);
        
        // 广播双击事件
        OnDoubleClicked.Broadcast();
        
        // 重置状态
        ResetClickState();
    }
    
    return FReply::Handled();
}

void UClickableButton::HandleSingleClick()
{
    // 如果没有处理过单击
    if (!bSingleClickHandled && bWaitingForSecondClick)
    {
        // 广播单击事件
        OnSingleClicked.Broadcast();
        bSingleClickHandled = true;
        
        // 重置状态（但保留等待状态以允许后续双击）
        // 在下次点击或超时后会完全重置
    }
}

void UClickableButton::ResetClickState()
{
    bWaitingForSecondClick = false;
    bSingleClickHandled = false;
    LastClickTime = 0.0f;
}
*/