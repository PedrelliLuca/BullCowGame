// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    // Get 1000 words from txt file
    // FPaths::ProjectContentDir() will return the absolute path to the Content directory
    const FString WordsPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordsPath);

    // Cut our words that aren't isograms or whose lenght is not in [4, 8]
    StripNonValidWords();

    PrintLine(TEXT("Welcome to BullCowGame!"));
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking player guess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = WordList[FMath::RandRange(0, WordList.Num() - 1)];
    // HiddenWord = TEXT("eclectic"); Great word for testing purposes
    SetHiddenWordLetters();

    NLetters = HiddenWord.Len();
    NLives = 2 * NLetters; // The difficulty ramps up with non-isograms -> double lives!
    bGameOver = false;

    // Testing only
    // PrintLine(FString::Printf(TEXT("The word to guess is %s."), *HiddenWord));
    // for (auto& Elem : HiddenWordLetters)
    //     PrintLine(TEXT("(%c, %i)"), Elem.Key, Elem.Value);
    
    PrintLine(TEXT("You have %i lives."), NLives);
    PrintLine(TEXT("Guess the %i-letters word."), NLetters);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    HiddenWordLetters.Empty();
    PrintLine(TEXT("Press enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You won, cool!"));
        EndGame();
        return;
    }
    
    // Error that do not cause to lose a life
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The word you inserted has %i letters,\nbut the hidden one has %i!"), Guess.Len(), NLetters);
        PrintLine(TEXT("Guess the %i-letters word."), NLetters);
        return;
    }

    // if (!IsIsogram(Guess))
    // {
    //     PrintLine(TEXT("The word you inserted is not an isogram,\nsome of its letters are the same!"));
    //     PrintLine(TEXT("Guess the %i-letters word."), NLetters);
    //     return;
    // }

    // Remove life
    PrintLine(TEXT("Wrong word, you lose a life.\nYou have %i left."), --NLives);
    if (NLives <= 0)
    {
        PrintLine(TEXT("You lost the game.\nThe hidden word was %s."), *HiddenWord);
        EndGame();
        return;
    }

    FBullCowCount BullCow = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows."), BullCow.Bulls, BullCow.Cows);
    PrintLine(TEXT("Guess the %i-letters word."), NLetters);
}

// bool UBullCowCartridge::IsIsogram(const FString& Word) const
// {
//     for (int32 i=0; i < Word.Len()-1; i++)
//         for (int32  j=i+1; j < Word.Len(); j++)
//             if (Word[i] == Word[j])
//                 return false;
    
//     return true;
// }

void UBullCowCartridge::StripNonValidWords()
{
    for (int32 i = 0; i < WordList.Num();)
        if (/*!IsIsogram(WordList[i]) ||*/ WordList[i].Len() < 4 || WordList[i].Len() > 8)
            WordList.RemoveAt(i);
        else
            i++;
}

FBullCowCount UBullCowCartridge::GetBullCows(FString CopyGuess) const
{
    int32 BullCount = 0, CowCount = 0;
    TMap<TCHAR, int32> AvailableLetters = HiddenWordLetters;

    // Checking for the bulls
    for (int32 i = 0; i < CopyGuess.Len(); i++)
        if (CopyGuess[i] == HiddenWord[i])
        {
            BullCount++;
            AvailableLetters[CopyGuess[i]]--;
            CopyGuess[i] = '$'; // Special character to replace bulls with. Avoids false cows in the for below.
        }
    
    // Checking for the cows on the remaining letters of the CopyGuess
    for (auto Letter : CopyGuess)
        if (AvailableLetters.Contains(Letter) && AvailableLetters[Letter] > 0)
        {
            CowCount++;
            AvailableLetters[Letter]--;
        }
    
    return {BullCount, CowCount};
}

void UBullCowCartridge::SetHiddenWordLetters()
{
    for (auto Letter : HiddenWord)
    {
        if(!HiddenWordLetters.Contains(Letter))
            HiddenWordLetters.Add(Letter);
        HiddenWordLetters[Letter]++;
    }
}
