// copyright tecnologer


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();	
	
	auto Alpha = 0.05f;
	UE_LOG(LogTemp, Warning, TEXT("Current Yaw: %f"), CurrentRotation.Yaw);
	//float Interpolation = FMath::Lerp(CurrentRotation.Yaw, TargetYaw, Alpha);
	float Interpolation = FMath::FInterpConstantTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, 45);

	UE_LOG(LogTemp, Warning, TEXT("Interpolation: %d"), Interpolation);
	//CurrentRotation = GetOwner()->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
	CurrentRotation.Yaw = Interpolation;
	// ...
	
	GetOwner()->SetActorRotation(CurrentRotation);
}

