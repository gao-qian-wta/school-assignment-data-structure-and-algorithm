#include <stdio.h>
#include <stdlib.h>
typedef struct PolyNode *Polynomial;
struct PolyNode
{
	int coef;
	int expon;
	Polynomial link;
};

//插入系数和指数(Attach)函数
void Attach(int c, int e, Polynomial *pRear)
{
	Polynomial P;

	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->coef = c;        //  对新结点赋值
	P->expon = e;
	P->link = NULL;
	(*pRear)->link = P;
	*pRear = P;         //修改pRear值
}


//读入多项式函数
Polynomial ReadPoly()
{
	Polynomial P, Rear, t;
	int c, e, N;

	scanf("%d", &N);  //读入系数
	P = (Polynomial)malloc(sizeof(struct PolyNode)); //链表头空结点
	P->link = NULL;
	Rear = P;
	while (N--){
		scanf("%d %d", &c, &e);
		Attach(c, e, &Rear); //将系数和指数插入链表中
	}
	t = P;
	P = P->link;
	free(t); 
	return P;
}

int compare(int e1, int e2)
{
    if(e1 > e2) return 1;
    else if(e1 < e2) return -1;
    else return 0;
}
//多项式相加函数
Polynomial Sum(Polynomial P1, Polynomial P2)
{
	Polynomial  P, Rear, temp;
	
	int sum;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	Rear = P;
	while (P1 && P2){
		switch(compare(P1->expon,P2->expon)){
            case 1:
                Attach(P1->coef,P1->expon,&Rear);
                P1=P1->link;
                break;
            case -1:
                Attach(P2->coef,P2->expon,&Rear);
                P2=P2->link;
                break;
            case 0:
                sum=P1->coef+P2->coef;
                if(sum) Attach(sum,P1->expon,&Rear);
                P1=P1->link;
                P2=P2->link;
                break;
        }
	}
	while (P1){
		Attach(P1->coef,P1->expon,&Rear);
        P1=P1->link;
	}
	while (P2){
		Attach(P2->coef,P2->expon,&Rear);
        P2=P2->link;
	}
	Rear->link = NULL;
	temp = P;
	P = P->link;
	free(temp);
	return P;
}

//多项式相乘函数
Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, Rear, t1, t2, t;
	int c, e;
	//两者相乘，其中一者为空即可返回NULL
	if (!P1 || !P2) return NULL;
	
	t1 = P1; t2 = P2;
	P  = (Polynomial)malloc(sizeof(struct PolyNode)); 
	P->link = NULL;
	Rear = P;
	
	while (t2){     //先使用P1的第一项乘P2,得到P
		Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
		t2 = t2->link;
	}
	t1 = t1->link;
	//两重循环 t1每一项乘t2每一项
	while (t1){
		t2 = P2; Rear = P;
		while (t2){
			e = t1->expon + t2->expon;
			c = t1->coef * t2->coef;
			while (Rear->link && Rear->link->expon > e)
				Rear = Rear->link; //当要插入的数的指数大于rear的指数时，向后移位
			if (Rear->link && Rear->link->expon == e){
				if (Rear->link->coef + c)  //当两者指数相等时，判断系数相加是否为0
					Rear->link->coef += c;
				else{
					t = Rear->link;
					Rear->link = t->link;
					free(t);
				}
			}
			else {
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = Rear->link;
				Rear->link = t;
				Rear = Rear->link;
			}
			t2 = t2->link;
		}
		t1 = t1->link;
	}
	t2 = P;
	P = P->link; free(t2);

	return P;
}

void PrintPoly(Polynomial P)
{	/* 输出多项式 */
	int flag = 0;

	if (!P){
		printf("0 0\n");
		return;
	}

	while (P){
		if (!flag)
			flag = 1;
		else
			printf(" ");
		printf("%d %d", P->coef, P->expon);
		P = P->link;
	}
	printf("\n");
}


int main()
{
	Polynomial P1, P2, PP, PS;
	P1 = ReadPoly();
	P2 = ReadPoly();
	PP = Mult(P1, P2);
	PrintPoly(PP);
	PS = Sum(P1, P2);
	PrintPoly(PS);

	return 0;
}




