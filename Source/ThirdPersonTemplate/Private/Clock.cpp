// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"

#define ONE_YEAR 31104000 // 360일 기준 1년 초
#define ONE_MONTH 2592000 // 30일 기준 1달 초
#define ONE_DAY 86400 // 1일 기준 24시간 초
#define ONE_HOUR 3600 // 1시간 24시간 초
#define ONE_MINUTE 60

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTime(DeltaTime);
	RotateDirectionalLightWithTime(Sun);

	//GetTimeByTotalSec(TotalSeconds);
}

void AClock::UpdateTime(float DeltaSec)
{
	TotalSeconds += DeltaSec * TimeScale; // DeltaSeconds를 더하여 시간 업데이트

	CurrentDay = TotalSeconds / 86400; // 1일은 86400초
	int32 RemainingSecondsAfterDays = (int)TotalSeconds % 86400; // 일을 제외한 나머지 초를 계산
	CurrentHour = RemainingSecondsAfterDays / 3600; // 시간을 초에서 시간으로 변환
	int32 RemainingSecondsAfterHours = RemainingSecondsAfterDays % 3600; // 시간을 제외한 나머지 초
	CurrentMinute = RemainingSecondsAfterHours / 60; // 분을 초에서 분으로 변환
	CurrentSecond = RemainingSecondsAfterHours % 60; // 분을 제외한 나머지 초를 초로 사용
}

// Directional Light을 조작하기 위한 함수
void AClock::RotateDirectionalLightWithTime(AActor* OwningActor) {
	if (OwningActor) {
		ADirectionalLight* _DirectionalLight = Cast<ADirectionalLight>(OwningActor);
		UDirectionalLightComponent* _DirectionalLightComp = _DirectionalLight->GetComponent();


		if (_DirectionalLight) {

			//float _AnglePerHour = 360.0f / 24.0f; // 24시간을 360도로 나눔 // = 15
			//float _HourAngle = FMath::Fmod(CurrentHour * _AnglePerHour, 360.0f); // 시간에 따른 각도 계산
			float _HourAngle = FMath::Fmod(CurrentHour * 15, 360.0f); // 시간에 따른 각도 계산
			//float _MinuteAngle = (CurrentMinute / 60.0f) * _AnglePerHour; // 분에 따른 각도 계산
			float _MinuteAngle = (CurrentMinute / 60.0f) * 15; // 분에 따른 각도 계산
			//float _SecondAngle = (CurrentSecond / 60.0f) * (_AnglePerHour / 60.0f); // 초에 따른 각도 계산
			float _SecondAngle = (CurrentSecond / 60.0f) * (15 / 60.0f); // 초에 따른 각도 계산
			float _CurrentAngle = _HourAngle + _MinuteAngle + _SecondAngle; // 시간, 분, 초에 따른 총 각도 계산

			FRotator _NewRotation = FRotator(_CurrentAngle,0.0f , 0.0f);
			_DirectionalLight->SetActorRotation(_NewRotation); // Directional Light의 회전 설정



			// 시간에 따라 보간되는 색상을 설정하고 싶은 경우
			FLinearColor InterpolatedColor;

			if (CurrentHour > 0 && CurrentHour <= 3)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color24, Color3, CurrentHour / 3.0f);
			}
			else if (CurrentHour > 3 && CurrentHour <= 6)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color3, Color6, (CurrentHour-3) / 3.0f);
			}
			else if (CurrentHour > 6 && CurrentHour <= 9)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color6, Color9, (CurrentHour - 6) / 3.0f);
			}
			else if (CurrentHour > 9 && CurrentHour <= 12)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color9, Color12, (CurrentHour - 9) / 3.0f);
			}
			else if (CurrentHour > 12 && CurrentHour <= 15)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color12, Color15, (CurrentHour - 12) / 3.0f);
			}
			else if (CurrentHour > 15 && CurrentHour <= 18)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color15, Color18, (CurrentHour - 15) / 3.0f);
			}
			else if (CurrentHour > 18 && CurrentHour <= 21)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color18, Color21, (CurrentHour - 18) / 3.0f);
			}
			else if (CurrentHour > 21 && CurrentHour <= 24)
			{
				InterpolatedColor = FLinearColor::LerpUsingHSV(Color21, Color24, (CurrentHour - 21) / 3.0f);
			}
			else
			{
				InterpolatedColor = FLinearColor::White;
			}
			
			// Directional Light의 색상 설정
			_DirectionalLightComp->SetLightColor(InterpolatedColor);
				
		}
	}
}

FString AClock::GetTimeByTotalSec(float totlaSec)
{
	//year = totlaSec / ONE_YEAR; // 입력값을 1년으로 나눔
	//month = totlaSec / ONE_MONTH % 12; // ‥ 1달로 나눈 후 12로 나눈 나머지값
	CurrentDay = (int)totlaSec / ONE_DAY % 30; // ‥ 1일으로 나눈 후 30으로 나눈 나머지값
	CurrentHour = (int)totlaSec / ONE_HOUR % 24; // ‥ 1시간으로 나눈 후 24로 나눈 나머지값
	CurrentMinute = (int)totlaSec / ONE_MINUTE % 60; // ‥ 1분으로 나눈 후 60으로 나눈 나머지값
	CurrentSecond = (int)totlaSec % 60; // ‥ 60초로 나눈 나머지값

	FString Now ;
	Now = "D:" + FString::SanitizeFloat(CurrentDay)
	+ "-H:"+ FString::SanitizeFloat(CurrentHour)
	+ "-M:"+ FString::SanitizeFloat(CurrentMinute)
	+ "-S:"+ FString::SanitizeFloat(CurrentSecond);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, (TEXT("%s"), Now));
	return Now;
}

