#include <stdio.h>
#include<stdlib.h>

int m, n;

void print(int x[10][10]){
	int i,j;
	for(i=0;i<n;i++){
		printf("\n");
		for(j=0;j<m;j++){
			printf("%d\t",x[i][j]);
		}
	}	
}
//Banker's Algorithm

void accept(int allocation[10][10],int need[10][10],int max[10][10],int available[1][10]){
	
	printf("\n Enter total no. of processes : ");
	scanf("%d",&n);
	printf("\n Enter total no. of resources : ");
	scanf("%d",&m);
	for(int i=0;i<n;i++){
		printf("\n Process %d\n",i+1);
		for(int j=0;j<m;j++){
			printf(" Allocation for resource %c : ",(65+j));
			scanf("%d",&allocation[i][j]);
			
		}
	}
    for(int i=0;i<n;i++){
		printf("\n Process %d\n",i+1);
		for(int j=0;j<m;j++){
    printf(" Maximum for resource %c : ",65+i);
			scanf("%d",&max[i][j]);
        }
    }

	printf("\n Available resources : \n");
	for(int i=0;i<m;i++){
		printf(" Resource %c : ",65+i);
		scanf("%d",&available[0][i]);
	}

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			need[i][j]=max[i][j]-allocation[i][j];

	printf("\n Allocation Matrix");
	print(allocation);
	printf("\n Maximum Requirement Matrix");
	print(max);
	printf("\n Need Matrix");
	print(need);

}

int banker(int allocation[10][10],int need[10][10],int available[1][10]){
	int j,i,a[10];
	j=safety(allocation,need,available,a);
	if(j != 0 ){
		printf("\n\n");
        printf("\n A safety sequence has been detected.\n");
		for(i=0;i<n;i++)
		     printf(" P%d  ",a[i]);
		
		return 1;
	}else{
		printf("\n Deadlock has occured.\n");
		return 0;
	}
}

int safety(int allocation[10][10],int need[10][10],int available[1][10],int a[10]){

	int i,j,k,x=0;
	int P[10],avail[1][10];
	int processFlag=0,flag=0;
	for(i=0;i<n;i++)
		P[i]=0;
	for(i=0;i<m;i++)
		avail[0][i]=available[0][i];

	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			if(P[i] == 0){
				flag=0;
				for(j=0;j<m;j++){
					if(need[i][j] > avail[0][j])
						flag=1;
				}
				if(flag == 0 && P[i] == 0){
					for(j=0;j<m;j++)
					    avail[0][j]+=allocation[i][j];
					P[i]=1;
					processFlag++;
					a[x++]=i;
				}
			}
		}
		if(processFlag == n)
			return 1;
	}
	return 0;
}
void res_request(int allocation[10][10],int need[10][10],int available[10][10],int pid)
{
	int reqmat[1][10];
	int i;
	printf("\n Enter additional request :- \n");
	for(i=0;i<m;i++){
		printf(" Request for resource %c : ",i+65);
		scanf("%d",&reqmat[0][i]);
	}
	
	for(i=0;i<m;i++)
		if(reqmat[0][i] > need[pid][i]){
			printf("\n Error encountered.\n");
			exit(0);
	}

	for(i=0;i<m;i++)
		if(reqmat[0][i] > available[0][i]){
			printf("\n Resources unavailable.\n");
			exit(0);
		}
	
	for(i=0;i<m;i++){
		available[0][i]-=reqmat[0][i];
		allocation[pid][i]+=reqmat[0][i];
		need[pid][i]-=reqmat[0][i];
	}
}


int main(){
	int ret;
	int allocation[10][10], max[10][10], need[10][10], available[1][10];
	int pid,ch;
	accept(allocation,need,max,available);
	ret=banker(allocation,need,available);
	if(ret !=0 ){
		printf("\n Do you want make an additional request ? (1=Yes|0=No)");
		scanf("%d",&ch);
		if(ch == 1){
			printf("\n Enter process no. : ");
			scanf("%d",&pid);
			res_request(allocation,need,available,pid-1);
			ret=banker(allocation,need,available);
			if(ret == 0 )
				exit(0);
		}
	}else
		exit(0);
    
	return 0;
}
