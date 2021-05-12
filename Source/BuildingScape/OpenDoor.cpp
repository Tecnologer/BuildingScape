// copyright tecnologer


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT
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

	CloseInterpSpeed = OpenDoorAngle / DoorCloseSpeed;
	OpenInterpSpeed = OpenDoorAngle / DoorOpenSpeed;
	
	FindPressurePlate();
	FindAudioComponent();
}

void UOpenDoor::FindAudioComponent(){
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No audio component found on %s!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("No pressure plate found on %s!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TotalMassOfActors() > MassToOpenDoor) {
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if((GetWorld()->GetTimeSeconds() - DoorLastOpened) >= DoorCloseDelay) {
		
		CloseDoor(DeltaTime);
		//CanPlay = true;
	}	
}

void UOpenDoor::OpenDoor(const float DeltaTime) {
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float Interpolation = FMath::FInterpConstantTo(CurrentRotation.Yaw, OpenDoorAngle, DeltaTime, OpenInterpSpeed);
	CurrentRotation.Yaw = Interpolation;
	GetOwner()->SetActorRotation(CurrentRotation);

	CloseDoorSound = false;
	if(!OpenDoorSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("play sound door open"));
		if (AudioComponent)
			AudioComponent->Play();

		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(const float DeltaTime) {
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	float Interpolation = FMath::FInterpConstantTo(CurrentRotation.Yaw, InitialDoorAngle, DeltaTime, CloseInterpSpeed);
	CurrentRotation.Yaw = Interpolation;
	GetOwner()->SetActorRotation(CurrentRotation);

	OpenDoorSound = false;
	if(!CloseDoorSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("play sound door close"));
		if (AudioComponent)
			AudioComponent->Play();

		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const{
	float TotalMass = 0.f;
	if(!PressurePlate)
	{
		// UE_LOG(LogTemp, Warning, TEXT("No presure plate!"));
		return TotalMass;
	}

	//Find all overlaping actors
	TArray<AActor *> OverlapingActors;
	PressurePlate->GetOverlappingActors(OUT OverlapingActors);
	
	//Add up their masses
	for (AActor* Actor : OverlapingActors){
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		// UE_LOG(LogTemp, Warning, TEXT("%s is on the pressureplate!"), *Actor->GetName());
	}

	// UE_LOG(LogTemp, Warning, TEXT("Total Mass: %f"), TotalMass);
	return TotalMass;
}