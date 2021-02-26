#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BowPlayer.generated.h"

UCLASS()
class BOWGAME_API ABowPlayer : public ACharacter
{
	GENERATED_BODY()

	// Mesh Components
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* WeaponPointer;

	// Camera Components
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	FTimerHandle BowDrawbackTimer;
	
public:
	ABowPlayer();

	// Misc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Misc)
	class ABowPlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement
	void OnMoveForward(float Value);

	void OnMoveRight(float Value);

	void OnShoot();

	void OnStopShoot();

	void OnTickShoot();

	void OnJump();

	// Getters
	FORCEINLINE class USkeletalMeshComponent* GetWeapon() const
	{
		return Weapon;
	}

	FORCEINLINE class USceneComponent* GetWeaponPointer() const
	{
		return WeaponPointer;
	}

	FORCEINLINE class UCameraComponent* GetCameraComponent() const
	{
		return Camera;
	}

	FORCEINLINE class ABowPlayerController* GetPlayerController() const
	{
		return PlayerController;
	}
};
