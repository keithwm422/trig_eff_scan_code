// This will plot the snr vs attenuation in input file and is used to help do the trigger efficiency scan of ANITA-4 
#include <iostream>
#include <fstream>
using namespace std;

void plot_snr_att()
{
  cout << "starting " << endl;

  // opening file to write profiles to.
  TFile * _file_out = new TFile("snr_att_profiles_2.root","RECREATE");

  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);

//TProfiles

  TProfile *p_snr_dH = new TProfile ("SNR dH vs Att","SNR dH vs Att", 25, 21, 46);
  TProfile *p_snr_dV = new TProfile ("SNR dV vs Att","SNR dV vs Att", 25, 21, 46);
  TProfile *p_snr_tH = new TProfile ("SNR tH vs Att","SNR tH vs Att", 25, 21, 46);
  TProfile *p_snr_tV = new TProfile ("SNR tV vs Att","SNR tV vs Att", 25, 21, 46);

  p_snr_dH->SetMarkerStyle(34);
  p_snr_dV->SetMarkerStyle(32);
  p_snr_tH->SetMarkerStyle(33);
  p_snr_tV->SetMarkerStyle(30);

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

  double meansnr_dH=0.;
  double meansnr_dV=0.;
  double meansnr_tH=0.;
  double meansnr_tV=0.;

// loop over all events (-n 100)

  for(int att=25;att<44;att++){
    histname_dH=Form("maxsnr_dH%d",att);
    h_dH=(TH1D*)_file0->Get(histname_dH);
    p_snr_dH->Fill(att,h_dH->GetMean(1));

    histname_dV=Form("maxsnr_dV%d",att);
    h_dV=(TH1D*)_file0->Get(histname_dV);
    p_snr_dV->Fill(att,h_dV->GetMean(1));

    histname_tH=Form("maxsnr_tH%d",att);
    h_tH=(TH1D*)_file0->Get(histname_tH);
    p_snr_tH->Fill(att,h_tH->GetMean(1));

    histname_tV=Form("maxsnr_tV%d",att);
    h_tV=(TH1D*)_file0->Get(histname_tV);
    p_snr_tV->Fill(att,h_tV->GetMean(1));

  }

  // write out the profiles to rootfile
  _file_out->cd();
  p_snr_dH->Write("snr_att_dH");
  p_snr_dV->Write("snr_att_dV");
  p_snr_tH->Write("snr_att_tH");
  p_snr_tV->Write("snr_att_tV");


  _file_out->Close();
}


