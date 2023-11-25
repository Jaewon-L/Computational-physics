

void oil_drop() {

  const double e = 1.602 * pow(10, -19); // true electron charge value
  const double pi = 3.141592;
  const int V = 500; //volt(V)
  const double d = 7 * pow(10, -3); //distance(m)
  const double g = 9.8; //acceleration of gravity(m/s^2)
  const int rho = 886; //oil density(kg/m^3)
  const double p = 101.3 * pow(10, 3); //air pressure (kg*m/s^2/m^2)
  const double eta = 1.825 * pow(10, -5); //viscosity of oil(kg/m*s)
  const double GV1 = 1.5 * pow(10, -19); //minimum range of guesses
  const double GV2 = 2.0 * pow(10, -19);  //maximum range of guesses
  double tr[6] = {4.11, 3.25, 1.11, 0.65, 0.70, 0.81}; // drop of oil(s)
  double tf[6] = {3.05, 2.91, 2.68, 2.86, 3.95, 3.87}; //rising of oil(s)
  double oil_q[6]; // charge
  double vr;
  double vf;

  //formula for oil droplets
  for(int i = 0; i < 6; i++) {
    vr = 5 * pow(10, -4) / tr[i]; //(m/s)
    vf = 5 * pow(10, -4) / tf[i]; //(m/s)
    oil_q[i] = 18 * pi * (d / V) * sqrt(((pow(eta, 3) * pow(vf, 3)) / (2 * rho * g))) * (1 + vr / vf);
    printf("i: %d, oil_q: %eC, vr: %em/s, vf: %em/s \n",i ,oil_q[i], vr, vf);
  }

  printf("-------------------------------------------------------------------------\n");

  double m1;
  double m2;
  double mid;
  double q[6]; //final value

  //calculation the amount of charge
  for(int j = 0; j < 6; j++) {
    m1 = oil_q[j] / GV1;
    m2 = oil_q[j] / GV2;
    mid = (m1 + m2) / 2;
    q[j] = oil_q[j] / mid;
    printf("j: %d, oil_q: %eC, q: %eC, m1: %f, m2: %f, mid: %f \n", j, oil_q[j], q[j], m1, m2, mid);
  }

}

    
