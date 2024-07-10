// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FTextArray {
	
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Texts;
};

/**
 * Data asset containing the possible level dialogs
 */
UCLASS()
class PROJECTSAILOR_API UDialogDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FTextArray> ObjectsArray;

};
