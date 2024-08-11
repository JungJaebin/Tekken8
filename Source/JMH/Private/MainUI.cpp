// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

#include "EnhancedInputComponent.h"
#include "MainGameInstance_MH.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	MainGameInstance = Cast<UMainGameInstance_MH>(GetWorld()->GetGameInstance());
	//ui클릭용 B,O 키 바인드해서 각자 캐릭터 선택할 수 있게 하기 // N,P는 취소
	//버튼 바인드
	Btn_Tournament->OnClicked.AddDynamic(this , &UMainUI::OnClickedTournament);
	Btn_PVSP->OnClicked.AddDynamic(this , &UMainUI::OnClickedPlayerVSPlayer);
	Btn_PVSCPU->OnClicked.AddDynamic(this , &UMainUI::OnClickedPlayerVSCPU);
	Btn_Left->OnClicked.AddDynamic(this , &UMainUI::OnClickedLeftSide);
	Btn_Right->OnClicked.AddDynamic(this , &UMainUI::OnClickedRightSide);
	Btn_Paul->OnClicked.AddDynamic(this , &UMainUI::UMainUI::OnClickedPaul);
	Btn_Random->OnClicked.AddDynamic(this , &UMainUI::UMainUI::OnClickedRandom);
	btn_Back->OnClicked.AddDynamic(this , &UMainUI::UMainUI::OnClickedEmptyBack);
}

void UMainUI::OnClickedTournament()
{
	ove_Empty->SetVisibility(ESlateVisibility::Visible);
	//토너먼트 선택이라고 변수 게임모드 전달
	/*
	if (Can_ChooseCharacter)
	{
		if (MainGameInstance)
		{
			MainGameInstance->GameModeSelectionIndex = 0;
		}
		//캐릭터 선택으로 이동
		WidgetSwitcher->SetActiveWidgetIndex(2);
	}*/
}

void UMainUI::OnClickedPlayerVSPlayer()
{
	//P VS P 변수 게임모드 전달

	if (Can_ChooseCharacter)
	{
		if (MainGameInstance)
		{
			//PvsP = 1
			MainGameInstance->GameModeSelectionIndex = 1;
		}
		//캐릭터 선택으로 이동
		WidgetSwitcher->SetActiveWidgetIndex(2);
	}
}

void UMainUI::OnClickedPlayerVSCPU()
{
	//P VS Ai라고 변수 게임모드 전달
	if (Can_ChooseCharacter)
	{
		if (MainGameInstance)
		{
			//PvsAi = 2
			MainGameInstance->GameModeSelectionIndex = 2;
		}
		//플레이사이드 선택으로 이동
		WidgetSwitcher->SetActiveWidgetIndex(1);
	}
}

void UMainUI::OnClickedCommu()
{
	ove_Empty->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI::OnClickedPalyData()
{
	ove_Empty->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI::OnClickedLeftSide()
{
	// 1P 위치에서 스폰, 1P
	//게임모드로 1p에 생성되고 2P는 NULL되게
	if (MainGameInstance)
	{
		MainGameInstance->IsPlayerOnLeftSide = true;
	}
	if (Can_ChooseCharacter)
	{
		//캐릭터 선택으로 이동
		WidgetSwitcher->SetActiveWidgetIndex(2);
		StartChoose();
	}
}

void UMainUI::OnClickedRightSide()
{
	//2P 위치에서 스폰, 2P
	//게임모드로 2p에 생성되고 1P는 NULL되게
	if (MainGameInstance)
	{
		MainGameInstance->IsPlayerOnLeftSide = false;
	}
	if (Can_ChooseCharacter)
	{
		//캐릭터 선택으로 이동
		WidgetSwitcher->SetActiveWidgetIndex(2);
		StartChoose();
	}
}

void UMainUI::StartChoose()
{
	//AI면
	if (MainGameInstance->GameModeSelectionIndex == 2)
	{
		//side left == ture 면 오른쪽은 카즈야 고정
		if (MainGameInstance->IsPlayerOnLeftSide)
		{
			bPlayer2Charac = true;
			FText KAZUYA = FText::FromString("KAZUYA");
			FText info1 = FText::FromString("가라테");
			FText info2 = FText::FromString("없음(일본 국적은 버림)");
			FText info3 = FText::FromString("181cm");
			FText info4 = FText::FromString("85kg");

			//만약 p1이라면
			//폴 정보 입력 
			Text_Player2Name->SetText(KAZUYA);
			Text_Player2Info01->SetText(info1);
			Text_Player2Info02->SetText(info2);
			Text_Player2Info03->SetText(info3);
			Text_Player2Info04->SetText(info4);
		}
		else
		{
			bPlayer1Charac = true;
			FText KAZUYA = FText::FromString("KAZUYA");
			FText info1 = FText::FromString("가라테");
			FText info2 = FText::FromString("없음(일본 국적은 버림)");
			FText info3 = FText::FromString("181cm");
			FText info4 = FText::FromString("85kg");

			//만약 p1이라면
			//폴 정보 입력 
			Text_Player1Name->SetText(KAZUYA);
			Text_Player1Info01->SetText(info1);
			Text_Player1Info02->SetText(info2);
			Text_Player1Info03->SetText(info3);
			Text_Player1Info04->SetText(info4);
		}
	}
}

void UMainUI::ChooseCharactter(int32 characnum)
{
	//어떤 캐릭 눌렀냐에 따라 게임모드로 메쉬 전달
	//PvsP
	//캐릭터 선택 ->
	if (bPlayer1Charac)
	{
		if (MainGameInstance)
		{
			MainGameInstance->Player1CharacterIndex = characnum;
		}
	}
	else if (bPlayer2Charac)
	{
		if (MainGameInstance)
		{
			MainGameInstance->Player2CharacterIndex = characnum;
		}
	}
	if (bPlayer1Charac && bPlayer2Charac)
	{
		//인게임 레벨로 이동
	}
}

void UMainUI::OnClickedPaul()
{
	//어느 버튼으로 움직여 눌렀는지에 따라 오른쪽, 왼쪽 정보창 띄우기
	//게임 모드가 PvsP인지 PvsAI인지 체크

	//PvsP 둘다 선택되어야 넘어감
	//PvsAi라면 AI는 카즈야 고정....

	//B면 1p쪽, P면 2P쪽 정보창 띄우기

	//player1 선택 -> 키 입력이 B(palyer1)였는지 , P(Player2)였는지 체크
	//if(B)
	bPlayer1Charac = true;
	ChooseCharactter(1);
	FText PAUL = FText::FromString("PAUL");
	FText info1 = FText::FromString("종합격투기");
	FText info2 = FText::FromString("미국");
	FText info3 = FText::FromString("187cm");
	FText info4 = FText::FromString("95kg");

	//만약 p1이라면
	//폴 정보 입력 
	Text_Player1Name->SetText(PAUL);
	Text_Player1Info01->SetText(info1);
	Text_Player1Info02->SetText(info2);
	Text_Player1Info03->SetText(info3);
	Text_Player1Info04->SetText(info4);

	//if(P)
	bPlayer2Charac = true;
	ChooseCharactter(1);
	//만약 p2이라면
	Text_Player2Name->SetText(PAUL);
	Text_Player2Info01->SetText(info1);
	Text_Player2Info02->SetText(info2);
	Text_Player2Info03->SetText(info3);
	Text_Player2Info04->SetText(info4);

	//if 두 캐릭터가 모두 선택 되었다면 ->레벨이동
}

void UMainUI::OnClickedRandom()
{
	GEngine->AddOnScreenDebugMessage(-6 , 5.f , FColor::Red , TEXT("OnClickedRandom!!!!!!!"));
	//if(B)
		bPlayer1Charac = true;
	   ChooseCharactter(1);
	//if(O)
	//bPlayer2Charac = true;
	   //ChooseCharactter(1);
	
	if (bPlayer1Charac && bPlayer2Charac)
	{
		//인게임 레벨로 이동
	}
	//폴밖에 없음
}

void UMainUI::ShowP1InputWindow()
{
	Player1Input->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI::ShowP2InputWindow()
{
	Player2Input->SetVisibility(ESlateVisibility::Visible);
}


void UMainUI::OnClickedEmptyBack()
{
	ove_Empty->SetVisibility(ESlateVisibility::Collapsed);
}

