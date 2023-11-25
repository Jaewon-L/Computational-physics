#include <iomanip>

//sin함수
double sin(double * v, double * p) {

	double x = v[0];

	double a = p[0];
	double b = p[1];

	return a*sin(b*x);
}


//메인함수
void hw1() {

	TF1 * func = new TF1("func", sin, 0, 10, 4);
	func->SetParameter(0, 1);
	func->SetParameter(1, 1);

	int npoint = 100;	//나눌 간격
	double Xmin = 0;	//적분구간 중 최솟값
	double Xmax = 10;   //적분구간 중 최댓값
	double step = (Xmax - Xmin)/(double)npoint;  //간격
	double integral_0th = 0;  //0차
	double integral_1th = 0;  //1차
	double integral_2th = 0;  //2차

	//구분구적법 함수들
	for(int i = 0; i < npoint; i++) {
		integral_0th += func->Eval(Xmin + i*step)*step;
		integral_1th += func->Eval(Xmin + (i+1)*step)*step;
	}
	for(int i = 1; i < npoint/2; i++) {
		integral_2th += 1/3.0*(2*func->Eval(Xmin + 2*i*step) + 4*func->Eval(Xmin + (2*i-1)*step))*step;
	}
	integral_2th += 1/3.0*(func->Eval(Xmin) - func->Eval(Xmax))*step;
	

	//출력문
	cout << "integral_0th:" << setw(8) << integral_0th << endl;
	cout << "integral_1th:" << setw(8) << integral_1th << endl;
	cout << "integral_2th:" << setw(8) << integral_2th << endl;

	cout << endl;
}
