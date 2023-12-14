// Fill out your copyright notice in the Description page of Project Settings.


#include "SudokuGameMode.h"
#include "SudokuGameState.h"
#include "Algo/RandomShuffle.h"

using namespace std;

//Constructor
ASudokuGameMode::ASudokuGameMode()
{
	GameStateClass = ASudokuGameState::StaticClass();
}

int32 ASudokuGameMode::GetSideCount() const
{
	return GetGameState<ASudokuGameState>()->Side;
}

int32 ASudokuGameMode::GetTotalSlots() const
{
	return GetGameState<ASudokuGameState>()->Side * GetGameState<ASudokuGameState>()->Side;
}

void ASudokuGameMode::SetSideCount(int32 newSide)
{
	GetGameState<ASudokuGameState>()->Side = newSide;
}

// geeks4geeks
int32 ASudokuGameMode::floorSqrt(int32 x)
{
    // Base cases
    if (x == 0 || x == 1)
        return x;

    // Starting from 1, try all numbers until
    // i*i is greater than or equal to x.
    int i = 1, result = 1;
    while (result <= x) {
        i++;
        result = i * i;
    }
    return i - 1;
}

int32 ASudokuGameMode::GetCellValue(int32 r, int32 c)
{
    int32 rank = floorSqrt(ASudokuGameMode::GetSideCount());
    return (rank * (r % rank) + r / rank + c) % ASudokuGameMode::GetSideCount();
}

TArray<int32> ASudokuGameMode::GetCompletedBoard() const
{
    return GetGameState<ASudokuGameState>()->CompletedBoard;
}

TArray<int32> ASudokuGameMode::GetCurrentBoard() const
{
    return GetGameState<ASudokuGameState>()->CurrentBoard;
}

//shuffles array's contents without modifying the original array
TArray<int32> ASudokuGameMode::ShuffleArray(TArray<int32> toShuffle)
{
    TArray<int32> copy;

    
    //return copy;
    //for (auto i : toShuffle)
    //{
       // copy.Add(i);
    //}

    Algo::RandomShuffle(toShuffle);
    return toShuffle;

}

void ASudokuGameMode::MakeCompletedBoard()
{
    const int32 rank = floorSqrt(ASudokuGameMode::GetSideCount());
    const int32 side = GetGameState<ASudokuGameState>()->Side;

    TArray<int32>& CompletedBoard = GetGameState<ASudokuGameState>()->CompletedBoard;

    // make base range
    TArray<int32> rrank;
    for (int i = 0; i < rank; i++)
    {
        rrank.Add(i);
    }

    //make range of usable numbers
    TArray<int32> rnums;
    for (int i = 0; i < side; i++)
    {
        rnums.Add(i+1);
    }

    //make row indices 
    TArray<int32> rowIndices;

    TArray<int32> rowCopy1 = ShuffleArray(rrank);
    TArray<int32> rowCopy2 = ShuffleArray(rrank);

    for (int i = 0; i < rank; i++)
    {
        int32 g = rowCopy1[i];
        
        for (int j = 0; j< rank; j++)
        {
            int32 r = rowCopy2[j];
            rowIndices.Add( g * rank + r);
        }
    }
    
    //make column indices 
    TArray<int32> columnIndices;

    TArray<int32> columnCopy1 = ShuffleArray(rrank);
    TArray<int32> columnCopy2 = ShuffleArray(rrank);

    for (int i = 0; i < rank; i++)
    {
        int32 g = columnCopy1[i];
        
        
        for (int j = 0; j < rank; j++)
        {
            int32 c = columnCopy2[j];
            columnIndices.Add( g * rank + c);

        }
    }
    Algo::RandomShuffle(rnums);

    //populate the board
    CompletedBoard;

    for (int i = 0; i< side; i++)
    {
        int32 c = columnIndices[i];

        for (int j = 0; j < side; j++)
        {
            int32 r = rowIndices[j];
            int32 p = GetCellValue(r, c);

            
            CompletedBoard.Add(rnums[p]);
        }
    }

}


void ASudokuGameMode::MakeBeginningBoard()
{
    const int32 side = GetGameState<ASudokuGameState>()->Side;
    const int32 emptySpaces = (side * side * 1) / 4;
    TArray<int32>& CompletedBoard = GetGameState<ASudokuGameState>()->CompletedBoard;
    TArray<int32>& CurrentBoard = GetGameState<ASudokuGameState>()->CurrentBoard;
    TArray<int32> randomIndices; 

    //populate indices, and copy the completed board
    for (int i = 0; i < side * side; i++)
    {
        randomIndices.Add(i);
        int32 value = CompletedBoard[i];
        CurrentBoard.Add(value);
    }

    Algo::RandomShuffle(randomIndices);

    //clear empty spaces on board
    for (int i = 0; i < emptySpaces; i++)
    {
        CurrentBoard[randomIndices[i]] = 0;
    }
}

//Assumes that CurrentBoard and CompletedBoard are the same size
bool ASudokuGameMode::CheckCompleteness()
{

    TArray<int32>& CompletedBoard = GetGameState<ASudokuGameState>()->CompletedBoard;
    TArray<int32>& CurrentBoard = GetGameState<ASudokuGameState>()->CurrentBoard;

    for (int i = 0; i < CurrentBoard.Num(); i++)
    {
        if (CurrentBoard[i] != CompletedBoard[i])
        {
            return false;
        }
    }
    return true;
}

void ASudokuGameMode::SetBox(int32 index, int32 value)
{
    GetGameState<ASudokuGameState>()->CurrentBoard[index] = value;
}