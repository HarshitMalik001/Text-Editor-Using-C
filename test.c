#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

struct termios orig_termios;

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	struct termios raw;

   	tcgetattr(STDIN_FILENO, &orig_termios);	
	atexit(disableRawMode); 
	
	raw = orig_termios; 
	
	raw.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{	
	enableRawMode();
	char c;

	
  		
	while(read(STDIN_FILENO,&c,1)==1 && c!='!') write(STDOUT_FILENO, &c, 1);

	return 0;
}
