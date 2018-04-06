// This will find the number of entries in an attenuation output of trigger efficiency scan of l3trigpattern in the header file that are greater than zero and then divide by the number of entries. 
//Thus this calculates the triggerefficiency. 
//
#include <iostream>
#include <fstream>
using namespace std;

void trig_eff_makevalues()
{
  cout << "starting " << endl;
  ofstream outfile;
  outfile.open("trig_eff_att_2.txt");
  // opening file to write hists to.
  TFile * _file_out = new TFile("l3_att_2.root","RECREATE");

  TH1D *l_trig = new TH1D ("l3 Trig Pattern","l3 Trig Pattern", 10000, -100.0, 100000);
  l_trig->SetLineWidth(3);
//  TH1D *l_dV = new TH1D ("MaxSNR digitizer V","MaxSNR digitizer V", 60, 0.0, 12.0);
//  TH1D *l_tH = new TH1D ("MaxSNR trigger H","MaxSNR trigger H", 60, 0.0, 12.0);
//  TH1D *l_tV = new TH1D ("MaxSNR trigger V","MaxSNR trigger V", 60, 0.0, 12.0);
  TTree *t;
//  TruthAnitaEvent* event= NULL;
  int counter=0;
  TString filename;
  TFile *_file0;
  RawAnitaHeader* h = NULL;
  for(int att=25; att<44; att++){
    filename = Form("/home/keith/icemc/efficiencyScanPulseAtAntennaNewTrigger/Att%ddb/SimulatedAnitaHeadFile1.root",att);
    _file0= TFile::Open(filename);
    t=(TTree*)_file0->Get("headTree");
    t->SetBranchAddress("header",&h);
    cout << "Found Tree" << endl;
    counter=0;
// loop over all events (-n 100)

    for(int i=0;i<100;i++){
      t->GetEntry(i);
//    cout << "getting entry " << i << " trigV is " << maxsnr_tV << endl;
// load vars
      //fill hists
      if(h->l3TrigPattern>0){
        counter++;
      }
      l_trig->Fill(h->l3TrigPattern);
    }
    
    _file_out->cd();
    l_trig->Write(Form("l3trig%d",att));
    l_trig->Reset();
    _file0->cd();
    _file0->Close();
    outfile << (double)(counter)/100.0 << " " << att << endl;

  }
  outfile.close();
  _file_out->Close();
}


