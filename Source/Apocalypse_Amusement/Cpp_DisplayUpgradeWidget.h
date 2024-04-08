#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.h"
#include "Components/VerticalBox.h"
#include "Cpp_DisplayUpgradeWidget.generated.h"

UCLASS()
class APOCALYPSE_AMUSEMENT_API UCpp_DisplayUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisplayUpgrades(TArray<TSubclassOf<ACpp_Upgrade>> RandomUpgrades, ACPP_Player* Player);

	void RemoveAllWidgets();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TArray<ULevelUpWidget*> LevelUpWidgets;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class ULevelUpWidget> levelUpWidgetBP;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;
};
