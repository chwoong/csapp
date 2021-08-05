/*
 * reference: https://github.com/simnalamburt/snucse/blob/master/System%20Programming/cachelab/part_a/csim.c
*/

#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	bool valid;
	int tag;
	int times;
}line;

typedef struct{
	line *lines;
}set;

typedef struct{
	set *sets;
}mycache;

//변수 명은 교과서에 있는대로
int S=0,s=0,E=0,B=0,b=0;
int hits=0,misses=0,evictions=0;
mycache cache={};
FILE *file;

//이번에는 안 사용한 times를 하나씩 증가시켜서 그 중 최댓값은 뽑아내는 방법으로 짜보자
//lru 알고리즘 방법은 수도 없이 많다. 
void update(set *ms,int i){
	line *ml=&(ms->lines[i]);
	for(int i=0;i<E;i++){
		line *it=&(ms->lines[i]);
		if(!(it->valid)) continue;
		if(it->times <= ml->times) continue;
		(it->times)--;
	}
	ml->times = E-1;
}

//각 simulate 마다 무조건 한번 만의 update가 일어남
void simulate(int addr){
	int set_index=((1<<s)-1)&(addr>>b);
	int tag=(addr>>(s+b))&((1<<(32-s-b))-1);
	set *myset=&cache.sets[set_index];
	for(int i=0;i<E;i++){
		line *myline=&(myset->lines[i]);
		if(!(myline->valid)) continue;
		if((myline->tag) != tag) continue;
		//hits
		hits++;
		update(myset,i);
		return;
	}
	//캐시 미스
	misses++;
	//빈 캐시 라인이 있는 확인
	for(int i=0;i<E;i++){
		line *ml=&(myset->lines[i]);
		if(ml->valid) continue;
		else{
			//이번에 캐싱 해놓는다
			ml->valid=true;
			ml->tag=tag;
			update(myset,i);
			return;
		}
	}
	//빈 캐시가 없다는 뜻이고 교체 필요
	evictions++;
	for(int i=0;i<E;i++){
		line *ml=&(myset->lines[i]);
		if(ml->times) continue;
		else{
			//lru 교체 알고리즘에 맞게 교체한다
			ml->valid=true;
			ml->tag=tag;
			update(myset,i);
			return;
		}
	}
	exit(2);
	return;
}

int main(int argc,char **argv){
	
	int opt;	
	while((opt=getopt(argc,argv,"s:E:b:t:")) !=-1){
		switch(opt){
			case 's':
				s=atoi(optarg);
				if(s==0) return 1;
				S=2<<s;
				break;
			case 'E':
				E=atoi(optarg);
				if(E==0) return 1;
				break;
			case 'b':
				b=atoi(optarg);
				break;
			case 't':
				if(!(file = fopen(optarg, "r"))) return 1;
				break;
			default:
				return 1;  
		}
	}
	
	cache.sets = malloc(sizeof(set)*S);
	for(int i=0;i<S;i++){
		//초기에 모두 0으로 세팅
		cache.sets[i].lines=calloc(sizeof(line),E);
	}
	
	//데이터 형태:
	//[space]M 0421c7f0,4
	
	char operation;
	int address;
	while(fscanf(file," %c %x%*c%*d",&operation,&address)!=EOF){
		if(operation=='I') continue;
		simulate(address);
		if(operation=='M') simulate(address);
	}

	printSummary(hits,misses,evictions);
	
	/* free */
	fclose(file);
	for(int i=0;i<S;i++) free(cache.sets[i].lines);
	free(cache.sets);
	
	return 0;
	
}
