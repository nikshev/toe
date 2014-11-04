#pragma once

class complex
{
 private:
  double imPart; //Мнимая часть
  double rePart; //Действительная часть
 public:
	complex();   
	complex(double fNum, double sNum, bool flag);
    double getIm();
	double getRe();
	double getAbsRe();
	double getModule();
	double getArg();
	double sgn(double a);
	complex getSopr();
	void AddComplexNum(double fNum, double sNum, bool flag);
	char* complexToString();
	virtual ~complex(void);
	complex operator+(const complex &c) const;
	complex operator-(const complex &c) const;
	complex operator*(const complex &c) const;
	complex operator/(const complex &c) const;
	complex* operator=(complex *c);

};
