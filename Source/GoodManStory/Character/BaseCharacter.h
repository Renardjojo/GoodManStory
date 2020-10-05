// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.generated.h"

class UInputComponent;
class UPawnMovementComponent;
class UShapeComponent;
class USkeletalMeshComponent;


UCLASS(config=Game, Blueprintable, BlueprintType)
class GOODMANSTORY_API ABaseCharacter : public APawn
{
	GENERATED_UCLASS_BODY()

	// Begin Pawn overrides
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;
	virtual void UpdateNavigationRelevance() override;
	// End Pawn overrides

	/**
	 * Input callback to move forward in local space (or backward if Val is negative).
	 * @param Val Amount of movement in the forward direction (or backward if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void MoveForward(float Val);

	/**
	 * Input callback to strafe right in local space (or left if Val is negative).
	 * @param Val Amount of movement in the right direction (or left if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void MoveRight(float Val);

	/**
	 * Input callback to move up in world space (or down if Val is negative).
	 * @param Val Amount of movement in the world up direction (or down if negative).
	 * @see APawn::AddMovementInput()
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void MoveUp_World(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void TurnAtRate(float Rate);

	/**
	* Called via input to look up at a given rate (or down if Rate is negative).
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	UFUNCTION(BlueprintCallable, Category="Pawn")
	virtual void LookUpAtRate(float Rate);
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pawn")
	float BaseTurnRate;

	/** Base lookup rate, in deg/sec. Other scaling may affect final lookup rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pawn")
	float BaseLookUpRate;

public:
	/** Name of the MovementComponent.  Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName MovementComponentName;

protected:
	/** DefaultPawn movement component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	/** The mesh associated with this Pawn. */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshComponent;

	/** DefaultPawn collision component */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UShapeComponent* CollisionComponent;
	
	/*life*/
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	uint8 Life;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	uint8 MaxLife;
	
public:
	/** Name of the CollisionComponent. */
	static FName CollisionComponentName;
	
public:

	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName MeshComponentName;
	
public:

	/** If true, adds default input bindings for movement and camera look. */
	UPROPERTY(Category=Pawn, EditAnywhere, BlueprintReadOnly)
	uint32 bAddDefaultMovementBindings:1;

	/** Returns CollisionComponent subobject **/
	UShapeComponent* GetCollisionComponent() const { return CollisionComponent; }
	/** Returns MeshComponent subobject **/
	USkeletalMeshComponent* GetMeshComponent() const { return MeshComponent; }

	/**
	* @brief Function to inflict dammage to player
	* @param dammage 
	* @return 
	*/
	UFUNCTION(BlueprintCallable, Category = "Life")
    void TakeDammage(uint8 Dammage) noexcept;

	/**
	* @brief Function to heal the player
	* @param dammage
	* @return
	*/
	UFUNCTION(BlueprintCallable, Category = "Life")
    void TakeLife(uint8 AdditionnalLife) noexcept;

	/**
	* @brief return the life of the player
	* @return 
	*/
	UFUNCTION(BlueprintCallable, Category = "Life")
    FORCEINLINE uint8 GetLife() const noexcept { return Life; }

	UFUNCTION(BlueprintCallable, Category = "Life")
    FORCEINLINE float GetLifeRatio() const noexcept { return Life / (float)MaxLife; }
};
