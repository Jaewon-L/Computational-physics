

const double pi = 3.141592;

//Specific charge calculation formula
double emcal(double volt, double current, double radius) {
  double mu = 4 * pi * pow(10, -7);
  double value = pow(1.25, 3) * 2 * volt * pow(0.15, 2) / pow((130 * mu * current * radius), 2);
  return value;
}

void specific_charge() {
  
  const int SIZE = 16;  //try number
  const double THV = 1.7588 * pow(10, 11); //True value(C/kg)
  double V[SIZE] = {190, 190, 190, 190, 210, 210, 210, 210, 230, 230, 230, 230, 250, 250, 250, 250}; //volt
  double I[SIZE] = {0.80, 0.95, 1.12, 1.46, 0.80, 0.95, 1.12, 1.46, 0.80, 0.95, 1.12, 1.46, 0.80, 0.95, 1.12, 1.46}; //ampere
  double R[SIZE] = {0.077, 0.07, 0.057, 0.046, 0.083, 0.062, 0.055, 0.045, 0.086, 0.075, 0.055, 0.046, 0.088, 0.078, 0.06, 0.048}; //meter
  double em[SIZE]; 
  double sum = 0;
  double sum2 = 0;

  TGraph * grp = new TGraph();
  
  for(int i = 0; i < SIZE; i++) {
    em[i] = emcal(V[i], I[i], R[i]);
    sum += em[i];
    sum2 += pow(em[i], 2);
    printf("%d: %e C/kg \n",i, em[i]);
  }
  //printf("sum: %e, sum2: %e \n", sum, sum2);
  
  printf("\n");
  printf("------------------------------------------------------------------------\n");
  printf("\n");

  //Error rate

  double er; 
  double er_mean;
  for(int m = 0; m < SIZE; m++) {
    er = (abs(em[m] - THV) / THV) * 100;
    er_mean += er;
    printf("%d: error rate = %f%% \n", m, er);
  }
  er_mean /= SIZE;
  printf("er_mean: %f%% \n", er_mean);

  printf("\n");
  printf("------------------------------------------------------------------------\n");
  printf("\n");

  //Mean, Variance, SD, SE
 
  double mean;
  double mean2;
  double variance;
  double SD;
  double SE;

  mean = sum / SIZE;
  mean2 = sum2 / SIZE;
  variance = mean2 - pow(mean, 2);
  SD = sqrt(variance);
  SE = sqrt(SD / sqrt(SIZE));
  printf("mean: %e C/kg, variance: %e, SD: %e, SE: %e \n", mean, variance, SD, SE);

  printf("\n");
  printf("------------------------------------------------------------------------\n");
  printf("\n");
 
  //Confidence Interval

  const double Z = 1.96; //95% confidence section Z score
  double rsd; //Right side section
  double lsd; //Left side section
  double mrsd; //Mean + rsd  
  double mlsd; //Mean - lsd

  rsd = Z * SD / sqrt(SIZE);
  lsd = Z * SD / sqrt(SIZE);
  mrsd = mean + rsd;
  mlsd = mean - lsd;  
  printf("95%% Confidence range: %e C/kg ~ %e C/kg \n", mlsd, mrsd);
  
  printf("\n");
  printf("------------------------------------------------------------------------\n");
  printf("\n");

  //Bubble sort 
 
  double temp;

  for(int j = 0; j < SIZE - 1; j++) {
    for(int k = 0; k < SIZE - 1 - j; k++) {
      if(em[k] > em[k+1]) {
        temp = em[k];
        em[k] = em[k+1];
        em[k+1] = temp;
      }
    }
  }

  /*for(int j = 0; j < SIZE; j++) {
    printf("%e \n", em[j]);
  }*/
 
  //Gaussian Function

  double y = 0;

  for(int l = 0; l < SIZE; l++) {
      y = TMath::Gaus(em[l], mean, SD, kTRUE);
	  //y = 1 / (SD * sqrt(2 * pi)) * exp(-pow((em[l] - mean), 2) / (2 * pow(SD, 2)));
      grp->SetPoint(l, em[l], y);
  } 
  grp->Draw("APL");

}
