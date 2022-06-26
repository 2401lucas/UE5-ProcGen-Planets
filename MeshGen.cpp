// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshGen.h"


// Sets default values
AMeshGen::AMeshGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	_smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"), false);
	SetRootComponent(_smComp);
}

// Called when the game starts or when spawned
void AMeshGen::BeginPlay()
{
	Super::BeginPlay();
	
	// Build a simple sphere
	FMeshDescription meshDesc;
	FStaticMeshAttributes Attributes(meshDesc);
	Attributes.Register();

	FMeshDescriptionBuilder* meshDescBuilder = new FMeshDescriptionBuilder();
	meshDescBuilder->SetMeshDescription( &meshDesc );
	meshDescBuilder->EnablePolyGroups();
	meshDescBuilder->SetNumUVLayers(1);

	
	// create 12 vertices of a icosahedron
	TArray<FVertexID> vertexIDs; vertexIDs.SetNum(12);
	TArray<FVector> rectPosArray;
	
	//Rect 1
	rectPosArray.Add(FVector(-1,  UE_GOLDEN_RATIO,  0));
	rectPosArray.Add(FVector( 1,  UE_GOLDEN_RATIO,  0));
	rectPosArray.Add(FVector(-1, -UE_GOLDEN_RATIO,  0));
	rectPosArray.Add(FVector( 1, -UE_GOLDEN_RATIO,  0));
	//Rect 2
	rectPosArray.Add(FVector( 0, -1,  UE_GOLDEN_RATIO));
	rectPosArray.Add(FVector( 0,  1,  UE_GOLDEN_RATIO));
	rectPosArray.Add(FVector( 0, -1, -UE_GOLDEN_RATIO));
	rectPosArray.Add(FVector( 0,  1, -UE_GOLDEN_RATIO));
	//Rect 3
	rectPosArray.Add(FVector( UE_GOLDEN_RATIO,  0, -1));
	rectPosArray.Add(FVector( UE_GOLDEN_RATIO,  0,  1));
	rectPosArray.Add(FVector(-UE_GOLDEN_RATIO,  0, -1));
	rectPosArray.Add(FVector(-UE_GOLDEN_RATIO,  0,  1));

	for(int i = 0; i < rectPosArray.Num(); i++)
	{
		rectPosArray[i].Normalize();
		vertexIDs[i] = meshDescBuilder->AppendVertex(rectPosArray[i]);
	}
	
	TArray<FVertexInstanceID>* vertexInsts = new TArray<FVertexInstanceID>();
	
	// 5 faces around point 0
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[0], vertexIDs[11], vertexIDs[5], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[0], vertexIDs[5], vertexIDs[1], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[0], vertexIDs[1], vertexIDs[7], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[0], vertexIDs[7], vertexIDs[10], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[0], vertexIDs[10], vertexIDs[11], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));

	// 5 adjacent faces
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[1], vertexIDs[5], vertexIDs[9], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[5], vertexIDs[11], vertexIDs[4], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[11], vertexIDs[10], vertexIDs[2], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[10], vertexIDs[7], vertexIDs[6], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[7], vertexIDs[1], vertexIDs[8], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	
	// 5 faces around point 3
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[3], vertexIDs[9], vertexIDs[4], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[3], vertexIDs[4], vertexIDs[2], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[3], vertexIDs[2], vertexIDs[6], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[3], vertexIDs[6], vertexIDs[8], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[3], vertexIDs[8], vertexIDs[9], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	
	// 5 adjacent faces
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[4], vertexIDs[9], vertexIDs[5], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[2], vertexIDs[4], vertexIDs[11], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[6], vertexIDs[2], vertexIDs[10], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[8], vertexIDs[6], vertexIDs[7], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	CreateFaceRec(meshDescBuilder, vertexInsts, vertexIDs[9], vertexIDs[8], vertexIDs[1], FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	
	// Allocate a polygon group
	FPolygonGroupID polygonGroup = meshDescBuilder->AppendPolygonGroup();
	
	// Add triangles to mesh description
	for(int i = 0; i < vertexInsts->Num(); i+=3)
	{
		meshDescBuilder->AppendTriangle((*vertexInsts)[i + 2], (*vertexInsts)[i + 1], (*vertexInsts)[i], polygonGroup);
	}

	// At least one material must be added
	UStaticMesh* staticMesh = NewObject<UStaticMesh>(this);
	staticMesh->GetStaticMaterials().Add(FStaticMaterial());

	UStaticMesh::FBuildMeshDescriptionsParams mdParams;
	mdParams.bBuildSimpleCollision = true;
	mdParams.bFastBuild = true;
	
	// Build static mesh
	TArray<const FMeshDescription*> meshDescPtrs;
	meshDescPtrs.Emplace(&meshDesc);
	staticMesh->BuildFromMeshDescriptions(meshDescPtrs, mdParams);
	
	// Assign new static mesh to the static mesh component
	_smComp->SetStaticMesh(staticMesh);
	_smComp->SetWorldScale3D(FVector(10, 10, 10));
}

void AMeshGen::CreateFace(FMeshDescriptionBuilder*& meshDescBuilder, TArray<FVertexInstanceID>*& vertexInsts, FVertexID pointA, FVertexID pointB, FVertexID pointC, FVector2d uv, FVector4f colour)
{
	const FVector normal = CalculateNormal(meshDescBuilder, pointA, pointB, pointC);
	
	FVertexInstanceID instanceA = meshDescBuilder->AppendInstance(pointA);
	meshDescBuilder->SetInstanceNormal(instanceA, normal);
	//meshDescBuilder->SetInstanceUV(instanceA, FVector2D(0, 1), 0);
	meshDescBuilder->SetInstanceColor(instanceA, colour);
	vertexInsts->Add(instanceA);
	
	FVertexInstanceID instanceB = meshDescBuilder->AppendInstance(pointB);
	meshDescBuilder->SetInstanceNormal(instanceB, normal);
	//meshDescBuilder->SetInstanceUV(instanceB, FVector2D(0, 1), 0);
	meshDescBuilder->SetInstanceColor(instanceB, colour);
	vertexInsts->Add(instanceB);
	
	FVertexInstanceID instanceC = meshDescBuilder->AppendInstance(pointC);
	meshDescBuilder->SetInstanceNormal(instanceC, normal);
	//meshDescBuilder->SetInstanceUV(instanceC, FVector2D(0, 1), 0);
	meshDescBuilder->SetInstanceColor(instanceC, colour);
	vertexInsts->Add(instanceC);
}

void AMeshGen::CreateFaceRec(FMeshDescriptionBuilder*& meshDescBuilder, TArray<FVertexInstanceID>*& vertexInsts, FVertexID pointA, FVertexID pointB, FVertexID pointC, FVector2d uv, FVector4f colour)
{
	TArray<FVertexID> faces;
	faces.Add(pointA);
	faces.Add(pointB);
	faces.Add(pointC);

	UE_LOG(LogTemp, Warning, TEXT("ID A: %a ID B: %b ID C: %c"), pointA, pointB, pointC);
	
	//Smooths Faces
	for (int i = 0; i < 3; i++)
	{
		TArray<FVertexID> newFaces;
		
		for(int f = 0; f < faces.Num(); f+=3)
		{
			FVertexID a = GetMiddlePoint(meshDescBuilder, faces[f], faces[f+1]);
			FVertexID b = GetMiddlePoint(meshDescBuilder, faces[f+1], faces[f+2]);
			FVertexID c = GetMiddlePoint(meshDescBuilder, faces[f+2], faces[f]);

			newFaces.Add(faces[f]);
			newFaces.Add(a);
			newFaces.Add(c);
			
			newFaces.Add(faces[f+1]);
			newFaces.Add(b);
			newFaces.Add(a);
			
			newFaces.Add(faces[f+2]);
			newFaces.Add(c);
			newFaces.Add(b);

			newFaces.Add(a);
			newFaces.Add(b);
			newFaces.Add(c);
		}
		faces = newFaces;
	}
	
	for(int f = 0; f < faces.Num(); f+=3)
	{
		// replace triangle by 4 triangles
		CreateFace(meshDescBuilder, vertexInsts, faces[f], faces[f+1], faces[f+2],FVector2D(0, 1),FVector4f(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// return index of point in the middle of p1 and p2
FVertexID AMeshGen::GetMiddlePoint(FMeshDescriptionBuilder*& meshDescBuilder, FVertexID p1, FVertexID p2)
{
	// first check if we have it already
	//bool firstIsSmaller = p1 < p2;
	// FVertexID smallerIndex = firstIsSmaller ? p1 : p2;
	// FVertexID greaterIndex = !firstIsSmaller ?  p1 : p2;
	// int key = (smallerIndex << 32) + greaterIndex;
	//
	// int ret;
	// if (this.middlePointIndexCache.TryGetValue(key, out ret))
	// {
	// 	return ret;
	// }

	// not in cache, calculate it
	FVector point1 = meshDescBuilder->GetPosition(p1);
	FVector point2 = meshDescBuilder->GetPosition(p2);
	FVector middle = FVector(
		(point1.X + point2.X) / 2.0, 
		(point1.Y + point2.Y) / 2.0, 
		(point1.Z + point2.Z) / 2.0);

	
	// add vertex makes sure point is on unit sphere
	middle.Normalize();
	
	FVertexID middleId = meshDescBuilder->AppendVertex(middle);
	// store it, return index
	// this.middlePointIndexCache.Add(key, i);
	return middleId;
}

FVector AMeshGen::CalculateNormal(FMeshDescriptionBuilder*& meshDescBuilder,FVertexID pointA, FVertexID pointB, FVertexID pointC)
{
	const FVector positionA = meshDescBuilder->GetPosition(pointA);
	const FVector positionB = meshDescBuilder->GetPosition(pointB);
	const FVector positionC = meshDescBuilder->GetPosition(pointC);
	
	const FVector sideAB = positionB - positionA;
	const FVector sideAC = positionC - positionA;
	
	FVector crossProd = FVector::CrossProduct(sideAB, sideAC);
	crossProd.Normalize(KINDA_SMALL_NUMBER);
	return crossProd;
}


// Called every frame
void AMeshGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}