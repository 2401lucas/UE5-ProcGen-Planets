// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeshGen.generated.h"

USTRUCT(BlueprintType)
struct FNoiseSettings
{
	GENERATED_BODY()
	
	FNoiseSettings(){}
	
	UPROPERTY(EditAnywhere)
	float amplitude = 1;
	UPROPERTY(EditAnywhere)
	float noiseScale = 1;
	UPROPERTY(EditAnywhere)
	float power = 1;
	UPROPERTY(EditAnywhere)
	int frequency = 1;
	UPROPERTY(EditAnywhere)
	float lacunarity = 2;
	UPROPERTY(EditAnywhere)
	float persistence = 0.5;
	UPROPERTY(EditAnywhere)
	float elevation = 0;
	UPROPERTY(EditAnywhere)
	float density = 0;
	UPROPERTY(EditAnywhere)
	FVector offset = FVector(0,0,0);
};

UCLASS()
class PROCEDURALPLANET_API AMeshGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshGen();
	UPROPERTY(EditAnywhere)
	int recursionLevel = 4;
	UPROPERTY(EditAnywhere)
	int radius = 100;
	UPROPERTY(EditAnywhere)
	float rotationSpeed = 36;
	UPROPERTY(EditAnywhere)
	FNoiseSettings shapeNoise;
	UPROPERTY(EditAnywhere)
	FNoiseSettings surfaceNoise;
	UPROPERTY(EditAnywhere)
	FNoiseSettings craterNoise;
	UPROPERTY(EditAnywhere)
	FNoiseSettings ridgeNoise;
	UPROPERTY(EditAnywhere)
	bool hasOceans;
	UPROPERTY(EditAnywhere)
	float oceanFloorHeight;
	
private:
	TMap<FVector, FVertexID> vertexCache;
	UStaticMeshComponent *_smComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector CalculateNormal(FMeshDescriptionBuilder*& meshDescBuilder, FVertexID pointA,FVertexID pointB,FVertexID pointC);
	void CreateFace(FMeshDescriptionBuilder*& meshDescBuilder, TArray<FVertexInstanceID>*& vertexInsts, FVertexID pointA,FVertexID pointB,FVertexID pointC, FVector2d uv, FVector4f colour);
	void CreateFaceRec(FMeshDescriptionBuilder*& meshDescBuilder, TArray<FVertexInstanceID>*& vertexInsts, FVertexID pointA, FVertexID pointB, FVertexID pointC, FVector2d uv, FVector4f colour);
	FVertexID GetMiddlePoint(FMeshDescriptionBuilder*& meshDescBuilder, FVertexID p1, FVertexID p2);
	float GetNoise(FVector pos);
};

