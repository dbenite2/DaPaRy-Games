// Property of DaPaRy Games


#include "SailorInstance.h"

USailorInstance::USailorInstance() {
	GameState = new FCompletedLevelState();
	GameState->Tutorial = FLevelStatus();
	GameState->FirstLevel = FLevelStatus();
	GameState->SecondLevel = FLevelStatus();
	GameState->ThirdLevel = FLevelStatus();

	LevelStatusMap.Add("Level_beach_01", GameState->Tutorial);
	LevelStatusMap.Add("Level_cave_02", GameState->FirstLevel);
	LevelStatusMap.Add("RickyTestLevel", GameState->SecondLevel);
	LevelStatusMap.Add("thirdLevel", GameState->ThirdLevel);
}


FLevelStatus USailorInstance::GetCurrentLevelStatus(const FString& LevelName) const {
	if (const FLevelStatus* Status = LevelStatusMap.Find(LevelName)) {
		return *Status;
	}
	return GameState->Tutorial;
}

void USailorInstance::SetCurrentLevelStatus(const FString& LevelName, int32 GoalIndex) {
	if (FLevelStatus* Status = LevelStatusMap.Find(LevelName)) {
		SetLevelGoals(*Status, GoalIndex);
	}
}

void USailorInstance::SetLevelGoals(FLevelStatus& CurrentLevel,int32 GoalIndex) {
	switch (GoalIndex) {
	case 0:
		CurrentLevel.bLevelComplete = true;
		break;
	case 1:
	default:
		CurrentLevel.bInitial = false;
		CurrentLevel.bGoal1Complete = true;
		break;
	case 2:
		CurrentLevel.bGoal2Complete = true;
		break;
	case 3:
		CurrentLevel.bGoal3Complete = true;
		break;
	}
}

