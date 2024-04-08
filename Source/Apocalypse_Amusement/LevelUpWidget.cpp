// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"
#include "Components/Button.h"
#include "CPP_Player.h"
#include "Cpp_DisplayUpgradeWidget.h"
#include "Kismet/GameplayStatics.h"

void ULevelUpWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the button click event
    if (Button)
    {
        Button->OnClicked.AddDynamic(this, &ULevelUpWidget::OnButtonClick);
    }

}

void ULevelUpWidget::OnButtonClick()
{
    // Assuming that you have a reference to the widget instance
    if (!IsValid(this))
    {
        UE_LOG(LogTemp, Error, TEXT("Widget instance is not valid!"));
        return;
    }

    // Call player function to select upgrade
    if (Player)
    {
        Player->OnUpgradeSelected(Upgrade);
    }

    // Remove all widgets from the screen
    if (DisplayWidget && DisplayWidget->IsValidLowLevel())
    {
        DisplayWidget->RemoveAllWidgets();
    }
    
    // UnPause the Game
    UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void ULevelUpWidget::SetWeaponName(const FString& NewText)
{
    if (WeaponName)
    {
        WeaponName->SetText(FText::FromString(NewText));
    }
}

void ULevelUpWidget::SetWeaponDescription(const FString& NewDescription)
{
    if (WeaponDescription)
    {
        WeaponDescription->SetText(FText::FromString(NewDescription));
    }
}

void ULevelUpWidget::SetWeaponLevel(int32 NewLevel)
{
    if (WeaponLevel)
    {
        FText LevelText = FText::FromString(FString::Printf(TEXT("%d"), NewLevel));
        WeaponLevel->SetText(LevelText);
    }
}

void ULevelUpWidget::SetPlayer(ACPP_Player* newPlayer)
{
    Player = newPlayer;
}

void ULevelUpWidget::SetUpgrade(TSubclassOf<class ACpp_Upgrade> newUpgrade)
{
    Upgrade = newUpgrade;
}

void ULevelUpWidget::SetDisplayWidget(UCpp_DisplayUpgradeWidget* newDisplayWidget)
{
    DisplayWidget = newDisplayWidget;
}
