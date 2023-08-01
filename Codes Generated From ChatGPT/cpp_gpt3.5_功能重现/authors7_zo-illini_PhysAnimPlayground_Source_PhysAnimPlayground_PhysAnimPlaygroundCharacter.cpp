// Copyright 2023 YourCompanyName. All rights reserved.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the VR Camera component to the RootComponent
	VRCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCameraComponent->SetupAttachment(GetRootComponent());
	VRCameraComponent->bUsePawnControlRotation = true;

	// Set the default values for the VR movement.
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind the movement input actions to the corresponding functions.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	// Bind the rotation input actions to the corresponding functions.
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyCharacter::LookUpAtRate);

	// Bind the jump input action to the corresponding function.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		// Determine the forward direction based on the VR camera's yaw.
		const FRotator Rotation = VRCameraComponent->GetRelativeRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		// Add the forward movement input.
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		// Determine the right direction based on the VR camera's yaw.
		const FRotator Rotation = VRCameraComponent->GetRelativeRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// Add the right movement input.
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::TurnAtRate(float Rate)
{
	// Calculate the new rotation based on the input rate and the base turn rate.
	const float NewRotation = Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds();

	// Apply the new rotation to the character.
	AddControllerYawInput(NewRotation);
}

void AMyCharacter::LookUpAtRate(float Rate)
{
    // Calculate the new rotation based on the input rate and the base look up rate.
    const float NewRotation = Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds();

    // Apply the new rotation to the character.
    AddControllerPitchInput(NewRotation);
}

