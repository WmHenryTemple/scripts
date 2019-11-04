//tr->Draw("P.dc.y_fp:P.dc.x_fp>>h1(100,-50,50,100,-50,50)","","COLZ")
#include "labelWkine.cpp"


void epCalo(Int_t run=3021){

  gStyle->SetStatX(.9);
  //  gStyle->SetPalette(62);

  Int_t nbins=100;
  Float_t zDrift=300;
  Double_t etottracknorm, x_fp, xp_fp, y_fp, yp_fp, delta, ngc,prnorm; 
  Double_t x,y,xp,yp, ntrack, beta;
  TString froot;
  froot = Form("/lustre/expphy/cache/hallc/E12-10-002/abishek/realpass-2-shms-data/shms_replay_production_%d_-1.root",run);
  TFile *f=new TFile(froot);
  f->Print();
  TTree *tr=(TTree*)f->Get("T");

  tr->SetBranchAddress("P.cal.etracknorm", &etottracknorm);
  tr->SetBranchAddress("P.dc.x_fp", &x_fp);
  tr->SetBranchAddress("P.dc.xp_fp", &xp_fp);
  tr->SetBranchAddress("P.dc.y_fp", &y_fp);
  tr->SetBranchAddress("P.dc.yp_fp", &yp_fp);
  tr->SetBranchAddress("P.ngcer.npeSum", &ngc);
  tr->SetBranchAddress("P.gtr.dp", &delta);
  tr->SetBranchAddress("P.cal.eprtracknorm", &prnorm);
  tr->SetBranchAddress("P.dc.ntrack", &ntrack);
  tr->SetBranchAddress("P.gtr.beta", &beta);

  TH1F *hcal = new TH1F("hcal", "Energy in Calorimeter (etottracknorm)", 150, 0.000, 1.5);
  TH2F *xy_cal= new TH2F("xy_cal", "Position at Calorimeter", nbins, -70, 70,nbins,-68,68);
  TH2F * xy_calNorm=new TH2F("xy_calNorm", "E/p at Calorimeter", nbins, -70, 70,nbins,-68,68);
  TH2F * xy_calWt=new TH2F("xy_calWt", "Wt at Calorimeter", nbins, -70, 70,nbins,-68,68);

  hcal->GetXaxis()->SetTitle("P.cal.etottracknorm");
  xy_cal->GetXaxis()->SetTitle("Proj. Y Pos.");
  xy_cal->GetYaxis()->SetTitle("Proj. X Pos.");
  xy_calNorm->GetXaxis()->SetTitle("Proj. Y Pos.");
  xy_calNorm->GetYaxis()->SetTitle("Proj. X Pos.");
  xy_calWt->GetXaxis()->SetTitle("Proj. Y Pos.");
  xy_calWt->GetYaxis()->SetTitle("Proj. X Pos.");

  Int_t nEvents = tr->GetEntries();
    for (Int_t iEvent = 0; iEvent < nEvents; iEvent++) {
    //          for (Int_t iEvent = 0; iEvent < 5000; iEvent++) {

    if (iEvent%1000==0)cout<<iEvent<<endl;
    tr->GetEntry(iEvent);
    //    if(ngc > 0 && delta > -10 && delta < 22 && prnorm>0.04 ){

    if(etottracknorm>0 && ngc > 10 && delta > -15 && delta < 27 && ntrack==1 && abs(1-beta)<0.5){
    hcal->Fill(etottracknorm);
    x=x_fp+xp_fp*zDrift;
    y=y_fp+yp_fp*zDrift;
    xy_cal->Fill(y,x);
    xy_calWt->Fill(y,x,etottracknorm);
    xy_calNorm->Divide(xy_calWt,xy_cal);
    }
  }
  TCanvas *c1=new TCanvas("c1","xy_totNorm",1);
  //  c1->Divide(2,1);
  //  c1->cd(1);
  //  hcal->Draw();
  //  c1->cd(2);
  xy_calNorm->GetZaxis()->SetRangeUser(0.1,1.3);
  xy_calNorm->Draw("COLZ");
  TPaveText *lab=labelWkine(run,0.12,.36,0.25,0.64);

  // *************Draw shower blocks **************
  Int_t nRows=16;
  Int_t nCols=14;
  Double_t thkRow=9;
  Double_t startRow=-thkRow*nRows/2.;
  Double_t startCol=-thkRow*nCols/2;
  TLine *trw[nRows];
  TLine *tc[nCols];
  for (Int_t i=0;i<=nRows;i++)
    {
      Double_t y= startRow+i*thkRow;
      //   tr[i]=new TLine(-63,y,63,y);
      trw[i]=new TLine(startCol,y,startCol+thkRow*nCols,y);
      trw[i]->SetLineColor(kRed-3);
      trw[i]->Draw("same");
    } 
  for (Int_t i=0;i<=nCols;i++)
    {
      Double_t x= startCol+i*thkRow;
      tc[i]=new TLine(x,startRow,x,startRow+thkRow*nRows);
      tc[i]->SetLineColor(kRed-3);
      tc[i]->Draw("same");
    } 
  // *********Done drawing shower blocks **************
  lab->Draw("same BR");

  c1->Print(Form("PDFs/run%d.pdf",run));
 
return;
}
