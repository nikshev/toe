#include "StdAfx.h"
#include "Math.h"
#include ".\complex.h"


/*
 ����������� ������ complex
*/
complex::complex()
{
 rePart=0;
 imPart=0;
}

/*
 ����������� ������ complex
 float fNum - ����� � ��������� ������ (�������������� ����� ��� �������������� 
              ��� ������ rp ��� ������������� �����.
 float sNum - ����� � ��������� ������ (������ ����� ��� �������������� 
              ��� ���� � �������� ��� ������������� �����.
 bool flag -  ���� ������ ����� (false - ������������� � ����� ���������� � ��������������,
                                 true - ��������������)
*/
complex::complex(double fNum, double sNum, bool flag)
{
 if (flag)
 {
  rePart=fNum;
  imPart=sNum;
 }
 else
 {
  rePart=fNum*cos(sNum*(180/3.142));
  imPart=fNum*sin(sNum*(180/3.142));	  
 }
}

/*
 ����������
*/
complex::~complex(void)
{
}

/*
 ����� getIm() ���������� ������ ����� �����
*/
double complex::getIm()
{
 return imPart;	 
}

/*
 ����� getRe() ���������� ������������ ����� �����
*/
double complex::getRe()
{
 return rePart;
}

/*
 ����� getAbsRe() ���������� ������ ������������ ����� �����
*/
double complex::getAbsRe()
{
 if (rePart>0 || rePart==0)
  return rePart;
 else 
  return -1*rePart;	 
}


/*
 ����������� ������ complex
 float fNum - ����� � ��������� ������ (�������������� ����� ��� �������������� 
              ��� ������ rp ��� ������������� �����.
 float sNum - ����� � ��������� ������ (������ ����� ��� �������������� 
              ��� ���� � �������� ��� ������������� �����.
 bool flag -  ���� ������ ����� (false - ������������� � ����� ���������� � ��������������,
                                 true - ��������������)
*/
void complex::AddComplexNum(double fNum, double sNum, bool flag)
{
 if (flag)
  {
   rePart=fNum;
   imPart=sNum;
  }
  else
  {
   rePart=fNum*cos(sNum*(3.142/180));
   imPart=fNum*sin(sNum*(3.142/180));	  
  }
}

/*
 ������������ �������� ��������
*/
complex complex::operator+(const complex &c) const
{
 double fNum;
 double sNum;
 complex temp;
 fNum=rePart+c.rePart; 
 sNum=imPart+c.imPart; 
 temp.AddComplexNum(fNum,sNum,true);
 return temp;	 
}

/*
 ������������ �������� ���������
*/
complex complex::operator-(const complex &c) const 
{
 double fNum;
 double sNum;
 complex temp;
 fNum=rePart-c.rePart; 
 sNum=imPart-c.imPart; 
 temp.AddComplexNum(fNum,sNum,true);
 return temp;	 	 
}

/*
 ������������ �������� ���������
*/
complex complex::operator*(const complex &c) const 
{
 double fNum,sNum,ar,ai,br,bi;
 complex temp;
 ar=rePart; ai=imPart; br=c.rePart; bi=c.imPart; 
 fNum=((ar*br)-(ai*bi));
 sNum=((ar*bi)+(ai*br)); 
 temp.AddComplexNum(fNum,sNum,true);
 return temp;	 
}

/*
 ������������ �������� �������
*/
complex complex::operator/(const complex &c) const 
{
 double fNum,sNum,ar,ai,br,bi;
 complex temp;
 ar=rePart; ai=imPart; br=c.rePart; bi=c.imPart; 
 fNum=((ar*br)+(ai*bi))/(br*br+bi*bi);
 sNum=((ai*br)-(ar*bi))/(br*br+bi*bi); 
 temp.AddComplexNum(fNum,sNum,true);
 return temp;	 
}


/*
 ������������ �������� ������������
*/

complex* complex::operator=(complex* c)
{
	this->AddComplexNum(c->getRe(),c->getIm(),true);
	return this;	 
}


/*
 ����� complexToString ���������� ��������� 
 ������������� ������������ �����(�������������� �����)�
*/
char* complex::complexToString()
{
 char* Buf;
 if (imPart<0)
  sprintf(Buf,"%5.4f%5.4fi",rePart,imPart);
 else 
  sprintf(Buf,"%5.4f+%5.4fi",rePart,imPart);
 
 return Buf;
}

/*
 ����� getModule() ���������� ������ rp
*/
double complex::getModule()
{
 
 return sqrt(rePart*rePart+imPart*imPart);	 
}

/*
 ����� getArg() ���������� ��������
*/
double complex::getArg()
{
 double ar,bi,arg;
 arg=0;
 ar=rePart; bi=imPart;
 if (ar!=0)
 {
  arg=90*sgn(bi);
  arg=90*(1-sgn(ar))*(sgn(arg+1));
  arg=((180*atan(bi/ar))/3.142+arg);
 }
 return arg;
}

/*
 ����� getSopr() ���������� ����������� ��������
*/
complex complex::getSopr()
{
 complex temp;
 temp.AddComplexNum(rePart,(-1)*imPart,true);
 return temp;
}

/*
 ����� sgn() ���������� ����������� ��������
*/
double complex::sgn(double a)
{
 if (a==0) 
  return 0;
 else if (a>0) 
  return 1;
 else 
  return -1;
}
