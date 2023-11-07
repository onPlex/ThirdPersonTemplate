// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "TPSPlayer.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class THIRDPERSONTEMPLATE_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Fire")
	class UStaticMeshComponent* weaponMeshComp;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveIA;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireIA;

public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);

public:
	//UPROPERTY(EditAnywhere, Category = "Move")
	//float moveSpeed;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class APBullet> magazine;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* attackAnimMontage;

private:
    FVector moveDirection;

	void Locomotion();

};
