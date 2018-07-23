// this file runs all of the macros that were originally used in early 2018 by Keith McBride to generate trigger efficiency scan plots like snr vs attenuation and trig eff vs snr, etc. 

/************************************************************************************/
// first run trig_eff_makevalues.C which is below:

// This will find the number of entries in an attenuation output of trigger efficiency scan of l3trigpattern in the header file that are greater than zero and then divide by the number of entries. 
//Thus this calculates the triggerefficiency. 
//
#include <iostream>
#include <fstream>
using namespace std;

void plot_all()
{
  trig_eff_makevalues();
  plot_trig_eff_att_graph();
  snr_att_makerootfiles();
  plot_snr_att_graphs();
  plot_trig_eff_snr();
}

void trig_eff_makevalues()
{
  cout << "starting " << endl;
  ofstream outfile;
  outfile.open("trig_eff_att.txt");
  // opening file to write hists to.
  TFile * _file_out = new TFile("l3_att.root","RECREATE");

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
    filename = Form("/home/keith/trigscan_tuffresponses_debugging_07_23_18/icemc/efficiencyScanPulseAtAntennaNewTrigger/Att%ddb/SimulatedAnitaHeadFile1.root",att);
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


/************************************************************************************/
// second run pot_trig_eff_att_graph.C
// This macro reads in the output from trig_eff_makevalues.C to plot the trigger effeciency versus attenuation

void plot_trig_eff_att_graph()
{
  ifstream infile;
  infile.open("trig_eff_att.txt");
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

/************************************************************************************/
// third, run snr_att_makerootfiles.C 
// This will plot the snr vs attenuation in input file and is used to help do the trigger efficiency scan of ANITA-4 

void snr_att_makerootfiles()
{
  cout << "starting " << endl;

  // opening file to write hists to.
  TFile * _file_out = new TFile("snr_att.root","RECREATE");

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
    filename = Form("/home/keith/trigscan_tuffresponses_debugging_07_23_18/icemc/efficiencyScanPulseAtAntennaNewTrigger/Att%ddb/SimulatedAnitaTruthFile1.root",att);
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

/************************************************************************************/
//fourth run plot_snr_att_graqphs.C
// This will plot the snr vs attenuation in input file and is used to help do the trigger efficiency scan of ANITA-4 

void plot_snr_att_graphs()
{
  cout << "starting " << endl;

  // opening file to write profiles to.
  TFile * _file_out = new TFile("snr_att_graphs.root","RECREATE");

  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);

// load in the snr and att files (1 for each attenuation)

  TString filename = Form("snr_att.root");
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

/************************************************************************************/

//lastly, run plot_trig_eff_snr.C

// This macro reads in the outputs from other macros to plot the trigger effeciency versus snr at trigger

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
  TString filename = Form("snr_att_graphs.root");
  TFile * _file0= TFile::Open(filename);
  g0=(TGraph*)_file0->Get("snr_att_tV");
  filename = Form("trig_att_graph.root");
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



