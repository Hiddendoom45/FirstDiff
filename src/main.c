#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc==3){
		FILE *a = fopen(argv[1],"rb");
		FILE *b = fopen(argv[2],"rb");
		int c, d;
		long i;
		for (i = 0; (c=fgetc(a))==(d=fgetc(b))&&c!=EOF;i++);
		if(ferror(a)!=0||ferror(b)!=0){
			printf("error %d,%d",ferror(a),ferror(b));
		}
		if(c==EOF&&d==EOF){
			printf("Files are the same length=0x%lx\n",i);
		}
		else{
			printf("First difference at 0x%lx 0x%x!=0x%x\n",i,c,d);
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