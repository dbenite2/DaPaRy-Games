// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SailorInstance.generated.h"

USTRUCT(BlueprintType)
struct FLevelStatus {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInitial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal1Complete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal2Complete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGoal3Complete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLevelComplete;

	FLevelStatus() {
		bInitial = true;
		bGoal1Complete = false;
		bGoal2Complete = false;
		bGoal3Complete = false;
		bLevelComplete = false;
	}
	
};

USTRUCT(BlueprintType)
struct FCompletedLevelState {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStatus Tutorial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStatus FirstLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStatus SecondLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLevelStatus ThirdLevel;
};

/**
 * Game instance
 * Holds all the state and the information of the game
 */
UCLASS()
class PROJECTSAILOR_API USailorInstance : public UGameInstance
{
	GENERATED_BODY()

	FCompletedLevelState* GameState;

	TMap<FString, FLevelStatus> LevelStatusMap;

	void SetLevelGoals(FLevelStatus& CurrentLevel, int32 GoalIndex);

public:

	USailorInstance();
	
	FLevelStatus GetCurrentLevelStatus(const FString& LevelName) const;

	void SetCurrentLevelStatus(const FString& LevelName, int32 GoalIndex);
	
};
