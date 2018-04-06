// This macro reads in the output from trig_eff_makevalues.C to plot the trigger effeciency versus attenuation

#include <iostream>
#include <fstream>

using namespace std;

void plot_trig_eff_att_graph()
{
  ifstream infile;
  infile.open("trig_eff_att_2.txt");
  double trig[19];
  double att[19];
  TFile * _file_out = new TFile("trig_att_graph.root","RECREATE");
  for(int i=0;i<19;i++){
    infile >> trig[i] >> att[i];
    cout << trig[i];
  }
  TGraph *gtrig = new TGraph(19,att,trig);
  infile.close();
  _file_out->cd();
  gtrig->Write("trigeff_att");
  _file_out->Close();
}
