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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Fire")
	class UStaticMeshComponent* weaponMeshComp;

	UPROPERTY(EditAnywhere, Category = "FX")
	class UNiagaraComponent* niagaraFX;

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
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractionIA;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractionIA_N;

public:
	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);
	void InputFire(const FInputActionValue& Value);
	void InteractionPositive(const FInputActionValue& Value);

public:
	//UPROPERTY(EditAnywhere, Category = "Move")
	//float moveSpeed;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class APBullet> magazine;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* attackAnimMontage;
private:
	void Locomotion();

	FVector moveDirection;
	bool fireReady;
	float fireTimerTime;

public:
	UPROPERTY(EditAnywhere, Category = "Fire")
	float fireCoolTime;
protected:
    void FireCoolTimer(float Duration, float deltaTime);

public:
	void SpawnBullet();
	void ShowFX();

public: 

	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = "Status")
	float maxHp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float currentHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float maxMp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	float currentMP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float interactionDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int64 money = 9999;

	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int64 inputVal);

	
	
};
