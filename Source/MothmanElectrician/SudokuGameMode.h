// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SudokuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOTHMANELECTRICIAN_API ASudokuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASudokuGameMode();

	virtual ~ASudokuGameMode() = default; //sets up a default destructor

	//Returns the number of boxes per side 
	UFUNCTION(BlueprintPure, Category = "GameGrid")
	virtual int32 GetSideCount() const;

	//Returns the total number of slots in the sudoku grid
	UFUNCTION(BlueprintPure, Category = "GameGrid")
	virtual int32 GetTotalSlots() const;

	UFUNCTION(BlueprintPure, Category = "GameGrid")
	virtual TArray<int32> GetCompletedBoard() const;

	UFUNCTION(BlueprintCallable, Category = "GameGrid")
	virtual void SetSideCount(int32 newSide);

	UFUNCTION(BlueprintPure, Category = "GameGrid")
	virtual TArray<int32> GetCurrentBoard() const;

	UFUNCTION(BlueprintCallable, Category = "GameGrid")
	virtual void MakeCompletedBoard();

	UFUNCTION(BlueprintCallable, Category = "GameGrid")
	virtual void MakeBeginningBoard();

	UFUNCTION(BlueprintCallable, Category = "GameGrid")
	virtual bool CheckCompleteness();

	UFUNCTION(BlueprintCallable, Category = "GameGrid")
	virtual void SetBox(int32 index, int32 value);

	virtual int32 floorSqrt(int32 x);

	virtual int32 GetCellValue(int32 r, int32 c);
	
	virtual TArray<int32> ShuffleArray(TArray<int32>);


	//variables
	//int32 Side;

};
