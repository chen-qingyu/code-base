#include <stdio.h>
char *I="#include <stdio.h>%cchar *I=%c%s%c;%cint main(){printf(I,10,34,I,34,10);}";
int main(){printf(I,10,34,I,34,10);}