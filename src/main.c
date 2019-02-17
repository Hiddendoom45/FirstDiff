#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc==3){
		FILE *a = fopen(argv[1],"rb");
		FILE *b = fopen(argv[2],"rb");
		char c;
		int i;
		for (i = 0; (c=fgetc(a))==fgetc(b)&&c!=EOF;i++);
		if(c==EOF){
			printf("Files are the same\n");
		}
		else{
			printf("First difference at 0x%x\n",i);
		}
	}
	else{
		printf("firstdiff [file1] [file2]\n");
	}

}