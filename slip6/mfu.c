#include<stdio.h>
#include<stdlib.h>
int pages[30],frames[5],np,nf,pf=0;
void accept();
int search();
int getMFU();
void main()
{
	int i,j;
	int x;//frame no
	accept();
	for(i=0;i<np;i++)
	{
		if(search(pages[i])==1)
		{
		
			x=getMFU(i);
			frames[x]=pages[i];
			pf++;
		}
		for(j=0;j<nf;j++)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");			
	}
	printf("\n\ntotal no. of page faults:%d\t",pf);
}
int getMFU(int pos)
{
	int freq[10]={0},maxfreq,maxcount,i,j,p;
	int count[10]={0},c=1;	
	for(i=0;i<nf;i++)
	{
		if(frames[i]==-1)
		{
			return i;
		}
	}
	for(i=pos-1;i>=0;i--)
	{
		for(j=0;j<nf;j++)
		{
			if(pages[i]==frames[j])
			{
				freq[j]++;
			}
		}
	}
	maxfreq=freq[0];
	p=0;
	for(i=1;i<nf;i++)
	{
		if(maxfreq<freq[i])
		{
			maxfreq=freq[i];
			p=i;
		}
	}
	maxcount=0;
	for(i=0;i<nf;i++)
	{
		if(freq[i]==maxfreq)
		{
			maxcount++;
		}
	}
	if(maxcount==1)
	{
		return p;
	}
	else
	{
		for(i=pos-1;i>=0;i--)
		{
			for(j=0;j<nf;j++)
			{
				if(pages[i]==frames[j] && freq[j]==maxfreq && count[j]==0)
				{
					count[j]=c;
					c++;
					break;
				}
			}
		}
		p=0;
		int max=count[0];
		for(i=1;i<nf;i++)
		{
			if(max<count[i])
			{
				max=count[i];
				p=i;
			}
		}
		return p;
	}
}
		
int search(int p)
{
	int i;
	for(i=0;i<nf;i++)
	{
		if(frames[i]==p)
		{
			return 0;
		}
	}
	return 1;	
	
}
void accept()
{
	int i;
	printf("\nEnter the Total No. of pages:");
	scanf("%d",&np);
	for(i=0;i<np;i++)
	{
		printf("\nEnter Page Number:");
		scanf("%d",&pages[i]);
	}
	printf("\nEnter the Minimum No. of frames:");
        scanf("%d",&nf);
	for(i=0;i<nf;i++)
        {
         	frames[i]=-1;       
        }
}
