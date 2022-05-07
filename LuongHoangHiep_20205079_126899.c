#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct NODE{
	char name[4];
	float mo,dong;
	struct NODE *rightchild;
    struct NODE *leftchild;
}Node;
Node *root[10];
Node *makeNode(char* name,float mo,float dong)
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->mo=mo;
    a->dong=dong;
    strcpy(a->name,name);
    a->leftchild =  NULL;
    a->rightchild = NULL;
    return a;
}

Node *InsertNode(Node *r,char* name,float mo,float dong)
{
    if (r==NULL) return makeNode(name,mo,dong);
    if (strcmp(r->name,name)==0) {printf("This profile exits\n"); return r;}
    else if (strcmp(r->name,name)>0) r->leftchild = InsertNode(r->leftchild,name,mo,dong);
    else r->rightchild = InsertNode(r->rightchild,name,mo,dong);
    return r;
}

Node *FindNode(Node *r,char* username)
{
    if (r==NULL) return NULL;
    if (strcmp(r->name,username)<0) return FindNode(r->rightchild,username);
    else if (strcmp(r->name,username)>0) return FindNode(r->leftchild,username);
    else return r;
}

void docfile(){
	FILE *f = fopen("data.txt","r");
    if(f==NULL) {printf("Plese check your file\n");return;}
    char name[4];
	float mo,dong;
	int N,i,j;
	fscanf(f,"%d",&N);
	for(i=0;i<10;i++){
		root[i]=NULL;
		for(j=0;j<N ;j++){
			fscanf(f,"%s %f %f",&name,&mo,&dong);
			root[i]=InsertNode(root[i],name,mo,dong);
		}
	}
    fclose(f);
}

void show(Node *r){
	if(r==NULL) return;
    show(r->leftchild);
    int i;float tb=0;
    tb=tb+r->dong-r->mo;
    for(i=1;i<10;i++){
    	Node *p=FindNode(root[i],r->name);
		if(p!=NULL){
			tb=tb+p->dong-p->mo;
		}
	}
	printf("%s %.3f\n",r->name,tb/10);
    show(r->rightchild);	
}

void Timkiem(){
	printf("Nhap ma co phieu:");
	char tencp[4];
	fflush(stdin);
	gets(tencp);
	int i;
	float min=10000,max=-10000;
	for(i=0;i<10;i++){
		Node *p=FindNode(root[i],tencp);
		if(p!=NULL){
			if(p->dong<min) min=p->dong;
			if(p->dong>max) max=p->dong;
		}
	}
	if(min!=10000 && max != -10000){
		printf("Gia cao nhat: %.3f,gia thap nhat: %.3f\n",max,min);
	}else printf("Khong tim thay!\n");
}

void Timkiemmatang(Node *r){
	if(r==NULL) return;
	if((r->dong-r->mo)>0){
		Node *p=FindNode(root[1],r->name);
		if(p!=NULL && (p->dong-p->mo)>0)
			printf("%s\n",p->name);
	}
    Timkiemmatang(r->leftchild);
    Timkiemmatang(r->rightchild);
}

void Freenode(Node *r){
	if(r==NULL) return;
	Freenode(r->leftchild);
	Freenode(r->rightchild);
	free(r);
}
int main(){
	int n,i;
	do{
		printf("Menu:\n");
		printf("1.Doc file\n");
		printf("2.Tim kiem theo ma chung khoan\n");
		printf("3.Tim kiem ma chung khoan co xu huong tang\n");
		printf("4.Tim ma co so ngay tang lon nhat\n");
		printf("5.Thoat\n");
		printf("Nhap lua chon:\n");
		scanf("%d",&n);
		switch(n){
			case 1:
				docfile();
				show(root[0]);
				break;
			case 2:
				Timkiem();
				break;
			case 3:
				Timkiemmatang(root[0]);
				break;
			case 5:
				for(i=0;i<10;i++){
					Freenode(root[i]);
				}
				printf("Luong Hoang Hiep - 20205079\n");
				break;
			default:
				printf("Ko co chuc nang da chon\n");
				break;
		}
	}while(n!=5);
	return 0;
}
