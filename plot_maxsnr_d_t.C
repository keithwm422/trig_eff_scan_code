// This will plot the maxsnr from the truthAnitaTree's for digitizer and trigger and is used to help do the trigger efficiency scan of ANITA-4 
#include <iostream>
#include <fstream>
using namespace std;

void plot_maxsnr_d_t()
{
  cout << "starting " << endl;

  // opening file to write histograms to.
  TFile * _file_out = new TFile("maxsnr_hists.root","RECREATE");

  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);

  TFile * _file2= TFile::Open("/home/keith/icemc/effScan_1/SimulatedAnitaTruthFile1.root");

  TH1D *h_dH = new TH1D ("MaxSNR digitizer H","MaxSNR digitizer H", 20, 0.0, 0.10);
  TH1D *h_dV = new TH1D ("MaxSNR digitizer V","MaxSNR digitizer V", 20, 0.0, 0.10);
  TH1D *h_tH = new TH1D ("MaxSNR trigger H","MaxSNR trigger H", 20, 0.0, 0.10);
  TH1D *h_tV = new TH1D ("MaxSNR trigger V","MaxSNR trigger V", 20, 0.0, 0.10);

  h_dH->SetMarkerStyle(34);
  h_dH->SetLineWidth(3);
  h_dH->SetLineColor(5);
  h_dV->SetMarkerStyle(34);
  h_dV->SetLineWidth(3);
  h_dV->SetLineColor(4);
  h_tH->SetMarkerStyle(34);
  h_tH->SetLineWidth(3);
  h_tH->SetLineColor(2);
  h_tV->SetMarkerStyle(34);
  h_tV->SetLineWidth(3);
  h_tV->SetLineColor(3);



// normalise
//  double norm_1 = 1;
//  double scale_1 = norm_1/(h->Integral());
//  h->Scale(scale_1);


//  h->Draw("HIST");
//  c1->Draw();
//  TString filename = Form("RMS_andrew_sum.png");
//  c1->SaveAs(filename);

  _file2->cd();
  TTree *t=(TTree*)_file2->Get("truthAnitaTree");
  TruthAnitaEvent* event= NULL;
  t->SetBranchAddress("truth",&event);
//  t_A->SetBranchAddress("fVolts[108][260]",&fVolts);
// loop over all events

  cout << "Found Tree" << endl;

  double maxsnr_dH=0.;
  double maxsnr_dV=0.;
  double maxsnr_tH=0.;
  double maxsnr_tV=0.;

// loop over all events (-n 100)

  for(int i=0;i<100;i++){
    t->GetEntry(i);
    cout << "getting entry " << i << " trigV is " << maxsnr_tV << endl;
// load vars
    maxsnr_dH=event->maxSNRAtDigitizerH;
    maxsnr_dV=event->maxSNRAtDigitizerV;
    maxsnr_tH=event->maxSNRAtTriggerH;
    maxsnr_tV=event->maxSNRAtTriggerV;

    //fill hists
    h_dH->Fill(maxsnr_dH);
    h_dV->Fill(maxsnr_dV);
    h_tH->Fill(maxsnr_tH);
    h_tV->Fill(maxsnr_tV);
  }

/*
  double norm = 1;
  double scale = norm/(h_mean->Integral());
  h_mean->Scale(scale);
  scale = norm/(h_std->Integral());
  h_std->Scale(scale);
  scale = norm/(h_rms->Integral());
  h_rms->Scale(scale);
  scale = norm/(h_rms_1->Integral());
  h_rms_1->Scale(scale);
*/

// Save hists on separate plots

  TString filename = Form("maxsnr_dH.png");
  h_dH->Draw();
  c1->SaveAs(filename);
  filename = Form("maxsnr_dV.png");
  h_dV->Draw();
  c1->SaveAs(filename);
  filename = Form("maxsnr_tH.png");
  h_tH->Draw();
  c1->SaveAs(filename);
  filename = Form("maxsnr_tV.png");
  h_tV->Draw();
  c1->SaveAs(filename);

  // write out the histograms to rootfile
  _file_out->cd();
  h_dH->Write("maxsnr_dH");
  h_dV->Write("maxsnr_dV");
  h_tH->Write("maxsnr_tH");
  h_tV->Write("maxsnr_tV");
/*
  h_rms_1->SetAxisRange(0.0, 0.16, "Y");
  h_rms_1->Draw("HIST");
  h_rms->Draw("sameHIST");
  h->Draw("sameHIST");

  leg = new TLegend(0.7,0.5,0.9,0.7);

  leg->AddEntry(h,"data");
  leg->AddEntry(h_rms,"Simulation 0.8");
  leg->AddEntry(h_rms_1,"Simulation 0.9");
  leg->Draw("same");

  c1->Draw();
  filename = Form("RMS_fVolts_rms_B.png");
  c1->SaveAs(filename);


  h_std->Draw("HIST");
  c1->Draw();
  filename = Form("RMS_fVolts_std_B.png");
  c1->SaveAs(filename);
*/
  _file_out->Close();
}


