// The header file MyCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()
    
    public:
    // Sets default values for this character's properties
    AMyCharacter();
    
    protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    // VR Camera component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* VRCameraComponent;
    
    // Base turn rate, in deg/sec. Other scaling may affect final turn rate.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;
    
    // Base look up/down rate, in deg/sec. Other scaling may affect final rate.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;
    
    // Handles moving forward/backward
    void MoveForward(float Value);
    
    // Handles moving right/left
    void MoveRight(float Value);
    
    // Handles turning based on the turn rate
    void TurnAtRate(float Rate);
    
    // Handles looking up and down based on the look up rate
    void LookUpAtRate(float Rate);
}