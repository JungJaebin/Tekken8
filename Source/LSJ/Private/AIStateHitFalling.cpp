// Fill out your copyright notice in the Description page of Project Settings.


#include "AIStateHitFalling.h"
#include "CPP_Tekken8CharacterParent.h"
#include "AICharacterAnimInstance.h"
#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AIStateBound.h"
#include "Components/BoxComponent.h"
void UAIStateHitFalling::SetAttackInfo ( FAttackInfoInteraction& pAttackInfo )
{
	attackInfoArray.Empty ( );
	attackInfoArray.Add ( pAttackInfo );
	currnetLocationZ = 0;
	maxLocationZ = owner->GetMesh()->GetSocketLocation(TEXT("root")).Z;
	minLocationZ = maxLocationZ;
}

void UAIStateHitFalling::Enter ( UAICharacterAnimInstance* pAnimInstance )
{
	Super::Enter ( pAnimInstance );
	//owner->collisionLower->SetCollisionEnabled ( ECollisionEnabled::NoCollision );


	animInstace->bKnockDown = false;
	owner->GetBlackboardComponent ( )->SetValueAsBool ( TEXT ( "IsKockDown" ) , false );
	owner->GetBlackboardComponent ( )->SetValueAsBool ( TEXT ( "IsHitFalling" ) , false );
	{
		FVector Direction = owner->GetActorLocation ( ) - owner->aOpponentPlayer->GetActorLocation ( )+ owner->aOpponentPlayer->GetActorForwardVector()*-10000.f;
		Direction.Z = 0.0f; // 수평 방향으로만 계산 (필요 시)

		// 벡터 정규화
		Direction.Normalize();

		// 반전된 벡터에 강도 적용 //attackInfoArray[0].KnockBackDirection.X
		FVector v = attackInfoArray[0].KnockBackDirection;
		v.X = 0;
		v.Y = 0;
		FVector LaunchVelocity = Direction * -1.f * 300.f + v;
		owner->LaunchCharacter ( LaunchVelocity , true , true );
		//owner->GetCharacterMovement ( )->AddImpulse ( attackInfoArray[0].KnockBackDirection * 100.0f , true );
	}
	//공격 받는 애니메이션 추가
	animInstace->StopAllMontages ( 0.1f );
	animInstace->PlayHitFallingTurnMontage ( attackInfoArray[0].RetrieveFrame + attackInfoArray[0].OppositeHitFrame , 30.0f);

		//owner->GetCharacterMovement ( )->AddImpulse ( attackInfoArray[0].KnockBackDirection * 100.0f , true );
		//owner->LaunchCharacter ( attackInfoArray[0].KnockBackDirection , true , true );
}

void UAIStateHitFalling::Execute ( const float& deltatime )
{
	currnetLocationZ = owner->GetMesh ( )->GetSocketLocation ( TEXT ( "root" ) ).Z;
	if( maxLocationZ < currnetLocationZ )
		maxLocationZ = currnetLocationZ;
	if ( false == owner->GetCharacterMovement ( )->IsFalling ( ) && maxLocationZ - minLocationZ > 10.f)
	{
		Exit();
	}
}

void UAIStateHitFalling::Exit ( )
{
	if ( maxLocationZ - minLocationZ > 10.f )
	{
		owner->GetBlackboardComponent ( )->SetValueAsBool ( TEXT ( "IsBound" ) , true );
		owner->GetAIStateBound ( )->SetAttackInfo ( attackInfoArray[0] );
	}
	else
	{
		animInstace->bKnockDown = true;
		owner->GetBlackboardComponent ( )->SetValueAsBool ( TEXT ( "IsKnockDown" ) , true );
	}
	Super::Exit ( );
}
