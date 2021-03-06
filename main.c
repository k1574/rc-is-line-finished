#include <stdlib.h>
#include <stdio.h>

char *argv0;

enum{
	qc = '\'',
	bc = '\\',
};
//const char qc = '\'' ;
//const char bc = '\\' ;

void
usage(void)
{
	fprintf(stderr, "usage: %s <line>\n", argv0);
	exit(1);
}

int
islinefinished(char *s)
{
	int q = 0 ;
	int b = 0 ;
	int cnt = 0 ;
	while(*s){
		switch(*s){
		case qc :
			if(q){
				if(s[1] == qc)
					++s;
				else
					q = 0 ;
			} else {
				q = 1 ;
			}
			break;
		case '{':
		case '(':
			if(q) break;
			++cnt;
			break;
		case '}' :
		case ')' :
			if(q) break;
			--cnt;
			break;
		default:
			break;
		}
		++s;
	}
	if(*--s == bc)
		b = 1 ;

	return (q || b || cnt) ? 0 : 1 ;
}

int
main(int argc, char *argv[])
{
	argv0 = argv[0] ;
	if(argc!=2) usage() ;
	if(!islinefinished(argv[1])) return 1 ;
	return 0 ;
}

