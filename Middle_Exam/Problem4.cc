#define pi TMath::Pi()				//pi value
#define MAX_DATA_COUNT 300			//file data array limit
#define AAS 86						//analytic array size

//basic values
const double g = 9.8;				//gravitional accelaration m/s^2
const double m = 30;				//mass (kg)
const double theta = pi/4;			//an angle of launch
const double IV = 600;				//Initial Velocity (m/s)
const double IVX = IV*cos(theta);   //Initial Velocity Xaxis (m/s)
const double IVY = IV*sin(theta);   //Initial Velocity Yaxis (m/s)

//============================================functions==========================================//
// basically calculated a formula based on the case where the resistance is -kmv^2 by referring to the book.

//Velocity of Xaxis function over time (Non_resistance)
double X_Velocity_Nr(double Time) {
    return IVX;
}

//Distance of Xaxis function over time (Non_resistance)
double X_Distance_Nr(double Time) {
    return IVX*Time;
}

//Velocity of Yaxis function over time (Non_resistance)
double Y_Velocity_Nr(double Time) {
    return -1*g*Time + IVY;
}

//Distnace of Yaxis function over time (Non_resistance)
double Y_Distance_Nr(double Time) {
    return -0.5*g*pow(Time,2) + IVY*Time;
}

//Velocity of Xaxis function over time (resistance)
double X_Velocity_r(double Time, double k) {
    return IVX/(1+IVX*k*Time);
}

//Distance of Xaxis function over time (resistance)
double X_Distance_r(double Time, double k) {
    return 1/k*log(IVX*k*Time + 1);
}

//Velocity of Yaxis function over time (resistance) v_y > 0
double Y_Velocity_r_P(double Time, double k) {
    return -1*sqrt(g/k)*tan(atan(-1*IVY*sqrt(k/g)) + sqrt(g*k)*Time);
}

//I calculated the initial conditions based on this because the direction of motion changes when the velocity in the y direction of the object is 34.8 seconds.

//Velocity of Yaxis function over time (resistance) v_y < 0
double Y_Velocity_r_M(double Time, double k) {
    return -1*sqrt(g/k)*tanh(sqrt(g*k)*Time - 34.8*sqrt(g*k));
}

//Distnace of Yaxis function over time (resistance) v_y > 0
double Y_Distance_r_P(double Time, double k) {
    return 1/k*log(cos(Time*sqrt(g*k)-atan(IVY*sqrt(k/g))))+1/(2*k)*log((pow(IVY,2)*k+g)/g);
}

//Distnace of Yaxis function over time (resistance) v_y < 0
double Y_Distance_r_M(double Time, double k) {
    return 6609 - 1/k*log(cosh((Time-34.8)*sqrt(g*k)));
}

//============================================functions==========================================//

//main function
void Problem4() { 

	//open file made by plot digitizer
	FILE * resl = fopen("resistance_Low_Velocity.txt", "r");		//resistance_low_velocity
	FILE * resh = fopen("resistance_High_Velocity.txt", "r");		//resistance_high_velocity
	FILE * FVXr = fopen("Velocity_X_resistance.txt", "r");			//File_Velocity_X_resistance 의 약자
	FILE * FVYr = fopen("Velocity_Y_resistance.txt", "r");			//File_Velocity_Y_resistance 의 약자	
	FILE * FXYP = fopen("XY_True_position.txt", "r");				//File_Velocity_Y_resistance 의 약자	
	FILE * FTYP = fopen("TY_True_position.txt", "r");				//File_Velocity_Y_resistance 의 약자	

	//Variables to store data in a file
	double VL[MAX_DATA_COUNT];	  //figure_2_3(c) relatively Low_Velocity array
	double NL[MAX_DATA_COUNT];	  //Figure_2_3(c) relatively Low_resistance array
	double VH[MAX_DATA_COUNT];	  //figure_2_3(d) relatively High_Velocity array
	double NH[MAX_DATA_COUNT];	  //Figure_2_3(d) relatively High_resitance array
	double VXr[MAX_DATA_COUNT];   //Velocity_X_resistance array
	double XTr[MAX_DATA_COUNT];   //X_Time_resistance array
	double VYr[MAX_DATA_COUNT];   //Velocity_Y_resistance array
	double YTr[MAX_DATA_COUNT];   //Y_Time_resistance array
	double XYPX[MAX_DATA_COUNT];   //Y_Time_resistance array
	double XYPY[MAX_DATA_COUNT];   //Y_Time_resistance array
	double TYPT[MAX_DATA_COUNT];   //Y_Time_resistance array
	double TYPY[MAX_DATA_COUNT];   //Y_Time_resistance array

	int count = 0;		//variables array size
	int klcount = 0;	//count for k low velocity value fitting
	int khcount = 0;	//count for k high velocity value fitting
	int XTrcount = 0;	//count for X_Time_resistance
	int YTrcount = 0;	//count for Y_Time_resistance
	int XYTrcount = 0;	//count for Y_Time_resistance
	int TYTrcount = 0;	//count for Y_Time_resistance

//==================================reading res(low) file===================================//
//Open the file and save it to an array
	if(resl == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(resl) && count < MAX_DATA_COUNT) {
		if(fscanf(resl, "%lf %lf", &VL[count], &NL[count]) != 2) {
			break;
		    printf("error \n");
		}   
      count++;
	}   

    fclose(resl); //file close

	klcount = count; //save a number of the array of Low velocity resistance coefficient

	double klValues[klcount];

	//N = kmv^{2} => k = N/(mv^{2})
    for(int i = 0; i < klcount; i++) {
        klValues[i] = NL[i]/(m*pow(VL[i],2));
    }   
/*
	//check value
    for (int i = 0; i < count; i++) {
      printf("%lf %lf %lf \n", V[i], N[i], kValues[i]);
    }   
*/
    printf("\n");

//==================================reading res(high) file===================================//
//Open the file and save it to an array

	count = 0; //count reset

	if(resh == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(resh) && count < MAX_DATA_COUNT) {
		if(fscanf(resh, "%lf %lf", &VH[count], &NH[count]) != 2) {
			break;
		    printf("error \n");
		}   
      count++;
	}   

    fclose(resh);

	khcount = count; //save a number of the array of High velocity resistance coefficient

	double khValues[khcount];

	//N = kmv^{2} => k = N/(mv^{2})
    for(int i = 0; i < khcount; i++) {
        khValues[i] = NH[i]/(m*pow(VH[i],2));
	}

//==================================reading FXYP file===================================//
//Open the file and save it to an array

	count = 0; //count reset

	if(FXYP == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(FXYP) && count < MAX_DATA_COUNT) {
		if(fscanf(FXYP, "%lf %lf", &XYPX[count], &XYPY[count]) != 2) {
			break;
			printf("error \n");
		}   
      count++;
	}   

    fclose(FXYP);

	XYTrcount = count;

	TGraph * X_Y_T_r = new TGraph();

    for (int i = 0; i < XYTrcount; i++) {
      //printf("%lf %lf \n", YTNr[i], VYNr[i]);
		X_Y_T_r->SetPoint(i, XYPX[i], XYPY[i]);
    }   

    printf("\n");

//==================================reading FTYP file===================================//
//Open the file and save it to an array

	count = 0; //count reset

	if(FTYP == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(FTYP) && count < MAX_DATA_COUNT) {
		if(fscanf(FTYP, "%lf %lf", &TYPT[count], &TYPY[count]) != 2) {
			break;
			printf("error \n");
		}   
      count++;
	}   

    fclose(FTYP);

	TYTrcount = count;

	TGraph * T_Y_T_r = new TGraph();

    for(int i = 0; i < TYTrcount; i++) {
      //printf("%lf %lf \n", YTNr[i], VYNr[i]);
		T_Y_T_r->SetPoint(i, TYPT[i], TYPY[i]);
		
    }   

    printf("\n");

//==================================reading FVXr file===================================//

	count = 0;

	if(FVXr == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(FVXr) && count < MAX_DATA_COUNT) {
        if(fscanf(FVXr, "%lf %lf", &XTr[count], &VXr[count]) != 2) {
			break;
			printf("error \n");
		}   
		count++;
	}   

    fclose(FVXr);

	XTrcount = count; //save a number of the array of Xaxis time count array

    TGraph * T_V_X_r = new TGraph();  //True X_Velocity

	//check value
    for (int i = 0; i < XTrcount; i++) {
		//printf("%d %lf %lf \n", i,XTr[i], VXr[i]);
		T_V_X_r->SetPoint(i, XTr[i], VXr[i]);
    }   

    printf("\n");

//==================================reading FVYr file===================================//

	count = 0;

	if(FVYr == NULL) {
      printf("file not found! \n");
    }   

    while(!feof(FVYr) && count < MAX_DATA_COUNT) {
		if(fscanf(FVYr, "%lf %lf", &YTr[count], &VYr[count]) != 2) {
			break;
			printf("error \n");
		}   
		count++;
	}   

    fclose(FVYr);

	YTrcount = count;  //save a number of the array of Yaxis time count array
    
	TGraph * T_V_Y_r = new TGraph();  //True X_Velocity

	//check value
    for (int i = 0; i < YTrcount; i++) {
		//printf("%lf %lf \n", YTr[i], VYr[i]);
		T_V_Y_r->SetPoint(i, YTr[i], VYr[i]);
    }   

    printf("\n");

//==============================================kValue_fitting_part===================================================//
	
	//
    TF1 * FFL = new TF1("FFL","pol11");		//fitting function Low velocity resistance
    TF1 * FFH = new TF1("FFH","pol4");		//fitting function High velocity resistance

	TCanvas * c1 = new TCanvas("c1","kValues", 800, 700);
	c1->Divide(1,2);

    TGraph * FGL = new TGraph();			  //drawing fitting graph (Low velocity)
	FGL->GetXaxis()->SetTitle("Velocity [m/s]");	
	FGL->GetYaxis()->SetTitle("klValue");	

    TGraph * FGH = new TGraph();			  //drawing fitting graph (High velocity)
	FGH->GetXaxis()->SetTitle("Velocity [m/s]");	
	FGH->GetYaxis()->SetTitle("khValue");	
 
	for(int i = 0; i < klcount; i++) {
		//printf("%lf %lf \n", VL[i], klValues[i]);
		FGL->SetPoint(i, VL[i], klValues[i]);
	}
	for(int i = 0; i < khcount; i++) {
		//printf("%lf %lf \n", VH[i], khValues[i]);
		FGH->SetPoint(i, VH[i], khValues[i]);
	}

	c1->cd(1);
    FGL->Fit(FFL);		//graph fitting
    FGL->Draw("AP");
	FGL->SetTitle("Low_Velocity-kValues Graph");
    FGL->SetMarkerStyle(7);

	c1->cd(2);
    FGH->Fit(FFH);		//graph fitting
    FGH->Draw("AP");
	FGH->SetTitle("High_Velocity-kValues Graph");
    FGH->SetMarkerStyle(7);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Calculating_part<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
//==============================================Non_resistance_part===================================================//

    //Analytic method
    TGraph * A_V_X_Nr = new TGraph();                  //Analytic method X_Velocity Non_resistance Graph

    TGraph * A_X_Nr = new TGraph();                    //Analytic method X_Distance Non_resistance Graph
    A_X_Nr->GetXaxis()->SetTitle("Time [s]");          //Xaxis label
    A_X_Nr->GetYaxis()->SetTitle("Position [m]");      //Yaxis label

    TGraph * A_V_Y_Nr = new TGraph();                  //Analytic method Y_Velocity Non_resistance Graph
    A_V_Y_Nr->GetXaxis()->SetTitle("Time [s]");        //Xaxis label
    A_V_Y_Nr->GetYaxis()->SetTitle("Velocity [m/s]");  //Yaxis label

    TGraph * A_Y_Nr = new TGraph();                    //Analytic method Y_Distance Non_resistance Graph
    A_Y_Nr->GetXaxis()->SetTitle("Time [s]");          //Xaxis label
    A_Y_Nr->GetYaxis()->SetTitle("Position [m]");      //Yaxis label

    TGraph * A_XY_Nr = new TGraph();				   //Analytic method X-Y_Position Non_resistance Graph
    A_XY_Nr->GetXaxis()->SetTitle("X_Position [m]");   //Xaxis label
    A_XY_Nr->GetYaxis()->SetTitle("Y_Position [m]");   //Yaxis label

    int npoint = 0; //check count

    //In the Analytic method, the speed in the Y direction and the cummulative distance traveled over a time intervla of 1 second 
    for(double t = 0; t < AAS; t++) {
		//output check
        //cout << "t = " << t << "  " << "X_Velocity_Nr: " << X_Velocity_Nr(t) << "  " << " X_Distance_Nr: " << X_Distance_Nr(t) << endl;
        //cout << "t = " << t << "  " << "Y_Velocity_Nr: " << Y_Velocity_Nr(t) << "  " << " Y_Distance_Nr: " << Y_Distance_Nr(t) << endl;
        //cout << "t = " << t << "  " << "X_Position_Nr: " << X_Distance_Nr(t) << "  " << " Y_Position_Nr: " << Y_Distance_Nr(t) << endl;
        //calculating 
		A_V_X_Nr->SetPoint(npoint, t, X_Velocity_Nr(t));                                           
        A_X_Nr->SetPoint(npoint, t, X_Distance_Nr(t));
        A_V_Y_Nr->SetPoint(npoint, t, Y_Velocity_Nr(t));                                           
        A_Y_Nr->SetPoint(npoint, t, Y_Distance_Nr(t));
        A_XY_Nr->SetPoint(npoint, X_Distance_Nr(t), Y_Distance_Nr(t));
        npoint++;
    } 

//================================================Numerical Method=======================================================//

    TGraph * N_V_X_Nr = new TGraph();  //Numerical X_Velocity_Non_resistance
    TGraph * N_X_Nr = new TGraph();    //Numerical X_Distance_Non_resistance
    TGraph * N_V_Y_Nr = new TGraph();  //Numerical Y_Velocity_Non_resistance
    TGraph * N_Y_Nr = new TGraph();    //Numerical Y_Distance_Non_resistance
    TGraph * N_XY_Nr = new TGraph();   //Numerical X-Y Position_Non_resistance

	//To be intution, I chose a method that embed the initial value.
    N_V_X_Nr->SetPoint(0, 0, IVX);
    N_X_Nr->SetPoint(0, 0, 0);
    N_V_Y_Nr->SetPoint(0, 0, IVY);
    N_Y_Nr->SetPoint(0, 0, 0);
	N_XY_Nr->SetPoint(0, 0, 0);

    double dt = 0.5;	//Time interval; In order to match the analytic value more, the time interval, should be shorter.

    //Assume that the resistance for one second is proportional to the square of the velocity and that the acceleration is constant
    //Calculate approximation from initial 0 to 1 second
    double X_N_V_Nr = IVX;					//X_Numerical_Velocity_Non_resistance
    double X_N_Nr = X_N_V_Nr*dt;            //X_Numerical_Distance_Non_resistance
    double Y_N_V_Nr = -1*g*dt + IVY;		//Y_Numerical_Velocity_Non_resistance
    double Y_N_Nr = (-0.5*g*dt + IVY)*dt;   //4.9m = 1/2*9.8m/s * 1s (Length), The reason for multiplying by 1/2 is to reduce the overall accumulated distance error by reducing the difference in the initial value, using 1/2*a*t^2, where a = acceleration //Y_Numerical_Distance_Non_resistance

    double t = 0.5;	//time setting	
        
    //1st output print
    //cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "X_Velocity_Nr: " << X_N_V_Nr << "m/s" << "  " << "X_Distance_Nr: " << X_N_Nr << "m"  << endl;
    //cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "Y_Velocity_Nr: " << Y_N_V_Nr << "m/s" << "  " << "Y_Distance_Nr: " << Y_N_Nr << "m"  << endl;

    N_V_X_Nr->SetPoint(1, t, X_N_V_Nr);
    N_X_Nr->SetPoint(1, t, X_N_Nr);
    N_V_Y_Nr->SetPoint(1, t, Y_N_V_Nr);
    N_Y_Nr->SetPoint(1, t, Y_N_Nr);
	N_XY_Nr->SetPoint(1, X_N_Nr, Y_N_Nr);
	
    npoint = 2;  

    //Recurringly obtaining numericla values
    for(int i = 0; i < 160; i++) {
        double X_N_V_Nr_I = X_N_V_Nr;				//X_Numerical_Velocity_Non_resistance_Interation
        double X_N_Nr_I = X_N_V_Nr_I*dt + X_N_Nr;   //X_Numerical_Distance_Non_resistance_Interation
        double Y_N_V_Nr_I = -1*g*dt + Y_N_V_Nr;     //Y_Numerical_Velocity_Non_resistance_Interation
        double Y_N_Nr_I = Y_N_V_Nr_I*dt + Y_N_Nr;   //Y_Numerical_Distance_Non_resistance_Interation
        t += 0.5; //time add

        //output print
        //cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "X_Velocity_Nr: " << X_N_V_Nr_I << "m/s" << "  " << "X_Distance_Nr: " << X_N_Nr_I << "m"  << endl;
        //cout << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "Y_Velocity_Nr: " << Y_N_V_Nr_I << "m/s" << "  " << "Y_Distance_Nr: " << Y_N_Nr_I << "m"  << endl;

        N_V_X_Nr->SetPoint(npoint, t, X_N_V_Nr_I); 
        N_X_Nr->SetPoint(npoint, t, X_N_Nr_I);         
        N_V_Y_Nr->SetPoint(npoint, t, Y_N_V_Nr_I); 
        N_Y_Nr->SetPoint(npoint, t, Y_N_Nr_I);   
		N_XY_Nr->SetPoint(npoint, X_N_Nr_I, Y_N_Nr_I);       
        npoint++;

		//Replace variables for repetition
        X_N_V_Nr = X_N_V_Nr_I;
        X_N_Nr = X_N_Nr_I;
        Y_N_V_Nr = Y_N_V_Nr_I;
        Y_N_Nr = Y_N_Nr_I;
    }

//============================================resistance part=====================================================//
//============================================Analytic method=====================================================//

    TGraph * A_V_X_r = new TGraph();                  //Analytic method X_Velocity_resistance Graph
    A_V_X_r->GetXaxis()->SetTitle("Time [s]");        //Xaxis label
    A_V_X_r->GetYaxis()->SetTitle("Velocity [m/s]");  //Yaxis label
    TGraph * A_X_r = new TGraph();                    //Analytic method X_Distance_resistance Graph
    TGraph * A_V_Y_r = new TGraph();                  //Analytic method Y_Velocity_resistance Graph
    TGraph * A_Y_r = new TGraph();                    //Analytic method Y_Distance_resistance Graph
    TGraph * A_XY_r = new TGraph();					  //Analytic method X-Y_Position_resistance Graph

    npoint = 0; //check point reset

	double k; //resistance coefficent
	double kL = FFL->Eval(92); //The speed from +-92 to 0 was measured incorrectly due to ambiguous data, so I put it as a constant. (resistance coefficent(low velocity)
	double kH; //resistance coefficent(high velocity)
	double AVXr; //analytic X_velocity variable 
	double AXr;  //analytic X_distance variable
	double AVXra[AAS]; //analytic X_velocity array for save    
	double AXra[AAS];  //analytic X_distance array for save    

	//In order to calculate it as accurately as possible, I first calculated the function of the "k" value with speed based on the data in the book, and then put in the resistance coefficient with the speed of the reliable interval.	
    for(int t = 0; t < AAS; t += 1) {
		if(t == 0) {
			AXr = 0; //Initial condition x(t) = 0
			//cout << "t = " << t << "  " << "X_Velocity: " << X_Velocity_r(t, k) << "  " << " X_Distance: " << X_Distance_r(t, k) << endl;
			A_V_X_r->SetPoint(npoint, t, IVX);                               
			A_X_r->SetPoint(npoint, t, AXr);
			AVXr = IVX;
			AVXra[t] = AVXr;
			AXra[t] = AXr;
			npoint++;
		}
		else {
			if((AVXr >= 92) && (AVXr < 470)) {
				k = FFL->Eval(AVXr); //Calculate the value of k according to the speed
				AVXr = X_Velocity_r(t, k);
				AXr = X_Distance_r(t, k);
				//cout << "t = " << npoint << "  " << "X_Velocity: " << AVXr  << "  " << " X_Distance: " << AXr << endl;
				A_V_X_r->SetPoint(npoint, t, AVXr);                                               
				A_X_r->SetPoint(npoint, t, AXr);
				AVXra[t] = AVXr;
				AXra[t] = AXr;
				npoint++;
			}
			else if(AVXr <= 92) {
				AVXr = X_Velocity_r(t, kL);
				AXr = X_Distance_r(t, kL);
				//cout << "t = " << npoint << "  " << "X_Velocity: " << AVXr << "  " << " X_Distance: " << AXr << endl;
				A_V_X_r->SetPoint(npoint, t, AVXr);                                               
				A_X_r->SetPoint(npoint, t, AXr);
				AVXra[t] = AVXr;
				AXra[t] = AXr;
				npoint++;
			}
			else if(AVXr >= 470) {
				kH = FFH->Eval(AVXr); //Resistance factor for high speed
				AVXr = X_Velocity_r(t, kH);
				AXr = X_Distance_r(t, kH);
				//cout << "t = " << npoint << "  " << "X_Velocity: " << AVXr << "  " << " X_Distance: " << AXr << endl;
				A_V_X_r->SetPoint(npoint, t, AVXr);                                               
				A_X_r->SetPoint(npoint, t, AXr);
				AVXra[t] = AVXr;
				AXra[t] = AXr;
				npoint++;
			}
		}
	}

	//Y_axis calculation
	npoint = 0; //checkpoint reset
	
	double AVYr; //analytic X_velocity variable
	double AYr;	 //analytic Y_distance variable
	double AVYra[AAS]; //analytic Y_velocity array for save 
	double AYra[AAS];  //analytic Y_distance array for save 

	//Like x, I used the same way in the y-direction. However, the y-direction changes the direction of motion when the speed passes zero, so the code is somewhat complicated because we take this into account.
    for(int t = 0; t < AAS; t += 1) {
		if(t == 0) {
			AYr = 0;  //Initial condition y(t) = 0
			//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
			A_V_Y_r->SetPoint(npoint, t, IVY);                               
			A_Y_r->SetPoint(npoint, t, AYr);
			AVYr = IVY;
			AVYra[t] = AVYr;
			AYra[t] = AYr;
			npoint++;
		}
		else {
			if((AVYr >= 92) && (AVYr <= 470)) {
				k = FFL->Eval(abs(AVYr)); //Calculate the value of k according to the speed
				AVYr = Y_Velocity_r_P(t, k);
				AYr = Y_Distance_r_P(t, k);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
			else if((AVYr < 92) && (AVYr > 0)) {
				AVYr = Y_Velocity_r_P(t, kL);
				AYr = Y_Distance_r_P(t, kL);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
			else if((AVYr > 470) && (AVYr > 0)) {
				kH = FFH->Eval(abs(AVYr));
				AVYr = Y_Velocity_r_P(t, kH);
				AYr = Y_Distance_r_P(t, kH);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
			else if((AVYr <= -92) && (AVYr >= -470)) {
				k = FFL->Eval(abs(AVYr));
				AVYr = Y_Velocity_r_M(t, k);
				AYr = Y_Distance_r_M(t, k);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
			else if((AVYr > -92) && (AVYr < 0)) {
				AVYr = Y_Velocity_r_M(t, kL);
				AYr = Y_Distance_r_M(t, kL);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
			else if((AVYr < -470) && (AVYr < 0)) {
				kH = FFH->Eval(abs(AVYr));
				AVYr = Y_Velocity_r_M(t, kH);
				AYr = Y_Distance_r_M(t, kH);
				//cout << "t = " << t << "  " << "AY_Velocity: " << AVYr << "  " << "AY_Distance: " << AYr << endl;
				A_V_Y_r->SetPoint(npoint, t, AVYr);                                               
				A_Y_r->SetPoint(npoint, t, AYr);
				AVYra[t] = AVYr;
				AYra[t] = AYr;
				npoint++;
			}
		}	
	}

	//Y Poistion part about X Position
	npoint = 0; //check point reset

	//Drawing graph about X-Y Position
	for(int t = 0; t < AAS; t += 1) {
		A_XY_r->SetPoint(npoint, AXra[t], AYra[t]);
		npoint++;
    }                                                     


//============================================Numerical Method===============================================//

    TGraph * N_V_X_r = new TGraph();  //Numerical X_Velocity_resistance
    TGraph * N_X_r = new TGraph();    //Numerical X_Distance_resistance
    TGraph * N_V_Y_r = new TGraph();  //Numerical Y_Velocity_resistance
    TGraph * N_Y_r = new TGraph();    //Numerical Y_Distance_resistance
    TGraph * N_XY_r = new TGraph();   //Numerical X-Y_Position_resistance
	
	int Xc; //X_count
	int Yc; //Y_count

	//
	for(int i = 0; i <= klcount; i++) { 
		if(VL[i] > IVX) {
			Xc = i;
			break;
		}	
	}

	for(int i = 0; i <= klcount; i++) { 
		if(VL[i] > IVY) {
			Yc = i;
			break;
		}
	}	
	//cout << VXr[XTrcount-1] << "  " << XLc << endl;  //check point

	//좀 더 정확한 수치값을 구하기 위해서는 속도가 424m/s 부터 떨어지기 직전의 배열의 크기의 값과 x 방향으로 총 비행한 시간을 나누어야 하지만, 데이터가 한정되었고 특정한 시간에 대한 속도의 저항력을 보정하기가 어려워 424m/s 부터 책에서 측정 할 수 있는 범위까지의 저항력의 배열의 수를 나누었습니다. 물론 무차별 대입법으로 책에있는 true 값과 최대한 비슷하게 만들어 본적도 있지만 수치해석의 방법과는 거리가 멀기에 최대한 기존의 데이터의 정보만으로 속도 그래프를 재구성하는 것을 생각해 보았습니다.
	double Time_interval_X = XTr[XTrcount-1]/Xc;
	//double Time_interval_X = 0.52;
	double dtx = Time_interval_X;
	double tx = Time_interval_X;

	npoint = 0;

	double NTXra[Xc];
    double NVXra[Xc];
    double NXra[Xc];
    
    //In the Analytic method, the speed in the Y direction and the cummulative distance traveled over a time intervla of 1 second 
	double X_F_r = -1*NL[Xc]; 
	double X_N_V_r = X_F_r/m*dtx + IVX;          //Xaxis_Numerical_Velocity_resistance 책에서 얻은 데이터로부터 물체의 질량을 나누어 저항력을 적용했습니다.
	double X_N_r = X_N_V_r*dtx;					 //Xaxis_Numerical_Distance_resistance 
	NTXra[0] = tx;								 //값을 저장할 배열(time)
	NVXra[0] = X_N_V_r;							 //값을 저장할 배열(velocity)
	NXra[0] = X_N_r;							 //값을 저장할 배열(distance)
	
	npoint = 1;

	double X_F_r_I = 0;                           //저항력 반복을 위한 값. 책에 있는 데이터를 불러와 시간간격에 따라 다른 값을 적용하였습니다.
    double X_N_V_r_I = 0;						  //Xaxis_Numerical_Velocity_resistance_Interation
	double X_N_r_I = 0;							  //Xaxis_numerical_Veloxity_resistance_Interation

	for(int i = 1; i <= Xc; i++) {
			X_F_r_I = -1*NL[Xc-i];                        
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Xaxis_Numerical_Velocity_resistance_Iteration        
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Xaxis_Numerical_Velocity_resistance_Iteration
			//cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += Time_interval_X;		
			NTXra[i] = tx; 
			npoint++;	

			//Repalce part of variable for iteration
			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
	}

	//다음의 일련의 코드는 x 방향의 저항력을 특정한 시간간격을 달리해 적용을 해 보았습니다. 좀 전에 언급했듯이, 얻을 수 있는 데이터가 한정되어 있어 제가 임의로 시간 구간을 나누어 저항력을 달리 적용해 보았습니다. 결과적으로 true(book) 값과 비슷한 결과를 얻을 수 있었습니다.
/*
	for(int i = 1; i <= Xc; i++) {
		if(tx < 4.5) { 
			X_F_r_I = -1*NL[Xc-i];                        //F_{r} = -kmv^{2}
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Numerical Velocity           
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Numerical Distance and save
			cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += Time_interval_X;		
			NTXra[i] = tx; 
			npoint++;	

			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
		}	
		else if((tx < 10) && (tx >= 4)) {
			X_F_r_I = -1*NL[Xc-i];                        //F_{r} = -kmv^{2}
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Numerical Velocity           
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Numerical Distance and save
			cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += 0.28;		
			NTXra[i] = tx; 
			npoint++;	

			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
		}
		else if((tx <= 35) && (tx >= 10)) {
			X_F_r_I = -1*NL[Xc-i];                        //F_{r} = -kmv^{2}
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Numerical Velocity           
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Numerical Distance and save
			cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += 0.5;		
			NTXra[i] = tx; 
			npoint++;	

			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
		}
		else if((tx > 35) && (tx <= 45)) {
			X_F_r_I = -1*NL[Xc-i];                        //F_{r} = -kmv^{2}
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Numerical Velocity           
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Numerical Distance and save
			cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += 0.35;		
			NTXra[i] = tx; 
			npoint++;
	
			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
		}
		else if((tx >= 45)) {
			X_F_r_I = -1*NL[Xc-i];                        //F_{r} = -kmv^{2}
			X_N_V_r_I = X_F_r_I/m*dtx + X_N_V_r;            //Numerical Velocity           
			X_N_r_I = X_N_V_r_I*dtx + X_N_r;                //Numerical Distance and save
			cout << "delta_t = " << npoint << tx - 1 << "-" << tx << " : " << setw(10) << "retarding force: " << X_F_r_I << "m/s^2"  << "  " <<"X_Velocity_r: " << X_N_V_r_I << "m/s" << "  " << "X_Distance_r: " << X_N_r_I << "m"  << endl;
			NVXra[i] = X_N_V_r_I;
			NXra[i] = X_N_r_I;
			tx += 0.17;		
			NTXra[i] = tx; 
			npoint++;
	
			X_N_V_r = X_N_V_r_I;
			X_N_r = X_N_r_I;
		}
	}	
*/			

	//for y calculate time reset
	double Time_interval_Y = YTr[YTrcount-1]/Yc;

	dt = Time_interval_Y;

	t = Time_interval_Y;
	
    npoint = 0;

    double NTYra[Yc];
    double NVYra[Yc];
    double NYra[Yc];
      
	//Y방항 또한 X방향과 마찬가지로 동일한 방법을 적용했습니다. 다만 Y 방항은 Y방향의 속도가 0이되는 지점의 기준으로 운동방향이 바뀌므로 이것을 고려했습니다.  
	double Y_F_r = -1*NL[Yc];
	double Y_N_V_r = Y_F_r/m*dt - g*dt + IVY;           //Velocity
	double Y_N_r = (Y_F_r/m*dt - 0.5*g*dt + IVY)*dt;    //4.9m = 1/2*9.8m/s * 1s (Length), The reason for multiplying by 1/2 is to reduce the overall accumulated distance error by reducing the difference in the initial value, using 1/2*a*t^2, where a = acceleration        
	NTYra[0] = t;  
    NVYra[0] = Y_N_V_r;
    NYra[0] = Y_N_r;


    npoint = 1;

	double Y_F_r_I = 0;					//Yaxis 저항력
    double Y_N_V_r_I = 0;				//Yaxis_Numerical_Velocity_resistance_Iteration         
    double Y_N_r_I = 0;                 //Yaxis_Numerical_Distance_resistance_Iteration

	for(int i = 1; i <= Yc; i++) {  
		if(Y_N_V_r >= 0) { 
			Y_F_r_I = -1*NL[Yc-2*i];                        //Y방향의 속도는 우연히 참값과 비교해 볼 때 비교적 정확하게 구할 수 있었습니다. plot digitalizer 로 만든 데이터에서 특정한 시간 간격이 흐를 때 마다 저향력이 감소되는 간격을 2배로 설정했습니다. 그 결과로 y방향의 속도가 424m/s 이하 부터의 배열의 총 개수가 221에서 거의 절반인 100쯤 y의 운동방향이 바뀌었습니다.
            Y_N_V_r_I = Y_F_r_I/m*dt - g*dt + Y_N_V_r;     //Numerical Velocity          
            Y_N_r_I = Y_N_V_r_I*dt + Y_N_r;                //Numerical Distance and save
			//cout << npoint << "delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "retarding force: " << Y_F_r_I << "m/s^2"  << "  " <<"Y_Velocity_r: " << Y_N_V_r_I << "m/s" << "  " << "Y_Distance_r: " << Y_N_r_I << "m"  << endl;
            NVYra[i] = Y_N_V_r_I;
            NYra[i] = Y_N_r_I;
            t += Time_interval_Y;         
		    NTYra[i] = t;  
            npoint++;   

            Y_N_V_r = Y_N_V_r_I;
            Y_N_r = Y_N_r_I;
        } 
		else if(Y_N_V_r <= 0) {  
			Y_F_r_I = NL[2*i-Yc-30];                        //마찬가지로 저항력을 서서히 늘려나갔습니다. 
            Y_N_V_r_I = Y_F_r_I/m*dt - g*dt + Y_N_V_r;     //Yaxis_Numerical_Velocity_resistance_Iteration       
            Y_N_r_I = Y_N_V_r_I*dt + Y_N_r;                //Yaxis_Numerical_Velocity_resistance_Iteration
			//cout << npoint <<"delta_t = " << t - 1 << "-" << t << " : " << setw(10) << "retarding force: " << Y_F_r_I << "m/s^2"  << "  " <<"Y_Velocity_r: " << Y_N_V_r_I << "m/s" << "  " << "Y_Distance_r: " << Y_N_r_I << "m"  << endl;
            NVYra[i] = Y_N_V_r_I;
            NYra[i] = Y_N_r_I;
            t += Time_interval_Y;         
		    NTYra[i] = t;  
            npoint++;   

			//Repalce part of variable for iteration
            Y_N_V_r = Y_N_V_r_I;
            Y_N_r = Y_N_r_I;
		}
	}


	//Drawing graph
	if(Xc == Yc) {
		for(int i = 0; i <= Xc; i++) { 
			N_V_X_r->SetPoint(i, NTXra[i], NVXra[i]);
			N_X_r->SetPoint(i, NTXra[i], NXra[i]);
			N_V_Y_r->SetPoint(i, NTYra[i], NVYra[i]);
			N_Y_r->SetPoint(i, NTYra[i], NYra[i]);
			N_XY_r->SetPoint(i, NXra[i], NYra[i]);
		}
	}
	else {
			cout << "Array dimension error" << endl;
	}
                                                                                             
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Calculating part end<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//=================================================Drawing_part=======================================================//
 
    //Drawing graph
    TCanvas * c2 = new TCanvas("c2", "Velocity-Time, Distance-Time", 1800,1000);
    c2->Divide(2,2);

    c2->cd(1);
    A_V_X_r->Draw("AP");
	A_V_X_r->SetTitle("Time-Velocity(X_axis) Graph");
    A_V_X_r->SetMarkerStyle(7);
    A_V_X_r->SetMarkerColor(2);

    A_V_X_Nr->Draw("Psame");
    A_V_X_Nr->SetMarkerStyle(7);
    A_V_X_Nr->SetMarkerColor(1);

    N_V_X_Nr->Draw("Psame");
    N_V_X_Nr->SetMarkerStyle(7);
    N_V_X_Nr->SetMarkerColor(3);

    N_V_X_r->Draw("Psame");
    N_V_X_r->SetMarkerStyle(7);
    N_V_X_r->SetMarkerColor(4);

    T_V_X_r->Draw("Psame");
    T_V_X_r->SetMarkerStyle(7);
    T_V_X_r->SetMarkerColor(6);

    //Making legend
    TLegend * leg1 = new TLegend(0.75, 0.6, 0.9, 0.8, "", "brNDC");
    leg1->AddEntry(A_V_X_Nr, "X_Analytic_V_Nr", "p");                                                               
    leg1->AddEntry(N_V_X_Nr, "X_Numerical_V_Nr", "p");
    leg1->AddEntry(A_V_X_r, "X_Analytic_V_r", "p");                                                                
    leg1->AddEntry(N_V_X_r, "X_Numerical_V_r", "p");
    leg1->AddEntry(T_V_X_r, "X_True(book)_V_r", "p");
    leg1->Draw("same");
    
	c2->cd(2);
	A_V_Y_Nr->Draw("AP");
	A_V_Y_Nr->SetTitle("Time-Velocity(Y_axis) Graph");
    A_V_Y_Nr->SetMarkerStyle(7);
    A_V_Y_Nr->SetMarkerColor(1);

	A_V_Y_r->Draw("Psame");
    A_V_Y_r->SetMarkerStyle(7);
    A_V_Y_r->SetMarkerColor(2);
    
	N_V_Y_Nr->Draw("Psame");
    N_V_Y_Nr->SetMarkerStyle(7);
    N_V_Y_Nr->SetMarkerColor(3);

    N_V_Y_r->Draw("Psame");
    N_V_Y_r->SetMarkerStyle(7);
    N_V_Y_r->SetMarkerColor(4);

    T_V_Y_r->Draw("Psame");
    T_V_Y_r->SetMarkerStyle(7);
    T_V_Y_r->SetMarkerColor(6);

    TLegend * leg2 = new TLegend(0.75, 0.7, 0.9, 0.9, "", "brNDC");
    leg2->AddEntry(A_V_Y_Nr, "Y_Analytic_V_Nr", "p");                                 
    leg2->AddEntry(N_V_Y_Nr, "Y_Numerical_V_Nr", "p");
    leg2->AddEntry(A_V_Y_r, "Y_Analytic_V_r", "p");                                           
    leg2->AddEntry(N_V_Y_r, "Y_Numerical_V_r", "p");
    leg2->AddEntry(T_V_Y_r, "Y_True(book)_V_r", "p");
    leg2->Draw("same");

    c2->cd(3);
    A_X_Nr->Draw("AP");
	A_X_Nr->SetTitle("Time-Position(X_axis) Graph");
    A_X_Nr->SetMarkerStyle(7);
    A_X_Nr->SetMarkerColor(1);

    A_X_r->Draw("Psame");
    A_X_r->SetMarkerStyle(7);
    A_X_r->SetMarkerColor(2);
    
	N_X_Nr->Draw("Psame");
    N_X_Nr->SetMarkerStyle(7);
    N_X_Nr->SetMarkerColor(3);

    N_X_r->Draw("Psame");
    N_X_r->SetMarkerStyle(7);
    N_X_r->SetMarkerColor(4);

    TLegend * leg3 = new TLegend(0.15, 0.65, 0.3, 0.85, "", "brNDC");
    leg3->AddEntry(A_X_Nr, "X_Analytic_D_Nr", "p");
    leg3->AddEntry(N_X_Nr, "X_Numerical_D_Nr", "p");
    leg3->AddEntry(A_X_r, "X_Analytic_D_r", "p");
    leg3->AddEntry(N_X_r, "X_Numerical_D_r", "p");
    leg3->Draw("same");

    c2->cd(4);
	A_Y_Nr->Draw("AP");
	A_Y_Nr->SetTitle("Time-Position(Y_axis) Graph");
    A_Y_Nr->SetMarkerStyle(7);
    A_Y_Nr->SetMarkerColor(1);

    A_Y_r->Draw("Psame");
    A_Y_r->SetMarkerStyle(7);
    A_Y_r->SetMarkerColor(2);
   
	N_Y_Nr->Draw("Psame");
    N_Y_Nr->SetMarkerStyle(7);
    N_Y_Nr->SetMarkerColor(3);

    N_Y_r->Draw("Psame");
    N_Y_r->SetMarkerStyle(7);
    N_Y_r->SetMarkerColor(4);

    T_Y_T_r->Draw("Psame");
    T_Y_T_r->SetMarkerStyle(7);
    T_Y_T_r->SetMarkerColor(6);

    TLegend * leg4 = new TLegend(0.75, 0.7, 0.9, 0.9, "", "brNDC");
    leg4->AddEntry(A_Y_Nr, "Y_Analytic_D_Nr", "p");                                                                       
    leg4->AddEntry(N_Y_Nr, "Y_Numerical_D_Nr", "p");
    leg4->AddEntry(A_Y_r, "Y_Analytic_D_r", "p");                                                                       
    leg4->AddEntry(N_Y_r, "Y_Numerical_D_r", "p");
    leg4->AddEntry(T_Y_T_r, "Y_True(book)value", "p");
    leg4->Draw("same");

//==============================================Drawing Position===========================================//

    TCanvas * c3 = new TCanvas("c3", "X_Position-Y_Position", 1300,800);
	c3->cd(1);
	A_XY_Nr->Draw("AP");
	A_XY_Nr->SetTitle("X_Position-Y_Position Graph");
	A_XY_Nr->SetMarkerStyle(7);
    A_XY_r->SetMarkerColor(1);

	A_XY_r->Draw("Psame");
	A_XY_r->SetMarkerStyle(7);
    A_XY_r->SetMarkerColor(2);

	N_XY_Nr->Draw("Psame");
	N_XY_Nr->SetMarkerStyle(7);
	N_XY_Nr->SetMarkerColor(3);

	N_XY_r->Draw("Psame");
	N_XY_r->SetMarkerStyle(7);
	N_XY_r->SetMarkerColor(4);

	X_Y_T_r->Draw("Psame");
	X_Y_T_r->SetMarkerStyle(7);
	X_Y_T_r->SetMarkerColor(6);

    TLegend * leg5 = new TLegend(0.75, 0.7, 0.9, 0.9, "", "brNDC");
    leg5->AddEntry(A_XY_Nr, "Analytic_XY_P_Nr", "p");                                                                      
    leg5->AddEntry(N_XY_Nr, "Numerical__XY_P_Nr", "p");                                                                   
    leg5->AddEntry(A_XY_r, "Analytic_XY_P_r", "p");                                                                       
    leg5->AddEntry(N_XY_r, "Numerical_XY_P_r", "p");                                                                       
    leg5->AddEntry(X_Y_T_r, "X-Y_Position_True(book)", "p");                                                                       
    leg5->Draw("same");
}
//==============================================Drawing part end=================================================//




