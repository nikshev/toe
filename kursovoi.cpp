// kursovoi.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "complex.h"
#include <iostream>
#include <fstream>
using namespace std;

struct Ishodnie{
 double R1; //�������� R1
 double R2; //�������� R2
 double C1; //����������� C1
 double C3; //����������� C1
 double L2; //������������� L2
 double L3; //������������� L2 
 double E2; //��� E2
 double E3; //��� E2
 double F2; //���� �2
 double F3; //���� �3
 double f;  //�������
};

struct Results{
 double Xc1; //������������� ����������� �������� Xc1
 double Xc3; //������������� ����������� �������� Xc3
 double XL2; //������������� ����������� �������� XL1
 double XL3; //������������� ����������� �������� XL3
 double PW1; //��������� ��������� 1
 double PW2; //��������� ��������� 2
 double Pist; //�������� �������� ���������
 double Qist; //���������� �������� ���������
 double Pnagr; //�������� �������� ��������
 double Qnagr; //���������� �������� ��������
 complex Z1; //����������� ������������� Z1
 complex Z2; //����������� ������������� Z2
 complex Z3; //����������� ������������� Z3
 complex E2; //����������� ��� E2
 complex E3; //����������� ��� E3
 complex Ugh; //���������� ����� ������� G � H
 complex I1; //��� � ������ ����� 
 complex I2; //��� �� ������ �����
 complex I3; //��� � ������� ����� 
};

//��������� �������
void zapolnenie_dannih(char *file, Ishodnie* data);
void raschet_schem(Ishodnie* data, Results* res);
void output_result_to_screen(Results* res);
void output_result_to_file(Results* res);

int _tmain(int argc, _TCHAR* argv[])
{
	Ishodnie ishod_data;
    Results  results;
	zapolnenie_dannih("C:\\data.txt",&ishod_data);
    raschet_schem(&ishod_data, &results);
	output_result_to_file(&results);
	output_result_to_screen(&results);
	return 0;
}

/*
 ������� zapolnenie_dannih ��������� ��������� Ishodnie 
 �� �����
 ���������:
 char *file - ���� � ��������� �������
 Ishodnie* data - ��������� �� ��������� �������� ������
*/
void zapolnenie_dannih(char *file, Ishodnie* data)
{
 char Buf[30];
 char tempChar;
 int  BufIndex;
 int  StringIndex;
 FILE *in;
 if ((in=fopen(file,"rt"))!=NULL)
 {
  StringIndex=0;
  while((!feof(in)))
  {
   BufIndex=0;
   tempChar=fgetc(in);
   if (tempChar!=-1)
   {
   while (tempChar!='\n') 
    {
     Buf[BufIndex]=tempChar; 
	 BufIndex++;
	 tempChar=fgetc(in);
    }
	Buf[BufIndex]=0;
	switch (StringIndex){
     case 0: data->C1=atof(Buf); 
		     break;
	 case 1: data->C3=atof(Buf);
			 break;
	 case 2: data->E2=atof(Buf);
			 break;
	 case 3: data->E3=atof(Buf);
			 break;
	 case 4: data->L2=atof(Buf);
			 break;
	 case 5: data->L3=atof(Buf);
			 break;
	 case 6: data->R1=atof(Buf);
			 break;
	 case 7: data->R2=atof(Buf);
			 break;
	 case 8: data->F2=atof(Buf);
			 break;
	 case 9: data->F3=atof(Buf);
			 break;
	 case 10: data->f=atof(Buf);
			 break;
	 default : StringIndex=-1;
		       break; 
	}
	StringIndex++;
   }
  }
  fclose(in);
 }
 else 
  cerr<<"Error reading file c:\\data.txt"<<endl;
}

/*
 ������� raschet_schem ������������ ������ �����
 ���������:
 Ishodnie* data - ��������� �� ��������� �������� ������
 Results* res   - ��������� �� ��������� �����������
*/
void raschet_schem(Ishodnie* data, Results* res)
{
  complex temp; //��������� ����������
  complex tempzn; //��������� ����������
   //1)����������� ������������� ���������� ��������� ����
	res->Xc1=1/(2*3.142*data->f*data->C1);  
	res->Xc3=1/(2*3.142*data->f*data->C3);  
	res->XL2=(2*3.142*data->f*data->L2);  
	res->XL3=(2*3.142*data->f*data->L3);  
 //2)���������� ����������� ������������� ������
	res->Z1.AddComplexNum(data->R1,-1*res->Xc1,true);
    res->Z2.AddComplexNum(data->R2,res->XL2,true);
	res->Z3.AddComplexNum(0,res->XL3-res->Xc3,true);
 //3)���������� ���������� ����� ������� G � H
    res->E2.AddComplexNum(data->E2,data->F2,false);
	res->E3.AddComplexNum(data->E3,data->F3,false);
	temp.AddComplexNum(1,0,true);
	res->Ugh=((res->E2/res->Z2)+(res->E3/res->Z3))/
		     ((temp/res->Z1)+(temp/res->Z2)+(temp/res->Z3));
 //4) ����������� ����� � ������
    temp.AddComplexNum(-1,0,true);
	res->I1 =(temp*res->Ugh)/res->Z1;
	res->I2 =(res->E2-res->Ugh)/res->Z2;
	res->I3 =(res->E3-res->Ugh)/res->Z3;
 //5) ���������� ��������� ����������
	temp=res->Ugh*res->I1.getSopr();
	res->PW1=temp.getAbsRe();  
	temp.AddComplexNum(-1,0,true);
	res->PW2=((res->Ugh-res->E2)*(temp*res->I3.getSopr())).getAbsRe();  
 //6) �������� ������� ���������
	res->Qist=((res->E2*res->I2.getSopr())+(res->E3*res->I3.getSopr())).getIm();
	res->Pist=((res->E2*res->I2.getSopr())+(res->E3*res->I3.getSopr())).getRe();
	res->Pnagr=(res->I1.getModule()*res->I1.getModule()*data->R1)+
               (res->I2.getModule()*res->I2.getModule()*data->R2);
	res->Qnagr=-1*(res->I1.getModule()*res->I1.getModule()*res->Xc1)+
                  (res->I2.getModule()*res->I2.getModule()*res->XL2)+
                  (res->I3.getModule()*res->I3.getModule()*(res->XL3-res->Xc3));
	if (res->Qist<0) 
	{
	 res->Qist*=-1;
	 res->Qnagr*=-1;
	}
}

/*
 ������� output_result_to_screen ������� �� ����� ����������
 ���������:
 Results* res   - ��������� �� ��������� �����������
*/
void output_result_to_screen(Results* res)
{
 cout<<"Step 1:"<<endl;
 cout<<"Xc1="<<res->Xc1<<"; Xc3="<<res->Xc3<<"; XL2="<<res->XL2
	 <<"; XL3="<<res->XL3<<"; "<<endl;
 cout<<"Step 2:"<<endl;
 cout<<"Z1="<<res->Z1.complexToString()<<"; Z2="<<res->Z2.complexToString()
 	 <<"; Z3="<<res->Z3.complexToString()<<"; "<<endl;
 cout<<"Step 3:"<<endl;
 cout<<"Ugh="<<res->Ugh.complexToString()<<endl;
 cout<<"Step 4:"<<endl;
 cout<<"I1="<<res->I1.complexToString()<<"; I2="<<res->I2.complexToString()
	 <<"; I3="<<res->I3.complexToString()<<"; "<<endl;
 cout<<"Step 5:"<<endl;
 cout<<"W1="<<res->PW1<<"; W2="<<res->PW2<<endl;
 cout<<"Step 6:"<<endl;
 cout<<"Pist="<<res->Pist<<" == Pnagr="<<res->Pnagr<<endl;
 cout<<"Qist="<<res->Qist<<" == Qnagr="<<res->Qnagr<<endl;
 cout<<"Press any key to continue....."<<endl;
 getch();
}

/*
 ������� output_result_to_screen ������� � ���� C:\rezult.txt
 ���������:
 Results* res   - ��������� �� ��������� �����������
*/
void output_result_to_file(Results* res)
{
 ofstream fout("C:\\Result.txt");
 fout<<"1)����������� ������������� ���������� ���������"<<endl;
 fout<<"Xc1="<<res->Xc1<<"; Xc3="<<res->Xc3<<"; XL2="<<res->XL2
	 <<"; XL3="<<res->XL3<<"; "<<endl;
 fout<<"2)���������� ����������� ������������� ������"<<endl;
 fout<<"Z1="<<res->Z1.complexToString()<<"; Z2="<<res->Z2.complexToString()
	 <<"; Z3="<<res->Z3.complexToString()<<"; "<<endl;
 fout<<"3)���������� ���������� ����� ������� G � H"<<endl;
 fout<<"Ugh="<<res->Ugh.complexToString()<<endl;
 fout<<"4) ����������� ����� � ������"<<endl;
 fout<<"I1="<<res->I1.complexToString()<<"; I2="<<res->I2.complexToString()
	 <<"; I3="<<res->I3.complexToString()<<"; "<<endl;
 fout<<"5)����������� ��������� ����������"<<endl;
 fout<<"W1="<<res->PW1<<"; W2="<<res->PW2<<endl;
 fout<<"6)������ ���������"<<endl;
 fout<<"Pist="<<res->Pist<<" == Pnagr="<<res->Pnagr<<endl;
 fout<<"Qist="<<res->Qist<<" == Qnagr="<<res->Qnagr<<endl;
 fout.close();
}

