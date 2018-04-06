// This macro reads in the outputs from other macros to plot the trigger effeciency versus snr at trigger

#include <iostream>
#include <fstream>

using namespace std;

void plot_trig_eff_snr()
{
//  double trig[19];
//  double att[19];
//  double snr[19];
  TGraph *g0;
  TGraph *g1;
  TCanvas *c= new TCanvas("c", "c", 800, 800);
// data stuff
// file is .txt with snr as one column then eff as second column
//  ifstream infile;
//  infile.open("");
  TGraph *g_data= new TGraph("snr_eff_data_elog691.txt");
//
// end data stuff


  TFile * _file_out = new TFile("trig_snr_graph.root","RECREATE");
// read in the plots necessary
// files are
  TString filename = Form("/home/keith/trig_eff_scan_code/snr_att_graphs_2.root");
  TFile * _file0= TFile::Open(filename);
  g0=(TGraph*)_file0->Get("snr_att_tV");
  filename = Form("/home/keith/trig_eff_scan_code/trig_att_graph.root");
  TFile * _file1= TFile::Open(filename);
  g1=(TGraph*)_file1->Get("trigeff_att");
  
  
  TGraph *g = new TGraph(19, g0->GetY(),g1->GetY());

//  g->SetMarkerStyle(34);
  g->SetLineColor(4);
  g->SetLineWidth(3);
  g->SetTitle("Trigger Efficiency vs SNR at Trigger");
//  g_data->SetMarkerStyle(32);
  g_data->SetLineColor(2);
g_data->SetLineWidth(3);

  g->Draw();
  g_data->Draw("same");

  leg = new TLegend(0.7,0.5,0.9,0.7);

  leg->AddEntry(g_data,"Data");
  leg->AddEntry(g,"Simulation");
  leg->Draw("same");

  c->SaveAs("trig_eff_vs_snr.png");

  _file_out->cd();
  g->Write("trigeff_snr");
  g_data->Write("trigeff_snr_data");
  _file_out->Close();


}
