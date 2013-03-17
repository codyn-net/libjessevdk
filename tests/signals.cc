#include <iostream>
#include <jessevdk/base/signals/signal.hh>

using namespace std;
using namespace jessevdk::base::signals;

struct A
{
	int b;

	A() : b(0) {};

	virtual ~A() {};
};

struct B : public A
{

};

bool cbb1(A args) { cout << "A object: " << args.b << endl; return false; }
bool cbb2(A &args) { cout << "A ref: " << args.b << endl; return false; }
bool cbb3(A const &args) { cout << "A const ref: " << args.b << endl; return false; }

void cbv1(A args) { cout << "A object: " << args.b << endl; }
void cbv2(A &args) { cout << "A ref: " << args.b << endl; }
void cbv3(A const &args) { cout << "A const ref: " << args.b << endl; }

bool bcbb1(B args) { cout << "B object: " << args.b << endl; return false; }
bool bcbb2(B &args) { cout << "B ref: " << args.b << endl; return false; }
bool bcbb3(B const &args) { cout << "B const ref: " << args.b << endl; return false; }

void bcbv1(B args) { cout << "B object: " << args.b << endl; }
void bcbv2(B &args) { cout << "B ref: " << args.b << endl; }
void bcbv3(B const &args) { cout << "B const ref: " << args.b << endl; }

bool ucbb1(A args, int user) { cout << "A object: " << args.b << ", " << user << endl; return false; }
bool ucbb2(A &args, int user) { cout << "A ref: " << args.b << ", " << user << endl; return false; }
bool ucbb3(A const &args, int user) { cout << "A const ref: " << args.b << ", " << user << endl; return false; }

void ucbv1(A args, int user) { cout << "A object: " << args.b << ", " << user << endl; }
void ucbv2(A &args, int user) { cout << "A ref: " << args.b << ", " << user << endl; }
void ucbv3(A const &args, int user) { cout << "A const ref: " << args.b << ", " << user << endl; }

bool ubcbb1(B args, int user) { cout << "B object: " << args.b << ", " << user << endl; return false; }
bool ubcbb2(B &args, int user) { cout << "B ref: " << args.b << ", " << user << endl; return false; }
bool ubcbb3(B const &args, int user) { cout << "B const ref: " << args.b << ", " << user << endl; return false; }

void ubcbv1(B args, int user) { cout << "B object: " << args.b << ", " << user << endl; }
void ubcbv2(B &args, int user) { cout << "B ref: " << args.b << ", " << user << endl; }
void ubcbv3(B const &args, int user) { cout << "B const ref: " << args.b << ", " << user << endl; }

void
test_ptr_arg()
{
	cout << "[Testing ptr arg]" << endl;
	Signal<A> signal1;
	Signal<B> signal2;

	signal1.Add(cbb1);
	signal1.Add(cbb2);
	signal1.Add(cbb3);
	signal1.Add(cbv1);
	signal1.Add(cbv2);
	signal1.Add(cbv3);
	signal2.Add(cbb1);
	signal2.Add(cbb2);
	signal2.Add(cbb3);
	signal2.Add(cbv1);
	signal2.Add(cbv2);
	signal2.Add(cbv3);

	signal1.AddAfter(cbb2);
	signal1.AddAfter(cbb3);
	signal1.AddAfter(cbv1);
	signal1.AddAfter(cbv2);
	signal1.AddAfter(cbv3);
	signal2.AddAfter(cbb1);
	signal2.AddAfter(cbb2);
	signal2.AddAfter(cbb3);
	signal2.AddAfter(cbv1);
	signal2.AddAfter(cbv2);
	signal2.AddAfter(cbv3);

	B args;
	args.b = 5;

	signal1(args);
	signal2(args);

	signal1.Add(bcbb1);
	signal1.Add(bcbb2);
	signal1.Add(bcbb3);
	signal1.Add(bcbv1);
	signal1.Add(bcbv2);
	signal1.Add(bcbv3);

	signal1.AddAfter(bcbb1);
	signal1.AddAfter(bcbb2);
	signal1.AddAfter(bcbb3);
	signal1.AddAfter(bcbv1);
	signal1.AddAfter(bcbv2);
	signal1.AddAfter(bcbv3);

	A &isab(args);

	signal1(isab);
}

void
test_ptr_user_arg()
{
	cout << "[Testing ptr user arg]" << endl;
	Signal<A> signal1;
	Signal<B> signal2;

	int user = 10;

	signal1.AddData(ucbb1, user);
	signal1.AddData(ucbb2, user);
	signal1.AddData(ucbb3, user);
	signal1.AddData(ucbv1, user);
	signal1.AddData(ucbv2, user);
	signal1.AddData(ucbv3, user);
	signal2.AddData(ucbb1, user);
	signal2.AddData(ucbb2, user);
	signal2.AddData(ucbb3, user);
	signal2.AddData(ucbv1, user);
	signal2.AddData(ucbv2, user);
	signal2.AddData(ucbv3, user);

	signal1.AddAfterData(ucbb1, user);
	signal1.AddAfterData(ucbb2, user);
	signal1.AddAfterData(ucbb3, user);
	signal1.AddAfterData(ucbv1, user);
	signal1.AddAfterData(ucbv2, user);
	signal1.AddAfterData(ucbv3, user);
	signal2.AddAfterData(ucbb1, user);
	signal2.AddAfterData(ucbb2, user);
	signal2.AddAfterData(ucbb3, user);
	signal2.AddAfterData(ucbv1, user);
	signal2.AddAfterData(ucbv2, user);
	signal2.AddAfterData(ucbv3, user);

	B args;
	args.b = 5;

	signal1(args);
	signal2(args);

	signal1.AddData(ubcbb1, user);
	signal1.AddData(ubcbb2, user);
	signal1.AddData(ubcbb3, user);
	signal1.AddData(ubcbv1, user);
	signal1.AddData(ubcbv2, user);
	signal1.AddData(ubcbv3, user);

	signal1.AddAfterData(ubcbb1, user);
	signal1.AddAfterData(ubcbb2, user);
	signal1.AddAfterData(ubcbb3, user);
	signal1.AddAfterData(ubcbv1, user);
	signal1.AddAfterData(ubcbv2, user);
	signal1.AddAfterData(ubcbv3, user);

	A &isab(args);

	signal1(isab);
}

struct CbObj
{
	bool cbb1(A args) { cout << "[Obj] A object: " << args.b << endl; return false; }
	bool cbb2(A &args) { cout << "[Obj] A ref: " << args.b << endl; return false; }
	bool cbb3(A const &args) { cout << "[Obj] A const ref: " << args.b << endl; return false; }

	void cbv1(A args) { cout << "[Obj] A object: " << args.b << endl; }
	void cbv2(A &args) { cout << "[Obj] A ref: " << args.b << endl; }
	void cbv3(A const &args) { cout << "[Obj] A const ref: " << args.b << endl; }

	bool bcbb1(B args) { cout << "[Obj] B object: " << args.b << endl; return false; }
	bool bcbb2(B &args) { cout << "[Obj] B ref: " << args.b << endl; return false; }
	bool bcbb3(B const &args) { cout << "[Obj] B const ref: " << args.b << endl; return false; }

	void bcbv1(B args) { cout << "[Obj] B object: " << args.b << endl; }
	void bcbv2(B &args) { cout << "[Obj] B ref: " << args.b << endl; }
	void bcbv3(B const &args) { cout << "[Obj] B const ref: " << args.b << endl; }


	bool ucbb1(A args, int user) { cout << "[Obj] A object: " << args.b << ", " << user << endl; return false; }
	bool ucbb2(A &args, int user) { cout << "[Obj] A ref: " << args.b << ", " << user << endl; return false; }
	bool ucbb3(A const &args, int user) { cout << "[Obj] A const ref: " << args.b << ", " << user << endl; return false; }

	void ucbv1(A args, int user) { cout << "[Obj] A object: " << args.b << ", " << user << endl; }
	void ucbv2(A &args, int user) { cout << "[Obj] A ref: " << args.b << ", " << user << endl; }
	void ucbv3(A const &args, int user) { cout << "[Obj] A const ref: " << args.b << ", " << user << endl; }

	bool ubcbb1(B args, int user) { cout << "[Obj] B object: " << args.b << ", " << user << endl; return false; }
	bool ubcbb2(B &args, int user) { cout << "[Obj] B ref: " << args.b << ", " << user << endl; return false; }
	bool ubcbb3(B const &args, int user) { cout << "[Obj] B const ref: " << args.b << ", " << user << endl; return false; }

	void ubcbv1(B args, int user) { cout << "[Obj] B object: " << args.b << ", " << user << endl; }
	void ubcbv2(B &args, int user) { cout << "[Obj] B ref: " << args.b << ", " << user << endl; }
	void ubcbv3(B const &args, int user) { cout << "[Obj] B const ref: " << args.b << ", " << user << endl; }

	virtual ~CbObj() {;}
};

struct CbObj2 : public CbObj
{

};

void
test_obj_arg()
{
	cout << "[Testing obj arg]" << endl;

	Signal<A> signal1;
	Signal<B> signal2;

	CbObj2 cbobj;

	signal1.Add(cbobj, &CbObj2::cbb1);
	signal1.Add(cbobj, &CbObj2::cbb2);
	signal1.Add(cbobj, &CbObj2::cbb3);
	signal1.Add(cbobj, &CbObj2::cbv1);
	signal1.Add(cbobj, &CbObj2::cbv2);
	signal1.Add(cbobj, &CbObj2::cbv3);
	signal2.Add(cbobj, &CbObj2::cbb1);
	signal2.Add(cbobj, &CbObj2::cbb2);
	signal2.Add(cbobj, &CbObj2::cbb3);
	signal2.Add(cbobj, &CbObj2::cbv1);
	signal2.Add(cbobj, &CbObj2::cbv2);
	signal2.Add(cbobj, &CbObj2::cbv3);


	signal1.AddAfter(cbobj, &CbObj2::cbb1);
	signal1.AddAfter(cbobj, &CbObj2::cbb2);
	signal1.AddAfter(cbobj, &CbObj2::cbb3);
	signal1.AddAfter(cbobj, &CbObj2::cbv1);
	signal1.AddAfter(cbobj, &CbObj2::cbv2);
	signal1.AddAfter(cbobj, &CbObj2::cbv3);
	signal2.AddAfter(cbobj, &CbObj2::cbb1);
	signal2.AddAfter(cbobj, &CbObj2::cbb2);
	signal2.AddAfter(cbobj, &CbObj2::cbb3);
	signal2.AddAfter(cbobj, &CbObj2::cbv1);
	signal2.AddAfter(cbobj, &CbObj2::cbv2);
	signal2.AddAfter(cbobj, &CbObj2::cbv3);

	B args;
	args.b = 5;

	signal1(args);
	signal2(args);

	signal1.Add(cbobj, &CbObj2::bcbb1);
	signal1.Add(cbobj, &CbObj2::bcbb2);
	signal1.Add(cbobj, &CbObj2::bcbb3);

	signal1.Add(cbobj, &CbObj2::bcbv1);
	signal1.Add(cbobj, &CbObj2::bcbv2);
	signal1.Add(cbobj, &CbObj2::bcbv3);

	A &isab(args);

	signal1(isab);
}

void
test_obj_user_arg()
{
	cout << "[Testing obj user arg]" << endl;

	Signal<A> signal1;
	Signal<B> signal2;

	int user = 10;

	CbObj2 cbobj;

	signal1.AddData(cbobj, &CbObj2::ucbb1, user);
	signal1.AddData(cbobj, &CbObj2::ucbb2, user);
	signal1.AddData(cbobj, &CbObj2::ucbb3, user);
	signal1.AddData(cbobj, &CbObj2::ucbv1, user);
	signal1.AddData(cbobj, &CbObj2::ucbv2, user);
	signal1.AddData(cbobj, &CbObj2::ucbv3, user);
	signal2.AddData(cbobj, &CbObj2::ucbb1, user);
	signal2.AddData(cbobj, &CbObj2::ucbb2, user);
	signal2.AddData(cbobj, &CbObj2::ucbb3, user);
	signal2.AddData(cbobj, &CbObj2::ucbv1, user);
	signal2.AddData(cbobj, &CbObj2::ucbv2, user);
	signal2.AddData(cbobj, &CbObj2::ucbv3, user);

	signal1.AddAfterData(cbobj, &CbObj2::ucbb1, user);
	signal1.AddAfterData(cbobj, &CbObj2::ucbb2, user);
	signal1.AddAfterData(cbobj, &CbObj2::ucbb3, user);
	signal1.AddAfterData(cbobj, &CbObj2::ucbv1, user);
	signal1.AddAfterData(cbobj, &CbObj2::ucbv2, user);
	signal1.AddAfterData(cbobj, &CbObj2::ucbv3, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbb1, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbb2, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbb3, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbv1, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbv2, user);
	signal2.AddAfterData(cbobj, &CbObj2::ucbv3, user);

	B args;
	args.b = 5;

	signal1(args);
	signal2(args);

	signal1.AddData(cbobj, &CbObj2::ubcbb1, user);
	signal1.AddData(cbobj, &CbObj2::ubcbb2, user);
	signal1.AddData(cbobj, &CbObj2::ubcbb3, user);
	signal1.AddData(cbobj, &CbObj2::ubcbv1, user);
	signal1.AddData(cbobj, &CbObj2::ubcbv2, user);
	signal1.AddData(cbobj, &CbObj2::ubcbv3, user);

	signal1.AddAfterData(cbobj, &CbObj2::ubcbb1, user);
	signal1.AddAfterData(cbobj, &CbObj2::ubcbb2, user);
	signal1.AddAfterData(cbobj, &CbObj2::ubcbb3, user);
	signal1.AddAfterData(cbobj, &CbObj2::ubcbv1, user);
	signal1.AddAfterData(cbobj, &CbObj2::ubcbv2, user);
	signal1.AddAfterData(cbobj, &CbObj2::ubcbv3, user);

	A &isab(args);

	signal1(isab);
}

int
main(int argc, char const *argv[])
{
	test_ptr_arg();
	cout << endl;

	test_obj_arg();
	cout << endl;

	test_ptr_user_arg();
	cout << endl;

	test_obj_user_arg();

	return 0;
}
