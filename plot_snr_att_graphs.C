// This will plot the snr vs attenuation in input file and is used to help do the trigger efficiency scan of ANITA-4 
#include <iostream>
#include <fstream>
using namespace std;

void plot_snr_att_graphs()
{
  cout << "starting " << endl;

  // opening file to write profiles to.
  TFile * _file_out = new TFile("snr_att_graphs_2.root","RECREATE");

  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);

// load in the snr and att files (1 for each attenuation)

  TString filename = Form("/home/keith/trig_eff_scan_code/snr_att_2.root");
  TFile * _file0= TFile::Open(filename);
  TString histname_dH;
  TString histname_dV;
  TString histname_tH;
  TString histname_tV;
  TH1D *h_dH;
  TH1D *h_dV;
  TH1D *h_tH;
  TH1D *h_tV;
  cout << "Found File" << endl;
  double x_att[19];
  double y_snr_dH[19];
  double y_snr_dV[19];
  double y_snr_tH[19];
  double y_snr_tV[19];
// loop over all events (-n 100)

  for(int att=25;att<44;att++){
    histname_dH=Form("maxsnr_dH%d",att);
    h_dH=(TH1D*)_file0->Get(histname_dH);
    y_snr_dH[att-25]=h_dH->GetMean(1);

    histname_dV=Form("maxsnr_dV%d",att);
    h_dV=(TH1D*)_file0->Get(histname_dV);
    y_snr_dV[att-25]=h_dV->GetMean(1);

    histname_tH=Form("maxsnr_tH%d",att);
    h_tH=(TH1D*)_file0->Get(histname_tH);
    y_snr_tH[att-25]=h_tH->GetMean(1);

    histname_tV=Form("maxsnr_tV%d",att);
    h_tV=(TH1D*)_file0->Get(histname_tV);
    y_snr_tV[att-25]=h_tV->GetMean(1);

    x_att[att-25]=att;
  }

// TGraphs
  TGraph *gdH= new TGraph(19,x_att,y_snr_dH);
  TGraph *gdV= new TGraph(19,x_att,y_snr_dV);
  TGraph *gtH= new TGraph(19,x_att,y_snr_tH);
  TGraph *gtV= new TGraph(19,x_att,y_snr_tV);

  // write out the graphs to rootfile
  _file_out->cd();
  gdH->Write("snr_att_dH");
  gdV->Write("snr_att_dV");
  gtH->Write("snr_att_tH");
  gtV->Write("snr_att_tV");


  _file_out->Close();
}


