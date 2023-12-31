// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "SAC1PlayerState.h"
#include "../Camera/HitCameraShake.h"

 
// Sets default values
APlayerCharacter::APlayerCharacter() 
{ 
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mTrail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	//SetRelativeLocation과 SetRelativeRotation은 더블타입. 뒤에 .f안붙인다.

	mSpringArm->TargetArmLength = 500.f;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>	TrailAsset(TEXT("/Script/Niagara.NiagaraSystem'/Game/Niagara/NS_Trail.NS_Trail'"));

	if (TrailAsset.Succeeded())
		mTrail->SetAsset(TrailAsset.Object);

	mTrail->SetupAttachment(GetMesh());

	//부모 컴포넌트로 Mesh를 지정한다.
	mSpringArm->SetupAttachment(GetMesh());

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm);

	mCameraRotationEnable = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// 오버랩 이벤트 생성을 켜준다.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// 시뮬레이션 히트 이벤트 생성을 켜준다.
	//물리적인 시뮬레이션이 일어날 때만 효과가 있다.
	//일반 이동이나 일반적인 충돌에서는 의미가 없다.
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	// OnComponentHit : Multicast + Dynamic 조합의 Delegate이다.
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,
		&APlayerCharacter::BodyHit);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,
		&APlayerCharacter::OverlapBegin);

	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this,
		&APlayerCharacter::OverlapEnd);

	GetCapsuleComponent()->CanCharacterStepUpOn =
		ECanBeCharacterBase::ECB_No;
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mTeam = ETeam::Team1; //여긴 1번 팀 지정. AIpawn은 2번팀으로 지정할꺼임.

	GetMesh()->bRenderCustomDepth = true;

	//0~255사이의 원하는 값을 넣어준다.
	GetMesh()->SetCustomDepthStencilValue(0);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	mTrail->SetRelativeLocation(FVector(0.0, 0.0,
		GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	// SkeletalMesh는 GetAnimInstance 함수를 지원해주고 있다.
	// 이 함수는 SkeletalMesh에 지정된 AnimInstance 클래스를 이용해서 생성
	// 한 객체를 가지고 있다.
	// GetAnimInstance함수는 바로 이 객체를 꺼내오는 함수이다.
	mPlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//1번 인자 : 축매핑 이름
	//2번 인자 : 함수를 호출할 객체
	//3번 인자 : 함수의 주소
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, 
		&APlayerCharacter::MoveFront);

	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this,
		&APlayerCharacter::MoveSide);

	PlayerInputComponent->BindAxis(TEXT("RotationCharacter"), this,
		&APlayerCharacter::RotationCharacterYaw);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this,
		&APlayerCharacter::UpDownPitch);


	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this,
		&APlayerCharacter::CameraZoom);



	PlayerInputComponent->BindAction(TEXT("RotationCamera"),
		EInputEvent::IE_Pressed,this,
		&APlayerCharacter::RotationCamera);

	PlayerInputComponent->BindAction(TEXT("RotationCamera"),
		EInputEvent::IE_Released, this,
		&APlayerCharacter::RotationCameraReleased); 

	PlayerInputComponent->BindAction(TEXT("Attack"),
		EInputEvent::IE_Pressed, this,
		&APlayerCharacter::Attack); 

	PlayerInputComponent->BindAction(TEXT("Jumpkey"),
		EInputEvent::IE_Pressed, this,
		&APlayerCharacter::Jumpkey);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, 
	AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	LOG(TEXT("CamerashakeTest"));

	/*UGameplayStatics::PlayWorldCameraShake(GetController(),
		UHitCameraShake::StaticClass(), FVector::ZeroVector,
		100.f, 1000.f);*/

		// 아래 두 함수는 PlayerController가 가지고 있는 CameraManager를 이용해서
		// 접근해야 한다. static 멤버함수가 아니기 때문이다.
	APlayerController* PlayerCtrl = Cast<APlayerController>(GetController());

	PlayerCtrl->PlayerCameraManager->StartCameraShake(UHitCameraShake::StaticClass());
	//APlayerCameraManager::StartCameraShake(UHitCameraShake::StaticClass());
	//APlayerCameraManager::StopCameraShake();

	return Dmg;
}

void APlayerCharacter::MoveFront(float Scale)
{
	AddMovementInput(GetActorForwardVector(), Scale);

	// Scale이 0이 아닌 경우는 이동키를 눌렀다는 것이므로 애니메이션을
	// Default로 변경한다.
	/*if (Scale != 0.f)
		mPlayerAnim->ChangeAnim(EPlayerAnimType::Default);*/
}

void APlayerCharacter::MoveSide(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);

	/*if (Scale != 0.f)
		mPlayerAnim->ChangeAnim(EPlayerAnimType::Default);*/
}


void APlayerCharacter::RotationCharacterYaw(float Scale)
{
	if (mCameraRotationEnable)
	{
		float Rot = 180.f * GetWorld()->GetDeltaSeconds() * Scale;

		mSpringArm->AddRelativeRotation(FRotator(0.0, (double)Rot, 0.0));
	
	}

	else
	{
		AddControllerYawInput(Scale);
	}
}

void APlayerCharacter::UpDownPitch (float Scale)
{
	if (mCameraRotationEnable)
	{
		float Rot = 180.f * GetWorld()->GetDeltaSeconds() * Scale;

		mSpringArm->AddRelativeRotation(FRotator((double)Rot,0.0, 0.0));

	}

	
}

void APlayerCharacter::CameraZoom(float Scale)
{
	float Length = Scale * 50.f;

	mSpringArm->TargetArmLength -= Length;


}

void APlayerCharacter::RotationCamera()
{
	mCameraRotationEnable = true;

	LOG(TEXT("Test : %d"), (int32)mCameraRotationEnable);
}

void APlayerCharacter::RotationCameraReleased()
{
	mCameraRotationEnable = false;
}

void APlayerCharacter::Jumpkey()
{
	if (CanJump()&&mPlayerAnim->CanJump()) //점프 가능 상태인지 체크한다.
	{
		Jump();
		mPlayerAnim->Jump();
		//mPlayerAnim->ChangeAnim(EPlayerAnimType::Jump);
	}
}

void APlayerCharacter::Attack()
{
	mPlayerAnim->AttackT();
}

void APlayerCharacter::BodyHit(UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
		FString::Printf(TEXT("Dest : %s"),*OtherActor->GetName()));

	ASAC1PlayerState* State = Cast<ASAC1PlayerState>(GetPlayerState());

	if (IsValid(State))
	{
		State->AddHP(-5);
	}



}

void APlayerCharacter::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString::Printf(TEXT("BeginOverlap Dest : %s"), *OtherActor->GetName()));
}

void APlayerCharacter::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString::Printf(TEXT("EndOverlap Dest : %s"), *OtherActor->GetName()));
}

void APlayerCharacter::Attack1()
{
}

void APlayerCharacter::Attack2()
{
}

/// 
void APlayerCharacter::Attack3()
{
}

/*

void APlayerCharacter::FootInteraction(bool Left)
{
	FVector	FootLoc;

	if (Left)
		FootLoc = GetMesh()->GetSocketLocation(TEXT("Foot_L"));

	else
		FootLoc = GetMesh()->GetSocketLocation(TEXT("Foot_R"));

	FVector	LineEnd = FootLoc + FVector::DownVector * 50.f;

	FHitResult	result;

	FCollisionQueryParams	param(NAME_None, false, this);
	param.bReturnPhysicalMaterial = true;

	bool Collision = GetWorld()->LineTraceSingleByChannel(result,
		FootLoc, LineEnd, ECollisionChannel::ECC_Visibility, param);

	if (Collision)
	{
		USAC1PhysicalMaterial* Phys = Cast<USAC1PhysicalMaterial>(result.PhysMaterial);

		if (IsValid(Phys))
		{
			LOG(TEXT("Physical : %s"), *Phys->GetName());

			if (IsValid(Phys->GetParticle()))
			{
				FActorSpawnParameters	ActorParam;
				ActorParam.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ADefaultEffect* Effect = GetWorld()->SpawnActor<ADefaultEffect>(
					FootLoc,
					FRotator::ZeroRotator, ActorParam);

				Effect->SetParticleAsset(Phys->GetParticle());
			}

			if (IsValid(Phys->GetSound()))
			{
				UGameplayStatics::PlaySoundAtLocation(this, Phys->GetSound(),
					FootLoc, 10.f);
			}
		}
	}
}


*/
 