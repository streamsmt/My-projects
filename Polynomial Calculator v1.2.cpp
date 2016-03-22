#include<stdio.h>
#include<stdlib.h>
//多项式结构体 
struct poly{
	float co;
	int order;
	struct poly*next;
};
//存储两个多项式的结构体（用于多项式的除法）
struct doublepoly{
	struct poly *po1;
	struct poly *po2;
}; 
//多项式创建函数 
struct poly *createlistf(void){
	struct poly*head=NULL;
	struct poly*p=NULL;
	float no;
	int ord;
	printf("请依次输入次数和对应的系数，然后以-1结尾，（例如6x+3x^2对应1 6 2 3 -1）:");
	scanf("%d",&ord);
	while(ord!=-1){
		p=(struct poly*)malloc(sizeof(struct poly));
		scanf("%f",&no);
		p->co=no;
		p->order=ord;
		p->next=head;
		head=p;
		scanf("%d",&ord);
	}
	return head;
}
//多项式复制函数 
struct poly *polycopy(struct poly *a){
	struct poly *p=a, *cp=NULL,*result=NULL;
	while(p!=NULL){
		cp=(struct poly *)malloc(sizeof(struct poly));
		cp->co=p->co;
		cp->order=p->order;
		cp->next=result;
		result=cp;
		p=p->next;
	} 
	return result;
}
//多项式排序函数
int polysort(struct poly **a){
	struct poly *rec=*a,*p=*a,*cp=NULL,*head=NULL;
	if(p!=NULL){
		cp=(poly *)malloc(sizeof(poly));
		cp->co=p->co;
		cp->order=p->order;
		cp->next=head;
		head=cp;
		p=p->next;
		while(p!=NULL){
			poly *sp1=head,*sp2=NULL;
			while(p->order<=sp1->order&&sp1->next!=NULL){
				sp2=sp1;
				sp1=sp1->next;
			}
			//终止情况1 
			if(sp1->order<=p->order){
				//终止情况1-1 
				if(sp1->order<p->order){
					poly *ccp=(poly *)malloc(sizeof(poly));
					ccp->co=p->co;
					ccp->order=p->order;
					if(sp2==NULL){
						ccp->next=head;
						head=ccp;
					}
					else{
						ccp->next=sp1;
						sp2->next=ccp;
					}
				}
				//终止情况1-2 
				else
					sp1->co+=p->co;
			}
			else{
				poly *ccp=(poly *)malloc(sizeof(poly));
				ccp->co=p->co;
				ccp->order=p->order;
				sp1->next=ccp;
				ccp->next=NULL;
			}
			poly *temp=p->next;
			p=temp;
		}
	}
	*a=head;
	return 0;
} 
//多项式化简函数
int polysimp(struct poly **a){
	struct poly *rec=*a,*p=*a,*prep=NULL,*waitdel=NULL;//waitdel用于处理链表第一个元素系数为0的情况 
	if(p->co==0)
		waitdel=p; 
	while(rec!=NULL){
			p=rec;
			p=rec->next;
			prep=rec;
			while(p!=NULL){
				if(p->co==0){
					prep->next=p->next;
					free(p);
					p=prep->next;			
				}
				else{
					if(rec->order==p->order){
						rec->co+=p->co;
						prep->next=p->next;
						free(p);
						p=prep->next;	
					}
					else{
						prep=p;
						p=p->next;
					}
				}
			}
			rec=rec->next;
	}
	if(waitdel!=NULL){
		*a=waitdel->next;
		free(waitdel);
	}
	return 0;
}

//多项式打印函数
int polyprint(poly *a){
	struct poly*head=a;
	struct poly*p=a;
	while(p!=NULL){
		if(p==head){
			if(p->order==1)
			 	printf("%fx ",p->co);
			if(p->order==0)
				printf("%f ",p->co);
			if(p->order!=1&&p->order!=0)
				printf("%fx^%d ",p->co,p->order);
		}
		else{
			if(p->co<0){
				if(p->order==1)
			 		printf("%fx ",p->co);
				if(p->order==0)
					printf("%f ",p->co);
				if(p->order!=1&&p->order!=0)
					printf("%fx^%d ",p->co,p->order);		
			}
			else{ 
				if(p->order==1)
		 			printf("+%fx ",p->co);
				if(p->order==0)
					printf("+%f ",p->co);
				if(p->order!=1&&p->order!=0)
					printf("+%fx^%d ",p->co,p->order);
			}	 				
		}
		p=p->next;
	}
	return 0;
}
//多项式相加函数 
struct poly *polyplus(poly *a, poly *b){
	struct poly *p=a,*result=NULL ,*cp=NULL;
	if(p!=NULL){
		while(p!=NULL){
			cp=(struct poly *)malloc(sizeof(struct poly));
			cp->co=p->co;
			cp->order=p->order;
			cp->next=result;
			result=cp;
			p=p->next;
		}
		if(b!=NULL){
			p=b;
			while(p!=NULL){
			cp=(struct poly *)malloc(sizeof(struct poly));
			cp->co=p->co;
			cp->order=p->order;
			cp->next=result;
			result=cp;
			p=p->next;	
			}
		}	
	}
	else
		return b;
	return result;
}
//多项式相乘函数 
struct poly *polymulti(poly *a,poly *b) {
	struct poly *ap=a,*bp=b;
	struct poly *result=NULL;
	struct poly *p=NULL; 
	while(ap!=NULL){
		while(bp!=NULL){
			p=(struct poly *)malloc(sizeof (struct poly));
			p->order=bp->order+ap->order;
			p->co=ap->co*bp->co;
			p->next=result;
			result=p;
			bp=bp->next;
		}
		bp=b;
		ap=ap->next;
		}
	return result;
}
//多项式相除函数，由于需要的返回结果有两个所以用结构体doublepoly表示，第一个元素为商，第二个元素为余数 
struct doublepoly *polydivi(struct poly *a, struct poly *b){
	struct poly *ca=polycopy(a),*cb=polycopy(b);
	struct poly *result=NULL,*rest=NULL,*pa=ca,*pb=cb;
	polysimp(&pa);
	polysimp(&pb);
	polysort(&pa);
	polysort(&pb);
		while(pa!=NULL){
			if(pa->order<pb->order)
				break;
			else{
				struct poly *temp=(struct poly *)malloc(sizeof(struct poly)); 
				temp->co=-pa->co/pb->co;
				temp->order=pa->order-pb->order;
				temp->next=NULL;
				struct poly *insp=(struct poly *)malloc(sizeof(struct poly));
				insp->co=-temp->co;
				insp->order=temp->order;
				insp->next=result;
				result=insp;	
				struct poly *stemp=polymulti(temp,pb);
				pa=polyplus(stemp,pa);
				polysimp(&pa);
				polysort(&pa);
			}
		}
	rest=pa;
	struct doublepoly *doubleresult=(doublepoly *)malloc(sizeof(struct doublepoly));
	doubleresult->po1=result;
	doubleresult->po2=rest;
	return doubleresult;
}
//主函数 
int main(){
	struct poly*p1=createlistf();
	printf("输入的多项式如下：");
	polysimp(&p1);
	polysort(&p1);
	polyprint(p1);
	printf("\n");
	struct poly*p2=createlistf();
	printf("输入的多项式如下：");
	polysimp(&p2);
	polysort(&p2);
	polyprint(p2);
	printf("\n");
	struct poly *p3=polyplus(p1,p2);
	printf("这是两个多项式相加的结果：\n");
	polysimp(&p3);
	polysort(&p3);
	polyprint(p3);
	printf("\n");
	struct poly *p4=polymulti(p1,p2);
	printf("这是两个多项式相乘的结果：\n");
	polysimp(&p4);
	polysort(&p4);
	polyprint(p4);
	printf("\n");
	struct doublepoly *p5=polydivi(p1,p2);
	printf("这是两个多项式相除的结果——\n");
	if(p5->po1!=NULL){
		struct poly *p5_one=polycopy(p5->po1);
		polysimp(&p5_one);
		polysort(&p5_one);
		printf("商为：");
		polyprint(p5_one);
	}
	else
		printf("商为:0");
	printf("\n");
	if(p5->po2!=NULL){
		struct poly *p5_two=polycopy(p5->po2);
		printf("余数为: ");
		polysimp(&p5_two);
		polysort(&p5_two);
		polyprint(p5_two);
	}
	else
		printf("余数为：0"); 
	return 0;
}
