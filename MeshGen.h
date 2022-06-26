// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeshGen.generated.h"
UCLASS()
class PROCEDURALPLANET_API AMeshGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshGen();
	int numHorizontalSegments = 100;
	int numVerticalSegments = 100;
private:
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
};