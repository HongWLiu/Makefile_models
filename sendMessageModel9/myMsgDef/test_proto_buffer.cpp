#include <iostream>
#include <string.h>
#include "msgDef.pb.h"
using namespace std;

int main()
{
	student st;
	baseInfo* pBaseInfo = st.mutable_base_info();
	pBaseInfo->set_name("fanchenxin");
	pBaseInfo->set_age(27);
	pBaseInfo->set_sex("man");

	st.set_student_id(20120101);

	pBaseInfo = st.add_parents();
	pBaseInfo->set_name("father");
	pBaseInfo->set_age(50);
	pBaseInfo->set_sex("man");

	pBaseInfo = st.add_parents();
	pBaseInfo->set_name("mother");
	pBaseInfo->set_age(48);
	pBaseInfo->set_sex("woman");

	int size = st.ByteSize();
	cout << "size = " << size << endl;
	char* pBuf = new char[size];
	st.SerializeToArray(pBuf, size);  //���л� ��ʽ1

	string str;
	st.SerializeToString(&str);   // ���л� ��ʽ2

	student st1;
	//st1.ParseFromArray(pBuf, size);  //���л� ��ʽ1
	st1.ParseFromArray((void *)str.c_str(), str.size());  //���л� ��ʽ2
	cout << "name: " << st1.base_info().name() << endl;
	cout << "age: " << st1.base_info().age() << endl;
	cout << "sex: " << st1.base_info().sex() << endl;

	cout << "parents number: " << st1.parents_size() << endl;
	for(int i = 0; i < st1.parents_size(); i++){
		cout << "<" << i << ">:" << endl;
		cout << "name: " << st1.parents(i).name() << endl;
		cout << "age: " << st1.parents(i).age() << endl;
		cout << "sex: " << st1.parents(i).sex() << endl;
	}

	free(pBuf);
	pBuf = NULL;
}

//g++ test.cpp msgDef.pb.cc -o test -lprotobuf 
//��Ҫ��װ libprotobuf-dev �� protobuf-compiler