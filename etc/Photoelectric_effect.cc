
double Array_min(double a[]) {
  double min = a[0];
  for(int b = 1; b <= 3430; b++) {
    if(a[b] < min) {
      min = a[b];
    }
  }
  return min;
}

void Photoelectric_effect() {

  double X[4] = {4.80645, 5.05085, 5.67619, 6.38116};
  double Y_E[4] = {0.237, 0.413, 0.592, 0.796};
  double x, y;
  double calc = 0;
  double ta, a, b;
  double min_1, min = 10000;

  //TGraph * grp = new TGraph();
  //grp->SetTitle("Frequency-Stopping voltage; F(10^14Hz); Volt(V)");  
  //TRandom3 * r = new TRandom3();
  //r->SetSeed();

  double tb[70];
  int s = 20;
  int q = 0;
 
  for(double l = 2; l > 0; l -= 0.1) { 
    tb[q] = l;
    //printf("%f \n", tb[q]);
    q++;
  }

  for(double k = 0; k < 5; k += 0.1) {
    tb[s] = -k;
    //printf("%f %f \n", tb[s], k);
    s++;
  }

  int m = 0;
  int n = 1;
  double sum;
  double sum_a[3430];
 
  for(double ta = 0.1; ta < 5; ta += 0.01) {
    for(int i = 0; i < 70; i++) {
      for(int j = 0; j < 4; j++) {
        calc = pow((Y_E[j] - (ta * X[j] + tb[i])), 2);
        sum += calc; 
        printf("sum:%f %d \n", sum, m);
      }
      sum_a[m*n] = sum;
      sum = 0;
      m++;
    }
  n++;
  }
 // min = Array_min(sum_a);
 // printf("min: %f \n", min);  
    //printf("min: %f, a: %f, b: %f \n", min, a, b); 
}


 
