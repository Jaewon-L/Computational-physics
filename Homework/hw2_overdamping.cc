#define k 1.0 //constant
#define m 1.0 //mass(kg)
#define c 6.0 //overdamping

#define fx(t,x,v) (v)
#define fv(t,x,v) (-(k)/(m)*(x)-(c)/(m)*(v))

#define N 300
#define A 2

double t_array_s[N], x_array_s[N], v_array_s[N];
double t_array_f[N], x_array_f[N], v_array_f[N];
double h = 0.1;

void runge_kutta_second_order(double a, double b) {
	double t = 0, x = A, v = 0;
	for(int i = 0; i < N; i++) { 
		t = i*h;
		double fn_x = fx(t,x,v);
		double fn_v = fv(t,x,v);
		double fa_x = fx(t+a*h, x+b*h*fn_x, v+b*h*fn_v);
		double fa_v = fv(t+a*h, x+b*h*fn_x, v+b*h*fn_v);

		x += h*(0.5*fn_x + 0.5*fa_x);
		v += h*(0.5*fn_v + 0.5*fa_v);
		t_array_s[i] = t+h;
		x_array_s[i] = x;
		v_array_s[i] = v;
	}
}

void runge_kutta_fourth_order(double a, double b) {
	double t = 0, x = A, v = 0;
	for(int i = 0; i < N; i++) { 
		t = i*h;
		double k1x = fx(t,x,v);
		double k1v = fv(t,x,v);
		double k2x = fx(t+b*h, x+b*h*k1x, v+b*h*k1v);
		double k2v = fv(t+b*h, x+b*h*k1x, v+b*h*k1v);
		double k3x = fx(t+b*h, x+b*h*k2x, v+b*h*k2v);
		double k3v = fv(t+b*h, x+b*h*k2x, v+b*h*k2v);
		double k4x = fx(t+a*h, x+a*h*k3x, v+a*h*k3v);
		double k4v = fv(t+a*h, x+a*h*k3x, v+a*h*k3v);

		x += h*(k1x+2*k2x+2*k3x+k4x)/6;
		v += h*(k1v+2*k2v+2*k3v+k4v)/6;

		t_array_f[i] = t+h;
		x_array_f[i] = x;
		v_array_f[i] = v;
	}
}

void hw2_overdamping() {

	runge_kutta_second_order(1.0, 1.0);
	runge_kutta_fourth_order(1.0, 0.5);

	TGraph * grp_x_s = new TGraph(N, t_array_s, x_array_s);
	TGraph * grp_v_s = new TGraph(N, t_array_s, v_array_s);
	TGraph * grp_x_f = new TGraph(N, t_array_f, x_array_f);
	TGraph * grp_v_f = new TGraph(N, t_array_f, v_array_f);

	TCanvas * c1 = new TCanvas("c1", "c1");
	c1->Divide(1,2);
	c1->cd(1);
	grp_x_s->Draw("AP"); grp_x_s->SetMarkerStyle(7);
	grp_x_f->Draw("Psame"); grp_x_f->SetMarkerStyle(7); grp_x_f->SetMarkerColor(2);
	grp_x_s->GetYaxis()->SetTitle("Position");

	TLegend * leg1 = new TLegend(0.7, 0.7, 0.9, 0.9, "", "brNDC");
	leg1->AddEntry(grp_x_s, "Position(second)", "p");
	leg1->AddEntry(grp_x_f, "Position(fourth)", "p");
	leg1->Draw("same");

	c1->cd(2);
	grp_v_s->Draw("AP"); grp_v_s->SetMarkerStyle(7);
	grp_v_f->Draw("Psame"); grp_v_f->SetMarkerStyle(7); grp_v_f->SetMarkerColor(2);
	grp_v_s->GetYaxis()->SetTitle("Velocity");

	TLegend * leg2 = new TLegend(0.7, 0.2, 0.9, 0.4, "", "brNDC");
	leg2->AddEntry(grp_v_s, "Velocity(second)", "p");
	leg2->AddEntry(grp_v_f, "Velocity(fourth)", "p");
	leg2->Draw("same");
}
