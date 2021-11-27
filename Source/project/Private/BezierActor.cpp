// Fill out your copyright notice in the Description page of Project Settings.


#include "BezierActor.h"

// Sets default values
ABezierActor::ABezierActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABezierActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABezierActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> ABezierActor::BezierCurve(TArray<FVector> src)
{
	// Ignore the dot version
	if (src.Num() < 1)
	{
		return src;
	}

	// t-step
	const float step = 0.01;
	// return value
	TArray<FVector> res;

	// linear version
	if (src.Num() == 1)
	{
		for (float t = 0; t < 1; t += step)
		{
			res.Add(src[0]);
		}
		return res;
	}

	// quadratic version
	TArray<FVector> src1;
	TArray<FVector> src2;
	
	for (int32 i = 0; i < src.Num() - 1; i++)
	{
		src1.Add(src[i]);
		UE_LOG(LogTemp, Warning, TEXT("==%s\t"), *src1[i].ToString());
	}
	for (int32 j = 0; j < src.Num(); j++)
	{
		src2.Add(src[j]);
		UE_LOG(LogTemp, Warning, TEXT("==%s\t"), *src2[j].ToString());
	}
	src2.RemoveAt(0);

	// recursive
	TArray<FVector> pln1 = BezierCurve(src1);
	TArray<FVector> pln2 = BezierCurve(src2);

	for (float t = 0; t < 1; t += step)
	{
		FVector tmp;
		tmp = ((1.0 - t) * pln1[FMath::RoundToInt(1.0 / step * t)])
			+ (t * pln2[FMath::RoundToInt(1.0 / step * t)]);
		res.Add(tmp);
	}

	return res;
}

