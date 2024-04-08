// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSE_AMUSEMENT_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MyWidget")
	void OnButtonClick();

	void SetWeaponName(const FString& NewText);
	void SetWeaponDescription(const FString& NewDescription);
	void SetWeaponLevel(int32 NewLevel);
	void SetPlayer(class ACPP_Player* newPlayer);
	void SetUpgrade(TSubclassOf<class ACpp_Upgrade> newUpgrade);
	void SetDisplayWidget(class UCpp_DisplayUpgradeWidget* newDisplayWidget);

protected:
	virtual void NativeConstruct() override;

private:
	// Weapon 1
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponDescription;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* WeaponLevel;
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	TSubclassOf<class ACpp_Upgrade> Upgrade;
	class ACPP_Player* Player;
	class UCpp_DisplayUpgradeWidget* DisplayWidget;

};
