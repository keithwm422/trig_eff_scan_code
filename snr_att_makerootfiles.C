// This will plot the snr vs attenuation in input file and is used to help do the trigger efficiency scan of ANITA-4 
#include <iostream>
#include <fstream>
using namespace std;

void snr_att_makerootfiles()
{
  cout << "starting " << endl;

  // opening file to write hists to.
  TFile * _file_out = new TFile("snr_att_2.root","RECREATE");

  TH1D *h_dH = new TH1D ("MaxSNR digitizer H","MaxSNR digitizer H", 60, 0.0, 12.0);
  TH1D *h_dV = new TH1D ("MaxSNR digitizer V","MaxSNR digitizer V", 60, 0.0, 12.0);
  TH1D *h_tH = new TH1D ("MaxSNR trigger H","MaxSNR trigger H", 60, 0.0, 12.0);
  TH1D *h_tV = new TH1D ("MaxSNR trigger V","MaxSNR trigger V", 60, 0.0, 12.0);
  TTree *t;
  TruthAnitaEvent* event= NULL;

  double maxsnr_dH=0.;
  double maxsnr_dV=0.;
  double maxsnr_tH=0.;
  double maxsnr_tV=0.;
  TString filename;
  TFile *_file0;
  for(int att=25; att<44; att++){
    filename = Form("/home/keith/icemc/efficiencyScanPulseAtAntennaNewTrigger/Att%ddb/SimulatedAnitaTruthFile1.root",att);
    _file0= TFile::Open(filename);
    t=(TTree*)_file0->Get("truthAnitaTree");
    t->SetBranchAddress("truth",&event);
    cout << "Found Tree" << endl;

// loop over all events (-n 100)

    for(int i=0;i<100;i++){
      t->GetEntry(i);
//    cout << "getting entry " << i << " trigV is " << maxsnr_tV << endl;
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
     _file_out->cd();
    h_dH->Write(Form("maxsnr_dH%d",att));
    h_dV->Write(Form("maxsnr_dV%d",att));
    h_tH->Write(Form("maxsnr_tH%d",att));
    h_tV->Write(Form("maxsnr_tV%d",att));
    h_dH->Reset();
    h_dV->Reset();
    h_tH->Reset();
    h_tV->Reset();
    _file0->cd();
    _file0->Close();


  }

  _file_out->Close();
}


