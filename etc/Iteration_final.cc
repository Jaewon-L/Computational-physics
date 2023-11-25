
const double H = 197.3;
const double M = 511 * pow(10, 3);
const double PI = 3.141592;
double NUM01 = 0;
double NUM02 = 0;

double pentration(double E) {
  double delta = H / sqrt(2 * M * (NUM01 - E));
  return delta;
}

double a_energy(double delta) {
  double E = (pow(PI, 2) * pow(H, 2)) / (2 * M * pow(NUM02 + 2 * delta, 2));
  return E;
}

void Iteration_final() {

  double i, j, k; 
  int count = 0;

  printf("Write the potential energy value and length. \n");
  printf("potential energy: ");
  scanf("%lf", &NUM01);
  printf("length: ");
  scanf("%lf", &NUM02);

  i = H / sqrt(2 * M * NUM01);
  printf("initial pentration: %lfnm\n", i);

  while(1) {
    j = a_energy(i);
    k = pentration(j);
    if(i == k) 
      break;
    else {
      i = k;
    }
    count++;
    printf("count: %d, energy: %lfeV, pentration: %lfnm \n",count, j, k);
  }
  printf("trying count: %d , energy: %lfeV , new pentration: %lfnm \n", count, j, k);

}
