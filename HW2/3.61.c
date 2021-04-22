# include <stdio.h>

long cread(long *xp){
	return (xp? *xp : 0);
}

long cread_alt(long *xp)
{
    long q=0;
    long *p = ( xp ? xp : &q);
	return *p;   
}

int main(){
	;
}
