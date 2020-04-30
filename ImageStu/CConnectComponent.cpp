#include "stdafx.h"
#include "CConnectedComponent.h"
#include "change.h"

CConnectedComponent::CConnectedComponent(int * _origin,int _height,int _width)
{
	height=_height;
	width=_width;
	size=height*width;
	L=new int[size];
	tempA=new int[size];
	tempB=new int[size];
	origin=new int[size];
	label=0;
	equ=false;

	for(int i = 0;i<size;i++)
	{
		L[i]=tempA[i]=tempB[i]=0;
		origin[i]=_origin[i];
	}
}

CConnectedComponent::~CConnectedComponent()
{
	delete [] L;
	delete [] tempA;
	delete [] tempB;
}

int CConnectedComponent::calc_start()
{
	for(int i = 0; i < size; i++)
	{
		if(origin[i]==255&&L[i]==0)
		{
			return i;
		}
	}

	return -1;
}

void CConnectedComponent::set_start(int index)
{
	tempA[index]=255;
}

void CConnectedComponent::calc_area()
{
	int count=0;
	while(!equ)
	{
		penzhang_white(tempA,height,width);
		for(int i=0;i < size;i++)
		{
			if(origin[i]==0&&tempA[i]==255)
			{
				tempA[i]=0;
			}

			if(tempB[i]==tempA[i])
			{
				count++;
			}
			tempB[i]=tempA[i];
		}

		if(count==size)
		{
			equ=true;
		}
		else
		{
			count=0;
		}
	}
	label++;
	for(int i=0;i<size;i++)
	{
		if(tempA[i]==255&&L[i]==0)
		{
			L[i]=label*10;
		}
	}
}

bool CConnectedComponent::confirm()
{
	for(int i = 0; i <size;i++)
	{
		if(origin[i]!=tempA[i])
		{
			equ=false;
			return false;
		}
	}
	return true;
}

void CConnectedComponent::return_L(int * result)
{
	for(int i=0;i<size;i++)
	{
		result[i]=L[i];
	}
}