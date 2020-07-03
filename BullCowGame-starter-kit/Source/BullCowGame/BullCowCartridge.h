// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls, Cows;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
	FString HiddenWord;
	TMap<TCHAR, int32> HiddenWordLetters;
	int32 NLetters, NLives;
	bool bGameOver;
	TArray<FString> WordList;

	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess);
	// bool IsIsogram(const FString& Word) const;
	void StripNonValidWords();
	FBullCowCount GetBullCows(FString Guess) const;
	void SetHiddenWordLetters();
};
