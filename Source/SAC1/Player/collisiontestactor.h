// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "collisiontestactor.generated.h"

UCLASS()
class SAC1_API Acollisiontestactor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Acollisiontestactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
TObjectPtr<UCapsuleComponent> mCapsule02; 

UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
TObjectPtr<UStaticMeshComponent> mStaticMesh02;

private:
UFUNCTION() 
void BodyHit02(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
