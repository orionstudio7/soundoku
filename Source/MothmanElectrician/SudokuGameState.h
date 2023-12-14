// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SudokuGameState.generated.h"

/**
 * 
 */
UCLASS()
class MOTHMANELECTRICIAN_API ASudokuGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASudokuGameState();
	
	virtual ~ASudokuGameState() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Side;

	TArray<int32> CompletedBoard;
	//current state of the sudoku puzzle
	TArray<int32> CurrentBoard;

};
