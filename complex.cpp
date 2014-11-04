#include "StdAfx.h"
#include "Math.h"
#include ".\complex.h"


/*
 Конструктор класса complex
*/
complex::complex()
{
 rePart=0;
 imPart=0;
}

/*
 Конструктор класса complex
 float fNum - число с плавающей точкой (действительная часть для алгебраической 
              или модуль rp для показательной формы.
 float sNum - число с плавающей точкой (мнимая часть для алгебраической 
              или угол в градусах для показательной формы.
 bool flag -  флаг выбора формы (false - показательная и будет переведена в алгебраическую,
                                 true - алгебраическая)
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
 Деструктор
*/
complex::~complex(void)
{
}

/*
 Метод getIm() возвращает мнимую часть числа
*/
double complex::getIm()
{
 return imPart;	 
}

/*
 Метод getRe() возвращает вещественную часть числа
*/
double complex::getRe()
{
 return rePart;
}

/*
 Метод getAbsRe() возвращает модуль вещественной части числа
*/
double complex::getAbsRe()
{
 if (rePart>0 || rePart==0)
  return rePart;
 else 
  return -1*rePart;	 
}


/*
 Конструктор класса complex
 float fNum - число с плавающей точкой (действительная часть для алгебраической 
              или модуль rp для показательной формы.
 float sNum - число с плавающей точкой (мнимая часть для алгебраической 
              или угол в градусах для показательной формы.
 bool flag -  флаг выбора формы (false - показательная и будет переведена в алгебраическую,
                                 true - алгебраическая)
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
 Перезагрузка операции сложения
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
 Перезагрузка операции вычитания
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
 Перезагрузка операции умножения
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
 Перезагрузка операции деление
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
 Перезагрузка операции присваивания
*/

complex* complex::operator=(complex* c)
{
	this->AddComplexNum(c->getRe(),c->getIm(),true);
	return this;	 
}


/*
 Метод complexToString возвращает строковое 
 представление комплексного числа(алгебраическая форма)ж
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
 Метод getModule() возвращает модуль rp
*/
double complex::getModule()
{
 
 return sqrt(rePart*rePart+imPart*imPart);	 
}

/*
 Метод getArg() возвращает аргумент
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
 Метод getSopr() возвращает сопряженный комплекс
*/
complex complex::getSopr()
{
 complex temp;
 temp.AddComplexNum(rePart,(-1)*imPart,true);
 return temp;
}

/*
 Метод sgn() возвращает сопряженный комплекс
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
