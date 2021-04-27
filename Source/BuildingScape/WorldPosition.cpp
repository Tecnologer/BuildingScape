// copyright tecnologer

#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	// ...
	FString ActorName = GetOwner()->GetName();
	FVector ActorPosition = GetOwner()->GetActorLocation();
	FString ActorPositionStr = ActorPosition.ToString();
	FString ActorTransform = GetOwner()->GetActorTransform().ToString();
	//UE_LOG(LogTemp, Display, TEXT("Actor: %s is on X: %f, Y: %f, Z: %f"), *ActorName, ActorPosition.X, ActorPosition.Y, ActorPosition.Z);
	UE_LOG(LogTemp, Display, TEXT("Actor: %s is on %s"), *ActorName, *ActorTransform);
}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
