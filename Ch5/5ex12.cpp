// Bull or Cow game - guessing game
// Bull : correctly guessed digit in the correct location
// Cow : correctly guessed digit, but not in the correct location
#include "../std_lib_facilities.h"

#define MAX 9999
#define DIGITS 4

int main(){
	vector<int> answer = {1,2,3,4};
	int guess[DIGITS], input;
	int bulls, cows;
	bool correct = false, invalid = false;

	while(!correct){
		try{
			invalid = false;	// reset invalid input flag
			cout << "Enter a four digit number: ";
			cin >> input;

			// range error checking
			if(input > MAX || input < 0){
				cout << "Invalid input value\n";
				continue;
			}

			// seperate out the digits of the user inputed number
			for(int i=DIGITS; i>0; i--){
				guess[i-1] = input%10;
				input/=10;
			}
			
			// test for repeated digits
			for(int i=0; i<DIGITS; i++){
				for(int j=i+1; j<DIGITS; j++){
					if(guess[i] == guess[j]){
						cout << "Repeated digits in number\n";
						invalid = true;
						break;
					}
				}
				if(invalid) break;
			}

			// don't test invalid inputs
			if(invalid) continue;

			bulls = 0;
			cows = 0;

			// Find matching digits and classify them as bulls or cows
			for(int i=0; i<DIGITS; i++){
				for(int j=0; j<DIGITS; j++){
					if(answer[i] == guess[j]){
						if(i == j) bulls++;
						else cows++;
					}
				}
			}

			// Handle game completed condition
			if(bulls == DIGITS){
				cout << "You guessed correctly!\n\n";
				correct = true;
				continue;
			}

			// Handle plurality of score outputs
			if(bulls == 0 || bulls >1){
				cout << bulls << " bulls and ";
			}else{
				cout << bulls << " bull and ";
			}

			if(cows == 0 || cows >1){
				cout << cows << " cows\n\n";
			}else{
				cout << cows << " cow\n\n";
			}
		}catch(...){
			cerr << "Error encounterred\n\n";
		}
	}

	return 0;
}