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
			printf(">>>%s\n",argv[1]);
			for(i = 0;i<16&&(c=fgetc(a))!=EOF;i++) printf("%02x ",c);
			printf("\n>>>%s\n",argv[2]);
			for(i = 0;i<16&&(c=fgetc(b))!=EOF;i++) printf("%02x ",c);
			printf("\n");
		}
	}
	else{
		printf("firstdiff [file1] [file2]\n");
	}

}