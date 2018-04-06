// This will produce root files that have the Ch1 pulses from ANITA-4 trig eff scans that are trimmed to ignore the timing before x seconds
#include <iostream>
#include <fstream>
using namespace std;

void trim_Avg_Ch1_pulses()
{
  cout << "starting " << endl;

  //opening files to save
    TFile * _file_out2 = new TFile("TriggerEfficiencyScanPulser_anita4_33dB_avg_trimmed.root","RECREATE");
    TFile * _file_out3 = new TFile("TriggerEfficiencyScanPulser_anita4_43dB_avg_trimmed.root","RECREATE");

  // opening files to trim.
  TCanvas *c1 = new TCanvas ("C1","c1", 800,800);
  TFile * _file2= TFile::Open("/home/keith/icemc_trig_scan_tests/TriggerEfficiencyScanPulser_anita4_33dB_avg.root");
  TFile * _file3= TFile::Open("/home/keith/icemc_trig_scan_tests/data/TriggerEfficiencyScanPulser_anita4_43dB_avg.root");

  _file2->cd();
  g2 = (TGraph*)_file2->Get("Phisector_3_33dBCh1");
  _file3->cd();
  g3 = (TGraph*)_file3->Get("Phisector_3_43dBCh1");


  g2->SetMarkerStyle(34);
  g2->SetLineWidth(3);
  g2->SetLineColor(5);
  g3->SetMarkerStyle(34);
  g3->SetLineWidth(3);
  g3->SetLineColor(3);

// do the trimming and plot, then resave if correct in root files

  int npoints = g2->GetN();
  double *xpoints= g2->GetX();
  double *ypoints2= g2->GetY();
  double *ypoints3= g3->GetY();
  // make xpoints_new which are after certain fraction of xpoints has been passsed over.
  // make ypoints_new which are values after certain fraction are passed over.
  double xpoints_new[npoints-454];
  double ypoints_new2[npoints-454];
  double ypoints_new3[npoints-454];
  cout << xpoints[0] << " " << xpoints[1] << " " << xpoints[2] << " " << npoints <<endl;

// step size is 2*10^-10 and there are 2494 steps from -3.08*10^-10 to 4.68*10^-7
  for (int i=0;i<npoints;i++){

    if(i>=454){
      xpoints_new[i-454]=((double)(i)-454.0)*2*TMath::Power(10.,-10.);
      ypoints_new2[i-454]=ypoints2[i];
      ypoints_new3[i-454]=ypoints3[i];
    }
    else{
      cout << "not shaving" << endl;
    }
  }
  *g2=TGraph(npoints-454,xpoints_new,ypoints_new2);
  *g3=TGraph(npoints-454,xpoints_new,ypoints_new3);
  TString filename = Form("graph1_33dB_trimmed.png");
  g2->Draw();
//  g3->Draw("same");
//  leg = new TLegend(0.7,0.5,0.9,0.7);
//  leg->AddEntry(g2,"33");
//  leg->AddEntry(g3,"43");
//  leg->Draw("same");
  c1->SaveAs(filename);
  _file_out2->cd();
  g2->Write("Phisector_3_33dBCh1_trimmed");
  _file_out2->Close();
  _file_out3->cd();
  g3->Write("Phisector_3_43dBCh1_trimmed");
  _file_out3->Close();

/*
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
  c1->SaveAs("ratio_hist_33_43.png");
  TGraph *grat= new TGraph(npoints,x,y2);
  grat->Draw("AL");
  c1->SaveAs("ratio_graph_33_43.png");
*/
}



