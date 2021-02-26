#include "Core/BowPlayer.h"
#include "Engine.h"

ABowPlayer::ABowPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

	// Mesh Components
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
	Weapon->SetCollisionObjectType(ECC_Pawn);

	WeaponPointer = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponPointer"));
	WeaponPointer->SetupAttachment(GetWeapon());
	
	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->SetRelativeLocation(FVector(-40.0f, 2.0f, 64.0f));
	Camera->bUsePawnControlRotation = true;
	
	// Character Movement
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
}

void ABowPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABowPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABowPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABowPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABowPlayer::OnMoveRight);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABowPlayer::OnJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Mouse
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Gameplay
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABowPlayer::OnShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABowPlayer::OnStopShoot);
}

void ABowPlayer::OnMoveForward(float Value)
{
	AddMovementInput(GetMesh()->GetForwardVector(), Value, false);
}

void ABowPlayer::OnMoveRight(float Value)
{
	AddMovementInput(GetMesh()->GetRightVector(), Value, false);
}

void ABowPlayer::OnShoot()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetWorld()->GetTimerManager().SetTimer(BowDrawbackTimer, this, &ABowPlayer::OnTickShoot, 1.0f);
}

void ABowPlayer::OnStopShoot()
{
	if (!BowDrawbackTimer.IsValid()) return;

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	float HeldTime = GetWorld()->GetTimerManager().GetTimerRemaining(BowDrawbackTimer);

	/*
	 * Get normalized value between 0 - 1
	 * Represents power, 1 is full power held
	 * Adds to velocity, 1 goes the furthest, 0 doesn't shoot, 0.5 shoots... somewhere
	 */

	
	GEngine->AddOnScreenDebugMessage(0, 2.0F, FColor::White, FString::Printf(TEXT("Held %f"), HeldTime), true);
	// Full Power Shot
	if (HeldTime <= 0)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.0F, FColor::White, FString("PEW PEW PEW"), true);
	}

	GetWorld()->GetTimerManager().ClearTimer(BowDrawbackTimer);
}

void ABowPlayer::OnTickShoot()
{
}


void ABowPlayer::OnJump()
{
	Jump();
}



