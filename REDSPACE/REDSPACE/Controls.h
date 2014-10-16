#pragma once

struct Controls{
	WORD up,down,left,right;
	Controls(WORD U, WORD D, WORD L, WORD R){
		up = U;
		down = D;
		left = L;
		right = R;
	}
	Controls(){};
};