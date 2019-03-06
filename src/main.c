#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 4096

int readachar(FILE *f, size_t *read, size_t *index, unsigned char *p){
	if(*read==*index){
		if(feof(f)) return -1;
		*read = fread(p,sizeof(unsigned char), BUFSIZE,f);
		if(*read==0) return -1;
		*index = 0;
		if(ferror(f)) return -1;
		return 0;
	}
	(*index)++;
	return 0;
}

int main(int argc, char *argv[]) {
	if(argc==3){
		FILE *a = fopen(argv[1],"rb");
		FILE *b = fopen(argv[2],"rb");
		long i;
		size_t cr = 0, dr = 0, ci = 0, di = 0;
		unsigned char *c, *d;
		c = malloc(BUFSIZE * sizeof(unsigned char));
		d = malloc(BUFSIZE * sizeof(unsigned char));
		*c = 0;
		*d = 0;
		int err = 0;
		cr = fread(c, sizeof(unsigned char), BUFSIZE,a);
		dr = fread(d, sizeof(unsigned char), BUFSIZE,b);
		for( i = 0; ci==cr||di==dr||*(d+di)==*(c+ci); i++, ci++, di++){
			if(ci == cr) {
				if(feof(a)){
#ifdef DEBUG
					printf("eof\n");
#endif
					break;
				} 
				cr = fread(c, sizeof(unsigned char), BUFSIZE,a);
				if(cr==0){
					//to ensure other file also reads EOF
					dr = fread(d, sizeof(unsigned char), BUFSIZE,b);
					break;
				}
				ci = 0;
				if(ferror(a)){
#ifdef DEBUG
					printf("err\n");
#endif
					err=1;
					break;
				}
			}
			if(di == dr){
				if(feof(b)){
#ifdef DEBUG
					printf("eof\n");
#endif
					break;
				} 
				dr = fread(d, sizeof(unsigned char), BUFSIZE,b);
				if(dr==0)break;
				di = 0;
				if(ferror(b)){
#ifdef DEBUG
					printf("err\n");
#endif
					err=1;
					break;
				}
			}
		}
		if(err){
			printf("error %d,%d",ferror(a),ferror(b));
		}
		if(feof(a)==feof(b)!=0&&*(d+di)==*(c+ci)){
			printf("files are the same 0x%lx\n",i-1);
		}
		else{
			printf("First difference at 0x%lx 0x%02x!=0x%02x\n",i,*(c+ci),*(d+di));
			printf(">>>%s\n",argv[1]);
			for(i = 0;i<16&&readachar(a,&cr,&ci,c)!=-1;i++) printf("%02x ",*(c+ci));
			printf("\n>>>%s\n",argv[2]);
			for(i = 0;i<16&&readachar(b,&dr,&di,d)!=-1;i++) printf("%02x ",*(d+di));
			printf("\n");
		}
	}
	else{
		printf("firstdiff [file1] [file2]\n");
	}

}