//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
//#include "Components/TextBlock.h"
//#include "Cpp_LevelUpWidget.generated.h"
//
///**
// * 
// */
//UCLASS()
//class APOCALYPSE_AMUSEMENT_API UCpp_LevelUpWidget : public UUserWidget
//{
//	GENERATED_BODY()
//
//public:
//
//	UFUNCTION(BlueprintCallable, Category = "MyWidget")
//	void OnButton1Click();
//	UFUNCTION(BlueprintCallable, Category = "MyWidget")
//	void OnButton2Click();
//	UFUNCTION(BlueprintCallable, Category = "MyWidget")
//	void OnButton3Click();
//
//	// Function to set the text for the TextBlock
//
//	void SetWeaponName1(const FString& NewText);
//	void SetWeaponDescription1(const FString& NewDescription);
//	void SetWeaponLevel1(int32 NewLevel);
//	void SetWeapon1Index(int32 Index);
//
//	void SetWeaponName2(const FString& NewText);
//	void SetWeaponDescription2(const FString& NewDescription);
//	void SetWeaponLevel2(int32 NewLevel);
//	void SetWeapon2Index(int32 Index);
//
//	void SetWeaponName3(const FString& NewText);
//	void SetWeaponDescription3(const FString& NewDescription);
//	void SetWeaponLevel3(int32 NewLevel);
//	void SetWeapon3Index(int32 Index);
//
//
//protected:
//	virtual void NativeConstruct() override;
//
//private:
//	// Weapon 1
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponName1;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponDescription1;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponLevel1;
//	int32 Weapon1Index;
//	UPROPERTY(meta = (BindWidget))
//	class UButton* Button1;
//
//	// Weapon 2
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponName2;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponDescription2;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponLevel2;
//	int32 Weapon2Index;
//	UPROPERTY(meta = (BindWidget))
//	class UButton* Button2;
//
//	// Weapon 3
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponName3;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponDescription3;
//	UPROPERTY(meta = (BindWidget))
//	UTextBlock* WeaponLevel3;
//	int32 Weapon3Index;
//	UPROPERTY(meta = (BindWidget))
//	class UButton* Button3;
//	
//};
