#pragma once
#include "headersSTD.h"
#include "techExcellFuncs.h"



class unitRecord
{
public:
	bool readUnit(XLWorksheet* wks,size_t lineNum);

	void writeUnit(ofstream& f1);
private:
	string type;
	string dictionary;
	string category;
	string clas;
	string voice_type;

	// �������=cavalry; ������=infantry; �������=ship; �������=siege
	void setCategory(string&excellCat);

	//light=˸����, ˸����(�������), �������; 
	//heavy=������(�������), ������; 
	//spearmen=���������(�����), ���������(�������), ���������(������); 
	//missile=����������(�����), ����������(�������), ����������(������)
	void setClas(string&excellClas);
};
class filesGenerator
{
public:
	void startConvertation(string excellPath,string destPath, atomic_bool& generationEnded);
private:
	void convertationThread(string excellPath, string destPath, atomic_bool& generationEnded);
	void writeEDU(const string& destPath);


	vector<unitRecord>units;
};

