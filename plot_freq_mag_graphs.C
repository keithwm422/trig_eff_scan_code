// This will plot the ratio of the magnitudes for two different averaged attenutation pulses measured after the high pass filter (Ch1) for ANITA-4 and will help determine if the variable attenuation was applied after or before this Channel was measured. 
#include <iostream>
#include <fstream>
using namespace std;

void plot_freq_mag_graphs()
{
  cout << "starting " << endl;

  // opening files to plot.
  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);

  TFile * _file2= TFile::Open("/home/keith/icemc_trig_scan_tests/freq_mag_graphs_33dB_avg_trimmed.root");
  TFile * _file3= TFile::Open("/home/keith/icemc_trig_scan_tests/freq_mag_graphs_43dB_avg_trimmed.root");

  _file2->cd();
  g2 = (TGraph*)_file2->Get("freq33dB_trimmed");
  _file3->cd();
  g3 = (TGraph*)_file3->Get("freq43dB_trimmed");


  g2->SetMarkerStyle(34);
  g2->SetLineWidth(3);
  g2->SetLineColor(5);
  g3->SetMarkerStyle(34);
  g3->SetLineWidth(3);
  g3->SetLineColor(3);




  TString filename = Form("freq_mag_33_43_avg_trimmed.png");
  g2->Draw();
  g3->Draw("same");
  leg = new TLegend(0.7,0.5,0.9,0.7);
  leg->AddEntry(g2,"33");
  leg->AddEntry(g3,"43");
  leg->Draw("same");
  c1->SaveAs(filename);


// take the ratio
  TH1D *hrat= new TH1D("","",100,-20,20);
  int npoints = g2->GetN();
  double *y2=g2->GetY();
  double *y3=g3->GetY();
  double *x=g2->GetX();
  for(int i=0;i<npoints; i++){
    y2[i]=y2[i]/y3[i];
    hrat->Fill(y2[i]);
  }

  hrat->Draw();
  c1->SaveAs("ratio_hist_33_43_trimmed.png");
  TGraph *grat= new TGraph(npoints,x,y2);
  grat->Draw("AL");
  c1->SaveAs("ratio_graph_33_43_trimmed.png");
}


