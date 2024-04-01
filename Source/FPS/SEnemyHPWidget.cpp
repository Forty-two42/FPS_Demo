// Fill out your copyright notice in the Description page of Project Settings.


#include "SEnemyHPWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEnemyHPWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SAssignNew(HPBar,SProgressBar)
	];
	
}
void SEnemyHPWidget::ChangeColor(float HP)
{
	HP = FMath::Clamp<float>(HP, 0.0f, 1.0f);
	HPBar->SetPercent(HP);
	ResultColor = FLinearColor(1.f - HP, HP, 0.f, 1.f);
	HPBar->SetFillColorAndOpacity(FSlateColor(ResultColor));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
