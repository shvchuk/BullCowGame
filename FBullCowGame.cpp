#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess)) { // if the guess isnt an isogram

		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { // if the guess inst all lowercase return an error

		return EWordStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) { // if the guess length is wrong return an error

		return EWordStatus::Wrong_Length;
	}
	else {

		return EWordStatus::OK;
	}
	
};


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess


	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the guess word
		for (int32 j = 0; j < WordLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true;  }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	// loop through all the letters of the word
		// if the letter is in the map
			// we do NOT have an isogram
		// otherwise
			// add the letter to the map as seen

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
