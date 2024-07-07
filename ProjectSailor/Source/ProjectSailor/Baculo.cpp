// Property of DaPaRy Games


#include "Baculo.h"

// Sets default values
ABaculo::ABaculo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	baculo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	baculo->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABaculo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaculo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

