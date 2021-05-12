// copyright tecnologer


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//check for physics handle component
	FindPhysicsHandle();
	
	//check for input handle component
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle component found on %s!"), *GetOwner()->GetName());
	}

}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input handle component found named %s!"), *InputComponent->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() 
{
	if (!PhysicsHandle)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber press"));
	//TODO: to only raycast when key is presed and see if we reach any actors with physics body collision channel set

	FHitResult Hit = GetFirstPhysicsBodyInReach();

	// get player viewpoint
	FGrabberReachPosition GrabberLocation = GetGrabberReachPosition();
	UPrimitiveComponent *ComponentToGrab = Hit.GetComponent();
	AActor *ActorHit = Hit.GetActor();
	
	if (ActorHit)
	{
		PhysicsHandle
			->GrabComponentAtLocation(
				ComponentToGrab,
				NAME_None,
				GrabberLocation.LineTraceEnd
			);
	}
	// if we hit something then attach the physics handle

	//TODO: attach a physics handle
}

void UGrabber::Release()
{
	if (!PhysicsHandle)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Grabber release"));
	//TODO: remove/release the physics handle
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the physic handle is attach
		//move the object we're holding
	if (PhysicsHandle && PhysicsHandle->GrabbedComponent)
	{
		// get player viewpoint
		FGrabberReachPosition GrabberLocation = GetGrabberReachPosition();

		PhysicsHandle->SetTargetLocation(GrabberLocation.LineTraceEnd);
	}
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0, 5.f);
	
	
	//see what it hits
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	// draw a line from player showing the reach (DEBUG)
	FGrabberReachPosition GrabberLocation = GetGrabberReachPosition();

	// ray-cast out to certain distance (reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()
		->LineTraceSingleByObjectType(
			OUT Hit,
			GrabberLocation.PlayerViewPointLocation,
			GrabberLocation.LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);
		
	return Hit;
}

FGrabberReachPosition UGrabber::GetGrabberReachPosition() const {
	FGrabberReachPosition GrabberLocation;
	// get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT GrabberLocation.PlayerViewPointLocation, 
		OUT GrabberLocation.PlayerViewPointRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewpointLocation.ToString(), *PlayerViewpointRotation.ToString());

	GrabberLocation.LineTraceEnd = GrabberLocation.PlayerViewPointLocation + GrabberLocation.PlayerViewPointRotation.Vector() * Reach;

	return GrabberLocation;
}