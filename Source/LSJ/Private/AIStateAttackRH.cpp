﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStateAttackRH.h"
#include "AICharacterAnimInstance.h"
#include "CPP_CharacterPaul.h"
#include "AICharacter.h"
#include "Components/SphereComponent.h"
void UAIStateAttackRH::Enter ( UAICharacterAnimInstance* pAnimInstance )
{
	Super::Enter(pAnimInstance);
	startLocation = owner->GetMesh ( )->GetBoneLocation ( (TEXT ( "head" )) );
	//공격거리 head 기준 175.0f RH Middle
	//공격거리 head 기준 81.0f LH Top
	//공격거리 head 기준 157 LF Lower

	animInstace->PlayeAttackRHMontage ();

	owner->GetCurrentMontage ( )->GetSectionStartAndEndTime ( 0 , startFrame , endFrame );
	TArray<const FAnimNotifyEvent*> notifyEvents;
	//몽타지 노티파이의 끝나는 시간
	owner->GetCurrentMontage ( )->GetAnimNotifies ( startFrame , endFrame , false , notifyEvents );
	for ( const FAnimNotifyEvent* NotifyEvent : notifyEvents )
	{
		endFrame = NotifyEvent->GetTriggerTime ( );
	}
	totalTime = 0;
	btest = false;

}

void UAIStateAttackRH::Execute ( const float& deltatime )
{
	ToLookTargetRotate ( deltatime );
	totalTime += deltatime;
	if ( totalTime >= endFrame && !btest)
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 1.f , FColor::Red , FString::Printf ( TEXT ( "range : %f " ) , FVector::Dist ( owner->collisionRH->GetComponentLocation ( ) , startLocation ) ) );
		btest = true;
	}
}

void UAIStateAttackRH::Exit ( )
{
	Super::Exit ( );
}
