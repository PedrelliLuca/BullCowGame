# BullCowGame
Simple game where the player has a limited number of tries to guess an isogram (word with no repeating letters).

This game is the first of a series of Unreal4 projects I replicated following the [Unreal4 C++ Developer: Learn C++ and Make Video Games](https://www.gamedev.tv/p/learn-unreal-engine-c-developer-4-22-for-video-game-development?coupon=1D3ABAD8) course.
It wasn't my first project in Unreal, and the level of difficulty was a bit too low even for a begginer course in my opinion, but I still learned something new about the engine so it was worth it.

## Game Flow

The hidden isogram is extracted from a file containing 1000 words. The player has a number of tries equal to the lenght of the word to guess it correctly.

After making a guess and pressing enter:
- If the word is correct the player wins

- If the word is wrong but the player has some lives left, he loses one and receives a suggestion based on how many "cows" and "bulls" are in the word he typed.
  - A cow is a letter that is in the hidden isogram but was inserted in the wrong position.
  - A bull is a letter that is in the hidden isogram and in the right position.
