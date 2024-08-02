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
	DefaultState UMETA(DisplayName = "Default State"),
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

	//카운트다운함수
	UFUNCTION()
	void CountDown(float DeltaTime);

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float roundTimer = 60.f;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	float gameTimer;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// 현재 게임 상태
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category="GameState")
	EGameState CurrentState = EGameState::DefaultState;

	// 게임 상태를 설정하는 함수
	UFUNCTION()
	void SetGameState(EGameState NewState);

	// 새로운 상태에 따라 행동을 처리하는 함수
	UFUNCTION()
	void HandleNewState(EGameState NewState);

	// 게임 시작 처리
	UFUNCTION()
	void StartGame();

	// 라운드 시작 처리
	UFUNCTION()
	void StartRound();

	// 게임 오버 조건 체크
	UFUNCTION()
	void CheckForGameOver();

	// 게임 오버 조건을 만족하는지 체크하는 함수
	UFUNCTION()
	bool IsGameOverConditionMet();

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TSubclassOf<class UinGameUI> inGameWidget;
	//상태 초기화(플레이어 HP, 타이머 시간, 라운드 표시 반영)

public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UinGameUI* inGameUI;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class ACPP_Tekken8CharacterParent* playerA;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class ACPP_Tekken8CharacterParent* playerB;


	// ** for make Character **//
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	TSubclassOf<class ACPP_CharacterPaul> Player1Class;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	TSubclassOf<class ACPP_CharacterPaul> Player2Class;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	class ACPP_Tekken8CharacterParent* Player1;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	class ACPP_Tekken8CharacterParent* Player2;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite)
	TSubclassOf<class AAICharacter> PlayerAIClass;


	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	class ACPP_Tekken8CharacterParent* PlayerAI1;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	class ACPP_Tekken8CharacterParent* PlayerAI2;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<class APawn> CameraPawn;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	APawn* SpawnedCameraPawn;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Round")
	int32 Player1Score;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Round")
	int32 Player2Score;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Round")
	int32 Player1HP;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Round")
	int32 Player2HP;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = "Round")
	AActor* Winner;

	UFUNCTION()
	void SetupCameraViewTarget();
	
	UFUNCTION()
	void CheckRoundWinner();
	
	UFUNCTION()
	void CheckFinalWinner();

	UFUNCTION()
	void HandleRoundEnd(AActor* RoundWinner);

	UFUNCTION()
	void CheckPlayerHP(float DeltaTime);
	
	UFUNCTION()
	int32 GetPlayerHP(ACharacter* Player);
};
