#pragma once

#include "CoreMinimal.h"
#include "BowPlayer.h"
#include "GameFramework/PlayerController.h"
#include "BowPlayerController.generated.h"

UCLASS()
class BOWGAME_API ABowPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Misc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Misc)
	class ABowPlayer* PlayerReference;
};
