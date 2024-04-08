//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Cpp_LevelUpWidget.h"
//#include "Components/Button.h"
//#include "CPP_Player.h"
//#include "Kismet/GameplayStatics.h"
//
//void UCpp_LevelUpWidget::NativeConstruct()
//{
//    Super::NativeConstruct();
//    
//    // Bind the button click event
//    if (Button1)
//    {
//        Button1->OnClicked.AddDynamic(this, &UCpp_LevelUpWidget::OnButton1Click);
//    }
//    if (Button2)
//    {
//        Button2->OnClicked.AddDynamic(this, &UCpp_LevelUpWidget::OnButton2Click);
//    }
//    if (Button3)
//    {
//        Button3->OnClicked.AddDynamic(this, &UCpp_LevelUpWidget::OnButton3Click);
//    }
//
//}
//
//void UCpp_LevelUpWidget::OnButton1Click()
//{
//    // Assuming that you have a reference to the widget instance
//    if (!IsValid(this))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Widget instance is not valid!"));
//        return;
//    }
//
//    // Call player function to select upgrade
//    ACPP_Player* Player = Cast<ACPP_Player>(GetOwningPlayerPawn());
//    if (Player)
//    {
//        Player->OnSelected(Weapon1Index);
//    }
//
//    // Remove the widget from its parent (destroy it)
//    RemoveFromParent();
//    // UnPause the Game
//    UGameplayStatics::SetGamePaused(GetWorld(), false);
//}
//
//void UCpp_LevelUpWidget::OnButton2Click()
//{
//    // Assuming that you have a reference to the widget instance
//    if (!IsValid(this))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Widget instance is not valid!"));
//        return;
//    }
//
//    // Call player function to select upgrade
//    ACPP_Player* Player = Cast<ACPP_Player>(GetOwningPlayerPawn());
//    if (Player)
//    {
//        Player->OnSelected(Weapon2Index);
//    }
//
//    // Remove the widget from its parent (destroy it)
//    RemoveFromParent();
//    // UnPause the Game
//    UGameplayStatics::SetGamePaused(GetWorld(), false);
//}
//
//void UCpp_LevelUpWidget::OnButton3Click()
//{
//    // Assuming that you have a reference to the widget instance
//    if (!IsValid(this))
//    {
//        UE_LOG(LogTemp, Error, TEXT("Widget instance is not valid!"));
//        return;
//    }
//
//    // Call player function to select upgrade
//    ACPP_Player* Player = Cast<ACPP_Player>(GetOwningPlayerPawn());
//    if (Player)
//    {
//        Player->OnSelected(Weapon3Index);
//    }
//
//    // Remove the widget from its parent (destroy it)
//    RemoveFromParent();
//    // UnPause the Game
//    UGameplayStatics::SetGamePaused(GetWorld(), false);
//}
//
//void UCpp_LevelUpWidget::SetWeaponName1(const FString& NewText)
//{
//    if (WeaponName1)
//    {
//        WeaponName1->SetText(FText::FromString(NewText));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponDescription1(const FString& NewDescription)
//{
//    if (WeaponDescription1)
//    {
//        WeaponDescription1->SetText(FText::FromString(NewDescription));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponLevel1(int32 NewLevel)
//{
//    if (WeaponLevel1)
//    {
//        FText LevelText = FText::FromString(FString::Printf(TEXT("%d"), NewLevel));
//        WeaponLevel1->SetText(LevelText);
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeapon1Index(int32 Index)
//{
//    Weapon1Index = Index;
//}
//
//void UCpp_LevelUpWidget::SetWeaponName2(const FString& NewText)
//{
//    if (WeaponName2)
//    {
//        WeaponName2->SetText(FText::FromString(NewText));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponDescription2(const FString& NewDescription)
//{
//    if (WeaponDescription2)
//    {
//        WeaponDescription2->SetText(FText::FromString(NewDescription));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponLevel2(int32 NewLevel)
//{
//    if (WeaponLevel2)
//    {
//        FText LevelText = FText::FromString(FString::Printf(TEXT("%d"), NewLevel));
//        WeaponLevel2->SetText(LevelText);
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeapon2Index(int32 Index)
//{
//    Weapon2Index = Index;
//}
//
//void UCpp_LevelUpWidget::SetWeaponName3(const FString& NewText)
//{
//    if (WeaponName3)
//    {
//        WeaponName3->SetText(FText::FromString(NewText));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponDescription3(const FString& NewDescription)
//{
//    if (WeaponDescription3)
//    {
//        WeaponDescription3->SetText(FText::FromString(NewDescription));
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeaponLevel3(int32 NewLevel)
//{
//    if (WeaponLevel3)
//    {
//        FText LevelText = FText::FromString(FString::Printf(TEXT("%d"), NewLevel));
//        WeaponLevel3->SetText(LevelText);
//    }
//}
//
//void UCpp_LevelUpWidget::SetWeapon3Index(int32 Index)
//{
//    Weapon3Index = Index;
//}
