#define pi TMath::Pi() //definition pi value

//basic values
double k = 0.01;			   //resistance coefficient
double theta = pi/3;		   //an angle of launch
double IV = 600;               //Initial Velocity
double IVX = IV*cos(theta);    //Intiial Velocity Xaxis

//Velocity function over time
double X_Velocity(double Time) { 
	return IVX*exp(-k*Time);      
}

//Distance function over time
double X_Distance(double Time) {
	return IVX/k*(1-exp(-k*Time));
}

//Main function
void Problem1() {

	//Analytic method
	TGraph * A_V_X = new TGraph();				    //Analytic method Velocity Graph
	A_V_X->GetXaxis()->SetTitle("Time [s]");		//Xaxis label
	A_V_X->GetYaxis()->SetTitle("Velocity [m/s]");	//Yaxis label

	TGraph * A_X = new TGraph();					//Analytic method Distance Graph
	A_X->GetXaxis()->SetTitle("Time [s]");			//Xaxis label
	A_X->GetYaxis()->SetTitle("Position [m]");		//Yaxis label

	int npoint = 0;	//numbering						
	
	//The speed in the X direction and the accumulated distance traveled over the time interval of 1 second in the Analytical method.
	for(double t = 0; t <= 100; t++) {
		cout << "t = " << t << "  " << "X_Velocity: " << X_Velocity(t) << "m/s" << "  " <<"X_Distance: " << X_Distance(t) << endl;
		A_V_X->SetPoint(npoint, t, X_Velocity(t));
		A_X->SetPoint(npoint, t, X_Distance(t));
		npoint++;
	}

	//Numerical Method
	TGraph * N_V_X = new TGraph();  //Numerical Velocity
	TGraph * N_X = new TGraph();    //Numerical Distance


	//To be intution, I chose a method that embed the initial value.
	N_V_X->SetPoint(0, 0, IVX); //nth, Time, Velocity
	N_X->SetPoint(0, 0, 0);		//nth, Time, Velocity

	//Assume constant resistance for 1 second
	//I find approximate values by 1 second between time intervals
	double dt = 1.0;				//time interval
	double X_F_r = -k*IVX;			//F_{r} = -kmv, where m = 1kg (Xaxis_Force_resistance)
	double X_N_V = X_F_r*dt + IVX;  //ex)297m/s = -3m/s^{2} * 1s + 300m/s (Xaxis_Numerical_Velocity)
	double X_N = X_N_V*dt;			//ex)297m = 297m/s * 1s, length save (Xaxis_Numerical_Distance)

	double t = 1; //time count

	//초기값 출력
	//cout << "delta_t = " << t - 1 << "-" << t <<" : " << setw(10) << "retarding force: " << X_F_r << "m/s^2" << "  " << "Velocity: " << X_N_V << "m/s" << "  "  << "Distance: " << X_N << "m" << endl;

	//Approximate values from 0 to 1
	N_V_X->SetPoint(1, t, X_N_V);
	N_X->SetPoint(1, t, X_N);

	npoint = 2;

	//Recurringly obtaining numerical values
	for(int i = 0; i < 100; i++) {
		double X_F_r_I = -k*X_N_V;					//-2.97m/s^{2} (X_Force_resistance_Iteration)
		double X_N_V_I = X_F_r_I*dt + X_N_V;		//X_Numerical_Velocity_Iteration  ex)294.03m/s = -2.97m/s^{2} * 1s + 297m/s 
		double X_N_I = X_N_V_I*dt + X_N;			//X_Numerical cumulative Distance_Iteration  ex)591.03m = 297m + 294.03m
		t += 1;

		//출력문
		//cout << "delta_t = " << t - 1 << "-" << t <<" : " << setw(10) << "retarding force:" << X_F_r_I << "m/s^2" << "  " << "Velocity: " << X_N_V_I << "m/s" << "  " << "Distance: " << X_N_I << "m" << endl;

		N_V_X->SetPoint(npoint, t, X_N_V_I); 
		N_X->SetPoint(npoint, t, X_N_I);	
		npoint++;

		//Replace variables for repetition
		X_N_V = X_N_V_I;
		X_N = X_N_I;
	}

	//Drawing graph
	TCanvas * c1 = new TCanvas("c1", "c1");
	c1->Divide(1,2);
	c1->cd(1);
	A_V_X->Draw("AP");
	A_V_X->SetTitle("Time-Velocity Graph");
	A_V_X->SetMarkerStyle(7);

	N_V_X->Draw("Psame");
	N_V_X->SetMarkerStyle(7);
	N_V_X->SetMarkerColor(2);

	//Creating Legend
	TLegend * leg1 = new TLegend(0.7, 0.7, 0.85, 0.9, "", "brNDC");
	leg1->AddEntry(A_V_X, "Analytic", "p");
	leg1->AddEntry(N_V_X, "Numeric", "p");
	leg1->Draw("same");

	c1->cd(2);
	A_X->Draw("AP");
	A_X->SetTitle("Time-Position Graph");
	A_X->SetMarkerStyle(7);

	N_X->Draw("Psame");
	N_X->SetMarkerStyle(7);
	N_X->SetMarkerColor(2);

	TLegend * leg2 = new TLegend(0.15, 0.60, 0.3, 0.80, "", "brNDC");
	leg2->AddEntry(A_X, "Analytic", "p");
	leg2->AddEntry(N_X, "Numeric", "p");
	leg2->Draw("same");
}


	
