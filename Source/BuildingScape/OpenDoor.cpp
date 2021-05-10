// copyright tecnologer


#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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

	if (!ActorThatOpen) {
		ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	}

	CloseInterpSpeed = OpenDoorAngle / DoorCloseSpeed;
	OpenInterpSpeed = OpenDoorAngle / DoorOpenSpeed;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen)) {
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if((GetWorld()->GetTimeSeconds() - DoorLastOpened) >= DoorCloseDelay) {
		
		CloseDoor(DeltaTime);
	}	
}

void UOpenDoor::OpenDoor(const float DeltaTime) const {
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float Interpolation = FMath::FInterpConstantTo(CurrentRotation.Yaw, OpenDoorAngle, DeltaTime, OpenInterpSpeed);
	CurrentRotation.Yaw = Interpolation;
	GetOwner()->SetActorRotation(CurrentRotation);
}

void UOpenDoor::CloseDoor(const float DeltaTime) const {
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float Interpolation = FMath::FInterpConstantTo(CurrentRotation.Yaw, InitialDoorAngle, DeltaTime, CloseInterpSpeed);
	CurrentRotation.Yaw = Interpolation;
	GetOwner()->SetActorRotation(CurrentRotation);
}

