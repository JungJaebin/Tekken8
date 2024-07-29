// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_MH.generated.h"

/**
 * 
 */
// 게임 상태를 나타내는 Enum
UENUM(BlueprintType , Category="GameState")
enum class EGameState : uint8
{
	GameStart UMETA(DisplayName = "Game Start"),
	RoundStart UMETA(DisplayName = "Round Start"),
	InProgress UMETA(DisplayName = "In Progress"),
	RoundEnd UMETA(DisplayName = "Round End"),
	GameOver UMETA(DisplayName = "Game Over")
};

UCLASS()
class JMH_API AGameMode_MH : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameMode_MH();

protected:
	virtual void BeginPlay() override;

	// 현재 게임 상태
	EGameState CurrentState;
	
	// 게임 상태를 설정하는 함수
	void SetGameState(EGameState NewState);

	// 새로운 상태에 따라 행동을 처리하는 함수
	void HandleNewState(EGameState NewState);

	// 게임 시작 처리
	void StartGame();

	// 라운드 시작 처리
	void StartRound();

	// 게임 오버 조건 체크
	void CheckForGameOver();

	// 게임 오버 조건을 만족하는지 체크하는 함수
	bool IsGameOverConditionMet();
	
};
