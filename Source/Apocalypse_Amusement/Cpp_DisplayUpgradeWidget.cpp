#include "Cpp_DisplayUpgradeWidget.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h" 

#include "Cpp_Upgrade.h"
#include "CPP_Player.h"

void UCpp_DisplayUpgradeWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCpp_DisplayUpgradeWidget::DisplayUpgrades(TArray<TSubclassOf<ACpp_Upgrade>> RandomUpgrades, ACPP_Player* Player)
{
    // Clear any existing widgets
    for (ULevelUpWidget* Widget : LevelUpWidgets)
    {
        Widget->RemoveFromParent();
    }
    LevelUpWidgets.Empty();

    // Create a new widget for each upgrade
    for (TSubclassOf<ACpp_Upgrade> UpgradeClass : RandomUpgrades)
    {
        ULevelUpWidget* NewWidget = CreateWidget<ULevelUpWidget>(GetWorld(), levelUpWidgetBP);
        NewWidget->SetPlayer(Player);
        NewWidget->SetUpgrade(UpgradeClass);
        NewWidget->SetDisplayWidget(this);

        // Check if an instance of this subclass has already been spawned
        TMap<TSubclassOf<ACpp_Upgrade>, ACpp_Upgrade*> Tmap = Player->GetTmap();
        ACpp_Upgrade** SpawnedUpgrade = Tmap.Find(UpgradeClass);

        // If spawned, access information from class
        if (SpawnedUpgrade)
        {
            NewWidget->SetWeaponName((*SpawnedUpgrade)->GetName());
            NewWidget->SetWeaponDescription((*SpawnedUpgrade)->GetDescription());
            NewWidget->SetWeaponLevel((*SpawnedUpgrade)->GetUpgradeLevel());
        }
        // If not spawned, access information from class defaults
        else if (UpgradeClass != nullptr)
        {
            ACpp_Upgrade* DefaultObject = UpgradeClass->GetDefaultObject<ACpp_Upgrade>();
            if (DefaultObject != nullptr)
            {
                NewWidget->SetWeaponName(DefaultObject->GetName());
                NewWidget->SetWeaponDescription(DefaultObject->GetDescription());
                NewWidget->SetWeaponLevel(DefaultObject->GetUpgradeLevel());
            }
        }

        // Add the new widget to the screen and to our array
        if (VerticalBox)
        {
            VerticalBox->AddChildToVerticalBox(NewWidget);
        }
        LevelUpWidgets.Add(NewWidget);
    }
}

void UCpp_DisplayUpgradeWidget::RemoveAllWidgets()
{
    // Iterate over the array of widgets
    for (ULevelUpWidget* Widget : LevelUpWidgets)
    {
        // Remove the widget from its parent
        if (Widget && Widget->IsValidLowLevel())
        {
            Widget->RemoveFromParent();
        }
    }

    // Clear the array
    LevelUpWidgets.Empty();
}
