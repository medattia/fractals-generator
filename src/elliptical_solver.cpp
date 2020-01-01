/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* %%%  Résolution du PB Elliptique 1D par Différences Finies:    %%% */
/* %%%      -(K(x)u')' + p(x) u = f(x)  dans [0,L]                %%% */
/* %%%                     u(0) = a    (Dirichlet)                %%% */
/* %%%                     u(L) = b    (Dirichlet)                %%% */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* %%%  F.Lefèvre, dernière modification: 09/11/2014              %%% */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

/* ================================================================== */
/* ===               INCLUSION DES LIBRAIRIES DU C                === */
/* ================================================================== */
#include <math.h>   /* sqrt()...         */
#include <stdio.h>  /* printf()...       */
#include <stdlib.h> /* malloc()...       */
#include <stddef.h> /* NULL...           */
#include <string.h> /* atof,memcpy...    */
#include <time.h>   /* clock()...        */
#include <limits.h> /* bornes limites... */
#include <assert.h> /* assert()...       */

/* ================================================================== */
/* ===                  DEFINITION DES MACROS                     === */
/* ================================================================== */
#define min(a,b) ( (a)<(b) ? (a) : (b) )
#define max(a,b) ( (a)>(b) ? (a) : (b) )
#define CARRE(x) ( (x)*(x) )
#define  CUBE(x) ( (x)*(x)*(x) )
#define   ABS(x) ( (x)>=0 ? (x) : -(x) )
#define  SIGN(x) ( (x)>0 ? (+1) : ( (x)<0 ? (-1) : (0) ) )

#define Inf  (1.0/0.0)
#define NaN  (0.0/0.0)
#define PI      3.141592653589793e+000
#define CAS_PB  1

/* ================================================================== */
/* ===                  DECLARATION DES STRUCTURES                === */
/* ================================================================== */

typedef struct {  
    int     length; /* nombre de coeff.  du vecteur */
    double *tab;    /* les coefficients  du vecteur */
} Vecteur;

typedef struct {
		int dim; 				/*dimension de la matrice */
		char type;			/*type de la matrice*/
		Vecteur *lA;		/*coeff sous-diagonaux*/
		Vecteur *dA;		/*coeff diagonaux*/
		Vecteur *uA;		/*coeff sur-diagonaux*/
} TriDiag;

/* ================================================================== */
/* ===                  DECLARATION DES ENTETES                   === */
/* ================================================================== */

double *alloc_dtab_1d(int n);
double *free_dtab_1d(double *v);
Vecteur *alloc_Vecteur(int n);
Vecteur *free_Vecteur(Vecteur *V);
void   disp_Vecteur(char *message, Vecteur *V);
TriDiag *alloc_TriDiag(int n);
TriDiag *free_TriDiag(TriDiag *T);
double dot(double *v, double *w, int d, int f);
double NORM    (Vecteur *x);
double NORM_INF(Vecteur *x);
void Solveur_LU_TriDiag(TriDiag *A, Vecteur *b, Vecteur *x);
void Solveur_TriDiag_Chol(TriDiag *A, Vecteur *b, Vecteur *x);
double fct_kappa(double x);
double fct_f    (double x);
double fct_p    (double x);
double fct_u    (double x);

/* ================================================================== */
/* ===                   DEFINITION DES FONCTIONS                 === */
/* ================================================================== */
/* ===================== */
/* allocation dynamique: */
/* ===================== */
/* ------------------------------------------------------------------------- */
double *alloc_dtab_1d(int n)
{ assert( n>0 ); 
  { double *v=NULL;
  
    v = (double *) calloc (n, sizeof(double));
    if (v == NULL) {
      printf("plus de place pour alloc_dtab_1d()\n"); exit(1);
    } 
    v = v-1;
  
    return v;
  }
}

double *free_dtab_1d(double *v)
{ if (v!=NULL) free(v+1);
  return NULL;
}

Vecteur *alloc_Vecteur(int n)
{ assert( n>0 ); 
  { Vecteur *V=NULL;
  
    V = (Vecteur *) malloc(sizeof(Vecteur));
    if (V == NULL) {
      printf("plus de place pour alloc_Vecteur()\n"); exit(1);
    };
    V->length = n;
    V->tab    = alloc_dtab_1d(n);
    return V;
  }
}

Vecteur *free_Vecteur(Vecteur *V)
{ if (V!=NULL) {
    free_dtab_1d(V->tab);
    free(V);
  }
  return NULL;
}

TriDiag *alloc_TriDiag(int n)
{ assert( n>0 ); 
  { TriDiag *T=NULL;
    T = (TriDiag *) malloc(sizeof(TriDiag));
    if (T == NULL) {
      printf("plus de place pour alloc_TriDiag()\n"); exit(1);
    };
    T->dim = n;
    T->uA    = alloc_Vecteur(n);
    T->dA    = alloc_Vecteur(n);
    T->lA    = alloc_Vecteur(n);
    return T;
  }
}

TriDiag *free_TriDiag(TriDiag *T)
{ if (T!=NULL) {
    free_Vecteur(T->lA);
    free_Vecteur(T->dA);
    free_Vecteur(T->uA);
    free(T);
  }
  return NULL;
}
/* ===================== */
/* ====     disp:   ==== */
/* ===================== */
/* ------------------------------------------------------------------------- */
void disp_Vecteur(char *message, Vecteur *V)
{ assert(V!=NULL); 
  { int i;

    printf("%s\n",message);
    for (i=0; i<=V->length-1; i++) printf("%24.16e\n",V->tab[i]);
    
    printf("\n");
  }
}
/* ============ */
/* === BLAS === */
/* ============ */
/* -------------------------- BLAS de bas niveau --------------------------- */
double dot(double *v, double *w, int d, int f)  
/* v(d:f)'*w(d:f) */
{ assert(v!=NULL); assert(w!=NULL); 
  { int    i; 
    double s=0.0;
  
    for (i=d; i<=f; i++) s += v[i]*w[i];
    
    return s;
  }
}
/* -------------------------- BLAS de haut niveau -------------------------- */
double NORM(Vecteur *x)  
/* ||x||_2 = sqrt( (x|x) ) */
{ assert(x!=NULL); 
  { return sqrt(dot(x->tab, x->tab, 1, x->length));
  }
}

double NORM_INF(Vecteur *x)  
/* ||x||_inf = max_{1<=i<=n} |x_i| */
{ assert(x!=NULL); 
  { int i; 
    double nx=0.0; 
  
    for (i=1; i<=x->length; i++) nx = max(nx, fabs(x->tab[i]));
      
    return nx;
  }
}
/* ====================== */
/* ====   Solveur:   ==== */
/* ====================== */
/* ------------------------------------------------------------------------- */
/* -----------------------------Solveur LU---------------------------------- */
/* ------------------------------------------------------------------------- */
void Solveur_LU_TriDiag(TriDiag *A, Vecteur *b, Vecteur *x)
{
/* --------------Variables locales--------------------------------- */	
 	int i,n; 											/*compteur i et dimension de la matrice n*/
	Vecteur *uU,*dU,*lL,*dL,*y;		/*vecteurs pour la décomposition LU*/
/* --------------Allocation des tableaux locaux--------------------------------- */	
	n=A->dim;											/*n=dim(A)*/
	dU=alloc_Vecteur(n);					/*allocation du vecteur diagonale de U*/
	uU=alloc_Vecteur(n-1);				/*allocation du vecteur sur-diagonale de U*/
	dL=alloc_Vecteur(n);					/*allocation du vecteur diagonale de L*/
	lL=alloc_Vecteur(n-1);				/*allocation du vecteur sous-diagonale de L*/
	y=alloc_Vecteur(n);						/*allocation du vecteur y*/
/* --------------Initialisation des tableaux--------------------------------- */	
	for (i=1;i<n;i++) 
	{	dL->tab[i]=1; 							/*les éléments diagonaux de L prennent 1*/
		lL->tab[i]=0;								/*initialisation de la sous-diagonale de L*/
		dU->tab[i]=0;								/*initialisation de la diagonale de U*/
		uU->tab[i]=0;								/*initialisation de la sur-diagonale de U*/
	};
	dU->tab[n]=0;																									/*U(n,n)=0*/
	dL->tab[n]=1;																									/*L(n,n)=1*/
/* --------------Factorisation LU--------------------------------- */		
	dU->tab[1]=A->dA->tab[1];																			/*U(1,1)=A(1,1)*/
	for(i=2;i<=n;i++)
	{	uU->tab[i-1]=(A->uA->tab[i-1]);															/*U(i-1,i)=A(i,i-1)*/
		lL->tab[i-1]=(A->lA->tab[i-1])/(dU->tab[i-1]);							/*L(i,i-1)=A(i,i-1)/U(i-1,i-1)*/
		dU->tab[i]=(A->dA->tab[i])-(lL->tab[i-1])*(uU->tab[i-1]);		/*U(i,i)=A(i,i)-L(i,i-1)*U(i-1,i)*/
	};

/* --------------Descente--------------------------------- */			
	y->tab[1]=b->tab[1];    																				/*y(1)=b(1)*/
	for(i=2;i<=n;i++)    
	{ y->tab[i]=((b->tab[i])-((lL->tab[i-1])*(y->tab[i-1])));    		/*y(i)=b(i)-L(i,i-1)*y(i-1)*/
		} ;
/* --------------Remontée--------------------------------- */			             
	x->tab[n]=((y->tab[n])/(dU->tab[n]));																/*x(n)=y(n)/U(n,n)*/  	       
	for(i=n-1;i>0;i--)   
	{	x->tab[i]=((y->tab[i])-(uU->tab[i])*(x->tab[i+1]))/(dU->tab[i]);	/*x(i)=(y(i)-U(i,i+1)*x(i+1))/U(i,i)*/
	};
/* --------------Désallocation des tableaux locaux--------------------------------- */	
	free_Vecteur(dU);
	free_Vecteur(uU);
	free_Vecteur(y);
	free_Vecteur(dL);
	free_Vecteur(lL);
}
/* ------------------------------------------------------------------------- */
/* -------------------------Solveur Choleski-------------------------------- */
/* ------------------------------------------------------------------------- */
void Solveur_Chol_TriDiag(TriDiag *A, Vecteur *b, Vecteur *x)
{ 
/* --------------Variables locales--------------------------------- */	
	int i,n;  			/*compteur i et dimension de la matrice n*/
	Vecteur *lC,*dC,*y;		/*vecteurs pour la décomposition Choleski*/
/* --------------Allocation des tableaux locaux--------------------------------- */	
	n=A->dim;					/*n=dim(A)*/
	dC=alloc_Vecteur(n);			/*allocation du vecteur diagonale de C*/
	lC=alloc_Vecteur(n-1);		/*allocation du vecteur sous-diagonale de C*/
	y=alloc_Vecteur(n);				/*allocation du vecteur y*/
/* --------------Initialisation des tableaux--------------------------------- */	
	for (i=1;i<=n;i++) 
	{	dC->tab[i]=0;						/*initialisation de la diagonale de C*/
		lC->tab[i]=0;						/*initialisation de la sous-diagonale de C*/
	};
/* --------------Factorisation de Choleski--------------------------------- */			
	dC->tab[1]=sqrt(A->dA->tab[1]);						/*C(1,1)=sqrt(A(1,1))*/
	for(i=2;i<=n;i++)
	{ lC->tab[i-1]=(A->lA->tab[i-1])/(dC->tab[i-1]);				/*C(i,i-1)=A(i,i-1)/C(i-1)*/
		dC->tab[i]=sqrt((A->dA->tab[i])-CARRE(lC->tab[i-1]));	/*C(i,i)=sqrt(A(i,i)-sqr(C(i,i-1)))*/		
	};
/* --------------Descente--------------------------------- */				
	y->tab[1]=(b->tab[1])/(dC->tab[1]);      		/*y(1)=b(1)/C(1,1)*/  
	for(i=2;i<=n;i++)    
	{ y->tab[i]=(b->tab[i]-(lC->tab[i-1])*(y->tab[i-1]))/dC->tab[i];  /*y(i)=(b(i)-L(i,i-1)*y(i-1))/C(i,i)*/
	};      
/* --------------Remontée--------------------------------- */				            
	x->tab[n]=((y->tab[n])/(dC->tab[n]));     	/*x(n)=y(n)/C(n,n)*/     	       
	for(i=n-1;i>0;i--)   
	{ x->tab[i]=((y->tab[i])-(lC->tab[i])*(x->tab[i+1]))/(dC->tab[i]);/*x(i)=(y(i)-C(i,i+1)*x(i+1))/C(i,i)*/
	};
/* --------------Désallocation des tableaux locaux--------------------------------- */	
	free_Vecteur(dC);
	free_Vecteur(lC);
	free_Vecteur(y);
}
/* ============================ */
/* ====   Pb Elliptique:   ==== */
/* ============================ */
/* ------------------------------------------------------------------------- */
double fct_u(double x)
{ double z;
	#if 	( CAS_PB==1 )
  	z = sin(x);
	#elif ( CAS_PB==2 )
  	double e;
  	e = fct_kappa(0.0);
  	z = exp(2/sqrt(e))/(exp(2/sqrt(e))-1)*exp(-x/sqrt(e)) + 1/(1-exp(2/sqrt(e)))*exp(x/sqrt(e));
	#elif ( CAS_PB==3 )
	  z = CARRE(x)*(1-x);
	#endif
  return z;
}

double fct_kappa(double x)
{ double z;
  #if   ( CAS_PB==1 )
  	z = 1;
	#elif ( CAS_PB==2 )
  	z = 0.00005;
	#elif ( CAS_PB==3 )
  	z = 1;
	#endif                 
  return z;
}

double fct_f(double x)
{ double z;
	#if   ( CAS_PB==1 )
	  z = 2*sin(x);
	#elif ( CAS_PB==2 )
	  z = 0.0;
	#elif ( CAS_PB==3 )
	  z = 6*x-2;
	#endif         
  return z;
}

double fct_p(double x)
{ double z;
	#if   ( CAS_PB==1 )
  	z = 1;
	#elif ( CAS_PB==2 )
  	z = 1;
	#elif ( CAS_PB==3 )
  	z = 0;
	#endif           
  return z;
}
/* ---------------------------------------------------------------------------------- */
/* -------------------------Schéma de différences finies----------------------------- */
/* ---------------------------------------------------------------------------------- */
void Schema(TriDiag *A, Vecteur *f, double h, double alpha, double beta)
{ 
/* --------------Déclaration des variables locales--------------------------------- */	
	int i;   			/*compteur i*/
	double x;			/*variable position*/
/* --------------Calcul des éléments de A--------------------------------- */	
	for(i=1;i<=A->dim;i++)
	{	x=i*h;
		A->uA->tab[i]=-fct_kappa(x+h/2)/CARRE(h);															/*sur-diagonale de A*/
		A->dA->tab[i]=fct_p(x)+(fct_kappa(x-h/2)+fct_kappa(x+h/2))/CARRE(h);	/*diagonale de A*/
		A->lA->tab[i]=-fct_kappa(x+h/2)/CARRE(h);															/*sous-diagonale de A*/
	};
/* --------------Calcul des éléments de F--------------------------------- */	
	f->tab[1]=fct_f(h)+(fct_kappa(h/2)*alpha/CARRE(h));	/*f(1)*/	
	for(i=2;i<=(f->length-1);i++)
	{	x=i*h;
		f->tab[i]=fct_f(x);																/*f(i) pour i=2,..,N-2*/
	};
	f->tab[f->length]=fct_f((f->length)*h)+(fct_kappa((f->length+1)*h-h/2)*beta/CARRE(h));	/*f(N-1)*/
}
/* ------------------------------------------------------------------------- */
/* -------------------------Programme principal----------------------------- */
/* ------------------------------------------------------------------------- */
int main(int narg, char **arg)
{	
/* --------------Déclaration des variables globales--------------------------------- */		
	int N,i;																/* dimension du maillage et compteur*/
	double L,h,x,p;													/* dimension du domaine, pas du maillage, variable position et ordre*/
	double alpha,beta;											/*conditions de aux limites de Dirichlet*/
	Vecteur *f;															/*Vecteur f (second membre)*/
	TriDiag *A;															/*Matrice A=M+K/h^2*/
	Vecteur *u,*v;													/*vecteurs solution discrètisée et solution exacte*/
	Vecteur *diff,*diff2;										/*vecteurs différence entre solution discrètisée et solution exacte à h et h/2*/
/* --------------Choix de la dimension du maillage------------------------------------------ */		
	printf("Dimension du maillage N?");
	scanf("\n %d",&N);
/* --------------Allocation des matrices -------------------------------------------------------- */		
	A=alloc_TriDiag(N-1);
	f=alloc_Vecteur(N-1);
	u=alloc_Vecteur(N-1);
	v=alloc_Vecteur(N-1);
	diff=alloc_Vecteur(N+1);
	diff2=alloc_Vecteur(N+1);
/* --------------Taille du domaine et les conditions aux limites selon le cas ------------------ */		
	#if   ( CAS_PB==1 )
		alpha = 0;
	  beta  = -1;
	  L 		= 3*PI/2;
	#elif ( CAS_PB==2 )
	  alpha	= 1;
	  beta	= 0;
	  L 		= 1;
	#elif ( CAS_PB==3 )
	  alpha	= 0;
	  beta	= 0;
	  L 		= 1;
	#endif
	h = L/(double)N;
/*--------------Construction du schéma numérique pour un pas h------------------- */	
	Schema(A,f,h,alpha,beta);
/* --------------Appel des fonctions de factorisation---------------------------- */	
	Solveur_LU_TriDiag(A,f,u);	
/* --------------Calcul de la Norme infinie de ||v-v^h||------------------------- */	
	for(i=1;i<=N-1;i++)
	{	x=i*h;
		v->tab[i]=fct_u(x);
		diff->tab[i]=v->tab[i]-u->tab[i];							/*diff(i)=v(i)-v^h(i) */	
	};
		diff->tab[N]=fct_u(0)-alpha;									/*v(0)-v^h(0) est stockée à diff[N]*/	
		diff->tab[N+1]=fct_u(L)-beta;									/*v(N)-v^h(N) est stockée à diff[N+1]*/	
/*--------------Construction du schéma numérique pour un pas h/2----------------- */	
	Schema(A,f,h/2,alpha,beta);
/* --------------Appel des fonctions de factorisation---------------------------- */	
	Solveur_LU_TriDiag(A,f,u);
/* --------------Calcul de la Norme infinie de ||v-v^(h/2)||--------------------- */	
	for(i=1;i<=N-1;i++)
	{	x=i*h/2;
		v->tab[i]=fct_u(x);
		diff2->tab[i]=v->tab[i]-u->tab[i];						/*diff2(i)=v(i)-v^h(i) */	
	};	
	diff2->tab[N]=fct_u(0)-alpha;										/*v(0)-v^h(0) est stockée à diff2[N]*/	
	diff2->tab[N+1]=fct_u(L)-beta;									/*v(N)-v^h(N) est stockée à diff2[N+1]*/
/* --------------Calcul de l'ordre p--------------------------------------------- */	
	p=(1/log(2))*log(NORM_INF(diff)/NORM_INF(diff2));
/* --------------Affichage des résultats--------------------------------------------- */	
	printf("| Maillage N |   Pas h   | Norme infinie ||v-v^h|| |    Ordre p   |\n");
	printf("|============|===========|=========================|==============|\n");
	printf("|    %d      | %f  |  	%f	   |  %f  |\n",N,h,NORM_INF(diff),p);
	printf("|    %d      | %f  |  	%f	   |  %f  |\n",N,h/2,NORM_INF(diff2),p);
/* --------------Désallocation des tableaux ------------------------------------------- */	
	free_TriDiag(A);
	free_Vecteur(f);
	free_Vecteur(u);
	free_Vecteur(v);
	free_Vecteur(diff);
	free_Vecteur(diff2);
  return EXIT_SUCCESS;
}
