# BullCowGame

My second Unreal 4 project.

## Gameplay

- The player has a limited amount of chances to guess a hidden word.
- After each try, if the player lives didn't reach 0, the game prompts how many bulls and cows the guess contained.
  - A cow is a letter in the player's guess that is present in the hidden word at a different location.
  - A bull is a letter in the player's guess that is present in the hidden word at the same location.

  The player can use this information to try again.

## Development

This game is the first of a series I made following the [Unreal4 C++ Developer: Learn C++ and Make Video Games](https://www.gamedev.tv/p/learn-unreal-engine-c-developer-4-22-for-video-game-development?coupon=1D3ABAD8) course.

Since this first project is meant for C++ beginners and I already had experience with the language, I wrote the majority of the code independently. I am quite satisfied with my results: I was able to extend the original project, which was limited to isograms (words with no repeating letters), to any kind of english word.
