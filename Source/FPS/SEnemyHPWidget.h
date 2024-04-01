// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class FPS_API SEnemyHPWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEnemyHPWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void ChangeColor(float HP);
	TSharedPtr<class SProgressBar> HPBar;
private:
	//½á¹ûÑÕÉ«
	FLinearColor ResultColor;
};
