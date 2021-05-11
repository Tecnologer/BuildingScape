// copyright tecnologer

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(const float DeltaTime) const;
	void CloseDoor(const float DeltaTime) const;
	float TotalMassOfActors() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/**The angle to consider door opened*/
	UPROPERTY(EditAnywhere)
	float OpenDoorAngle = 90.f;
	
	/**Initial door angle, 0 if it's closed*/
	UPROPERTY(EditAnywhere)
	float InitialDoorAngle = 0.f;
	
	/**Instance of the trigger base to open the door*/
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	
	/**Instance of the actor that will be trigger open the door*/
	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpen;	
	
	/**Time in seconds to wait before start closing the door*/
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .5f;
	
	/**Door open animation duration in seconds*/
	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.2;
	
	/**Door close animation duration in seconds*/
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed= 1.2;

	/**Minimum of mass to open the door*/
	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	float DoorLastOpened = 0.f;
	float OpenInterpSpeed = 0.f;
	float CloseInterpSpeed = 0.f;
};
