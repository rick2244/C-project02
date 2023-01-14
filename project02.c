#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct val{
	char name[32];
	int qty;
	int aisle;
	int bin;
	struct val *next;
};
struct val *make_val(){
	struct val *v = malloc(sizeof(struct val));
	if(!v){
		printf("failed to malloc(struct val)\n");
		exit(-1);
	}
	return v;
}
struct val *insert_sorted(struct val *head, struct val *pf){
	if(!head){
		return pf;
	}
	if(pf->aisle < head->aisle){
		pf->next = head;
		return pf;
	}

	struct val *walk = head;
	struct val *prev;
	while(walk && (pf->aisle > walk->aisle)){
		prev = walk;
		walk = walk->next;
	}
	pf->next = walk;
	prev->next = pf;
	
	return head; 
}
const char* assign(struct val *pf, char buff[64],  int i){
	//pf = make_val();
	char name[16];
	char qty1[2];
	char aisle1[2];
	char bin1[2];
	char *s = buff;
	i = 0;
	while(s[i] != ','){
		name[i] = s[i];
		i++;		
	}
	name[i] = '\0';
	strcpy(pf->name, name);
	i++;
	qty1[0] = s[i];
	qty1[1] = '\0';
	int qty = atoi(qty1);
	pf->qty = qty;
	i+=2;
	aisle1[0] = s[i];
	aisle1[1] = '\0';
	int aisle = atoi(aisle1);
	pf->aisle = aisle;
	s+=2;
	bin1[0] = s[i];
	bin1[1] = '\0';
	int bin = atoi(bin1);
	pf->bin = bin;
	pf->next = NULL;
}

int main(int argc, char *argv[]){
	struct val *head = NULL;
	char* path = argv[1];
	char *mode = "r";
	FILE* f = fopen(path, mode);
	if(!f){
		printf("failed to open: %s\n", path);
		return -1;
	}
	struct val *pf = make_val();
	char buffer[64];
	int i = 0;
	int row = 0;
	while(fgets(buffer,64, f)){
		row++;
		i = 0;
		if(row == 1){
			continue;
		}
		if(row > 1){
			assign(pf, buffer, i);
			//pf->next = NULL;
			//pf = insert_sorted(head, pf);
			head = insert_sorted(head, pf);
			pf = make_val();
			}

		/*while(head != NULL){
			printf("%s: quantity: %d, aisle: %d, bin: %d\n", head->name, head->qty, head->aisle, head->bin);
			head = head->next;
		}*/		
	}
	while(head != NULL){
		printf("%s: quantity: %d, aisle: %d, bin: %d\n", head->name, head->qty, head->aisle, head->bin);
		head = head->next;
	}
		
	free(pf);
	fclose(f);
}




