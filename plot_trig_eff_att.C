// This macro reads in the output from trig_eff_makevalues.C to plot the trigger effeciency versus attenuation

#include <iostream>
#include <fstream>

using namespace std;

void plot_trig_eff_att()
{
  ifstream infile;
  infile.open("trig_eff_att_2.txt");
  double trig=0;
  int att=0;
  TProfile *p = new TProfile("Trigger Efficiency Vs Attenuation", "Trigger Efficiency vs Attenuation", 25, 21, 46);
  TFile * _file_out = new TFile("trig_att_profile.root","RECREATE");
  p->SetMarkerStyle(34);
  while(infile.good()){
    infile >> trig >> att;
    p->Fill(att, trig);
  }
  infile.close();
  _file_out->cd();
  p->Write("trigeff_att");
  _file_out->Close();
}
