
//basic values
double k = 0.01;	//resistance constant
double g = 9.8;     //gravitational acceleration (m/s^2)
double IVY = 0;     //Initial Velocity Yaxis	 (m/s)

//Velocity function over time
double Y_Velocity(double Time) {
    return sqrt(g/k)*tanh(sqrt(k*g)*Time);
}

//Distance function over time
double Y_Distance(double Time) {
    return 1/k*log(cosh(sqrt(k*g)*Time));
}

//main function
void Problem3() {

	//Analytic method
    TGraph * A_V_Y = new TGraph();					//Analytic method Velocity Graph
    A_V_Y->GetXaxis()->SetTitle("Time [s]");		//Xaxis label
    A_V_Y->GetYaxis()->SetTitle("Velocity [m/s]");	//Yaxis label

    TGraph * A_Y = new TGraph();					//Analytic method Distance Graph
    A_Y->GetXaxis()->SetTitle("Time [s]");			//Xaxis
    A_Y->GetYaxis()->SetTitle("Position [m]");		//Yaxis

    int npoint = 0; //numbering

	//In the Analytic method, the speed in the Y direction and the cummulative distance traveled over a time intervla of 1 second 
    for(double t = 0; t <= 100; t++) {
        //cout << "t = " << t << "  " << "Y_Velocity: " << Y_Velocity(t) << "  " << " Y_Distance: " << Y_Distance(t) << endl;
        A_V_Y->SetPoint(npoint, t, Y_Velocity(t));
        A_Y->SetPoint(npoint, t, Y_Distance(t));
        npoint++;
    }

//=======================================================Numerical Method=====================================================//

    TGraph * N_V_Y = new TGraph();  //Numerical Velocity Graph
    TGraph * N_Y = new TGraph();    //Numerical Distance Graph

	//To be intuitive, I chose a method that embed a initial value.
    N_V_Y->SetPoint(0, 0, IVY);
    N_Y->SetPoint(0, 0, 0);

	//Assume that the resistance for one second is proportional to the square of the velocity and that the acceleration is constant
	//Calculate approximation from initial 0 to 1 second
    double dt = 1.0;							//Time interval
    double Y_F_r = -k*pow(IVY,2);				//F_{r} = -kmv^{2} ,where m = 1kg (Y_Force_resistance)
    double Y_N_V = Y_F_r + g*dt + IVY;			//9.8m/s = 0 + 9.8m/s^{2} * 1s + 0 (Y_Numerical_Velocity)
    double Y_N = (Y_F_r + 0.5*g*dt + IVY)*dt;   //4.9m = 1/2*9.8m/s * 1s (Length), The reason for multiplying by 1/2 is to reduce the overall accumulated distance error by reducing the difference in the initial value, using 1/2*a*t^2, where a = acceleration (Y_Numerical_Distance)

    double t = 1; //time count
	
	//print for check
	//cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "retarding force: " << Y_F_r << "  " << "m/s^2"  << "Velocity: " << Y_N_V << "m/s" << "  " << "Distance: " << Y_N << "m"  << endl;

    N_V_Y->SetPoint(1, t, Y_N_V);
    N_Y->SetPoint(1, t, Y_N);

    npoint = 2; 

	//Recurringly obtaining numericla values
	for(int i = 0; i < 100; i++) {
        double Y_F_r_I = -k*pow(Y_N_V,2);               //F_{r} = -kmv^{2}
        double Y_N_V_I = Y_F_r_I*dt + g*dt + Y_N_V;		//Y_Numerical_Velocity_Interation (Velocity)     
        double Y_N_I = Y_N_V_I*dt + Y_N;                //Y_Numerical cumulative Distance_Interation (Distance) 
        t += 1; //time plus

		//print for check
		//cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "retarding force: " << Y_F_r_I << "  " << "m/s^2"  << "Velocity: " << Y_N_V_I << "m/s" << "  " << "Distance: " << Y_N_I << "m"  << endl;

        N_V_Y->SetPoint(npoint, t, Y_N_V_I); 
        N_Y->SetPoint(npoint, t, Y_N_I);     
        npoint++;

		//Replace variables for repetition
        Y_N_V = Y_N_V_I;
        Y_N = Y_N_I;
    }   

    //Drawing graph
    TCanvas * c1 = new TCanvas("c1", "c1");
    c1->Divide(1,2);
    c1->cd(1);
    A_V_Y->Draw("AP");
	A_V_Y->SetTitle("Time-Velocity Graph");
    A_V_Y->SetMarkerStyle(7);

    N_V_Y->Draw("Psame");
    N_V_Y->SetMarkerStyle(7);
    N_V_Y->SetMarkerColor(2);

	//Making legend
    TLegend * leg1 = new TLegend(0.75, 0.35, 0.9, 0.15, "", "brNDC");
    leg1->AddEntry(A_V_Y, "Analytic", "p");
    leg1->AddEntry(N_V_Y, "Numeric", "p");
    leg1->Draw("same");

    c1->cd(2);
    A_Y->Draw("AP");
	A_Y->SetTitle("Time-Position Graph");
    A_Y->SetMarkerStyle(7);

    N_Y->Draw("Psame");
    N_Y->SetMarkerStyle(7);
    N_Y->SetMarkerColor(2);

    TLegend * leg2 = new TLegend(0.15, 0.60, 0.3, 0.80, "", "brNDC");
    leg2->AddEntry(A_Y, "Analytic", "p");
    leg2->AddEntry(N_Y, "Numeric", "p");
    leg2->Draw("same");

}

