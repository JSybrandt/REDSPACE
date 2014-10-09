#pragma once

struct Controls{
	char up,down,left,right;
	Controls(char U, char D, char L, char R){
		up = U;
		down = D;
		left = L;
		right = R;
	}
	Controls(){};
};