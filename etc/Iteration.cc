
const double H = 197.3;
const double M = 511 * pow(10, 3);
const double PI = 3.141592;
//double NUM01 = 0;
//double NUM02 = 0;

/*double pentration(double E) {
  double delta = HABAR / sqrt(2 * M * NUM01 - E);
  return delta;
}

double a_energy(double D) {
  double energy = (pow(PI, 2) * pow(HABAR, 2)) / 2 * M * pow(NUM02 + D, 2);
  return energy;
}*/

void Iteration() {

  double delta = 0;
  double NUM01 = 0;
  double NUM02 = 0;
  double energy = 0;
  double delta2 = 0;
  int count = 0;
  
  printf("Writting the potential energy value and length. \n");
  printf("potential energy: ");
  scanf("%lf", &NUM01);
  printf("length: ");
  scanf("%lf", &NUM02);

  delta = H / sqrt(2 * M * NUM01);
  printf("%lf\n", delta);

  while(1) {
    energy = (pow(PI, 2) * pow(H, 2)) / (2 * M * pow((NUM02 + 2 * delta), 2));
    delta2 = H / sqrt(2 * M * (NUM01 - energy));

    if(delta == delta2) 
      break;
    else {
      delta = delta2;
    }
    count++;
    printf("count:%d, energy:%lf, pentration:%lf \n",count, energy, delta);
  }
  printf("count:%d , energy:%lf , new pentration:%lf \n", count, energy, delta);

}
