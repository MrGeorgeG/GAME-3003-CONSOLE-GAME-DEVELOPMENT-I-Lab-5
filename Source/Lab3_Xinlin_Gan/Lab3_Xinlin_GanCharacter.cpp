// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab3_Xinlin_GanCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALab3_Xinlin_GanCharacter::ALab3_Xinlin_GanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALab3_Xinlin_GanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALab3_Xinlin_GanCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALab3_Xinlin_GanCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALab3_Xinlin_GanCharacter::TouchStopped);
}

void ALab3_Xinlin_GanCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ALab3_Xinlin_GanCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ALab3_Xinlin_GanCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ALab3_Xinlin_GanCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnControllerConnectionHandle = FCoreDelegates::OnControllerConnectionChange.AddUFunction(this, FName("OnControllerConnectionChange"));
}

void ALab3_Xinlin_GanCharacter::EndPlay(const EEndPlayReason::Type EndplayReason)
{
	Super::EndPlay(EndplayReason);
	FCoreDelegates::OnControllerConnectionChange.Remove(OnControllerConnectionHandle);
}

void ALab3_Xinlin_GanCharacter::OnControllerConnectionChange_Implementation(bool Connected, int32 UserID, int32 ControllerID)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, 
		FString::Printf(TEXT("Connection Change ControllerID: %d, Connected: %d, Connected: %d"), ControllerID, Connected));
}