//tr->Draw("P.dc.y_fp:P.dc.x_fp>>h1(100,-50,50,100,-50,50)","","COLZ")
#include "labelWkine.cpp"


void geomCut(Int_t run=3021){

//========= Macro generated from object: cutBot/Graph
//========= by ROOT version6.14/06
   
   TCutG *cutBot = new TCutG("cutBot",7);
   cutBot->SetVarX("P.dc.y_fp+P.dc.yp_fp*292.64");
   cutBot->SetVarY("P.dc.x_fp+P.dc.xp_fp*292.64");
   cutBot->SetTitle("Graph");
   cutBot->SetLineColor(kBlue);      
   cutBot->SetPoint(0,0.752149,24.1316);
   cutBot->SetPoint(1,55.1576,-28.1842);
   cutBot->SetPoint(2,54.9069,-63.1842);
   cutBot->SetPoint(3,-53.904,-62.4474);
   cutBot->SetPoint(4,-53.6533,-30.7632);
   cutBot->SetPoint(5,1.25358,23.7632);
   cutBot->SetPoint(6,0.752149,24.1316);
   cutBot->Draw("");

//========= Macro generated from object: cutTL/Graph
//========= by ROOT version6.14/06
   
   TCutG *cutTL = new TCutG("cutTL",8);
   cutTL->SetVarX("P.dc.y_fp+P.dc.yp_fp*292.64");
   cutTL->SetVarY("P.dc.x_fp+P.dc.xp_fp*292.64");
   cutTL->SetTitle("Graph");
   cutTL->SetLineColor(kRed);
   cutTL->SetPoint(0,-42.1203,-17.8684);
   cutTL->SetPoint(1,-42.1203,-17.8684);
   cutTL->SetPoint(2,-13.5387,17.5);
   cutTL->SetPoint(3,-24.0688,63.1842);
   cutTL->SetPoint(4,-52.9011,34.4474);
   cutTL->SetPoint(5,-54.4054,0.552632);
   cutTL->SetPoint(6,-42.8725,-16.7632);
   cutTL->SetPoint(7,-42.1203,-17.8684);
   cutTL->Draw("");

//========= Macro generated from object: cutTR/Graph
//========= by ROOT version6.14/06
   
   TCutG *cutTR = new TCutG("cutTR",7);
   cutTR->SetVarX("P.dc.y_fp+P.dc.yp_fp*292.64");
   cutTR->SetVarY("P.dc.x_fp+P.dc.xp_fp*292.64");
   cutTR->SetTitle("Graph");
   cutTR->SetLineColor(kGreen);
   cutTR->SetPoint(0,-2.25645,29.2895);
   cutTR->SetPoint(1,33.596,-6.07895);
   cutTR->SetPoint(2,55.9097,14.5526);
   cutTR->SetPoint(3,8.77507,64.6579);
   cutTR->SetPoint(4,-3.51003,47.7105);
   cutTR->SetPoint(5,-2.50716,28.9211);
   cutTR->SetPoint(6,-2.25645,29.2895);
   cutTR->Draw("");



  
   gStyle->SetStatX(.9);
   gStyle->SetPalette(62);

  Int_t nbins=100;
  Float_t zDrift=300;
  Double_t etottracknorm, x_fp, xp_fp, y_fp, yp_fp, delta, ngc,prnorm; 
  Double_t x,y,xp,yp, ntrack, beta,p ;
  TString froot, name, title;
  TH1F *myhist[16];


  
  TFile *f=new TFile("shms_replay_production_3021_-1.root");
  f->Print();
  TTree *tr=(TTree*)f->Get("T");

  tr->SetBranchAddress("P.cal.etracknorm", &etottracknorm);
  tr->SetBranchAddress("P.dc.x_fp", &x_fp);
  tr->SetBranchAddress("P.dc.xp_fp", &xp_fp);
  tr->SetBranchAddress("P.dc.y_fp", &y_fp);
  tr->SetBranchAddress("P.dc.yp_fp", &yp_fp);
  tr->SetBranchAddress("P.ngcer.npeSum", &ngc);
  tr->SetBranchAddress("P.gtr.dp", &delta);
  tr->SetBranchAddress("P.gtr.p", &p);
  tr->SetBranchAddress("P.cal.eprtracknorm", &prnorm);
  tr->SetBranchAddress("P.dc.ntrack", &ntrack);
  tr->SetBranchAddress("P.gtr.beta", &beta);

  TH2F *xy_cal= new TH2F("xy_cal", "Position at Calorimeter", nbins, -70, 70,nbins,-68,68);
  TH2F * xy_calWt=new TH2F("xy_calWt", "Wt at Calorimeter", nbins, -70, 70,nbins,-68,68);
  for (Int_t k=0;k<16;k++)
    {
      name=Form("h%d",k);
      title=name;      
      if(k<8)
	{
	  myhist[k]=new TH1F(name,title,100,-40,40);
	}
      else
	{
	  myhist[k]=new TH1F(name,title,100,-0.5,0.5);
	}

      if(k%4==0)myhist[k]->SetLineColor(kRed);
      if(k%4==1)myhist[k]->SetLineColor(kYellow);
      if(k%4==2)myhist[k]->SetLineColor(kBlue);
      if(k%4==3)myhist[k]->SetLineColor(kGreen);      
    }
  

  TCut goodE="P.cal.etracknorm>0 &&  P.ngcer.npeSum>10 && P.dc.ntrack==1 &&"
    "P.gtr.dp>-10 && P.gtr.dp < 22 && abs(1-P.gtr.beta)<0.5 &&"
    "P.gtr.p>3.4 && P.gtr.p<4.4";

  Int_t nEvents = tr->GetEntries();
  nEvents=50000;


   for (Int_t iEvent = 0; iEvent < nEvents; iEvent++)
    {
    //          for (Int_t iEvent = 0; iEvent < 5000; iEvent++) {

    if (iEvent%1000==0)cout<<iEvent<<endl;
    tr->GetEntry(iEvent);
    if(etottracknorm>0 && ngc > 10 && delta > -10 && delta < 22 && ntrack==1 && abs(1-beta)<0.5 && p>3.4 && p<4.4)
      {
	x=x_fp+xp_fp*zDrift;
	y=y_fp+yp_fp*zDrift;
	xy_cal->Fill(y,x);
	xy_calWt->Fill(y,x,p);
      }
    }
  xy_calWt->Divide(xy_cal);

  TCanvas *c2=new TCanvas("c2","DC Variables with Cuts");
  c2->Divide(3,2);
  c2->cd(1);
  xy_calWt->Draw("COLZ");
  xy_calWt->GetZaxis()->SetRangeUser(3,5);
  cutTR->Draw("same");


  cutTL->Draw("same");
  cutBot->Draw("same");
  //    tr->Draw("P.dc.x_fp:P.dc.xp_fp","cutTL || cutTR || cutBot");
  
  c2->cd(4);
  xy_cal->Draw();
  cutTR->Draw("same");
  cutTL->Draw("same");
  cutBot->Draw("same");
  
  c2->cd(2);
  gPad->SetLogy();
  tr->Draw("P.dc.x_fp>>h1", goodE && "cutTL" || goodE && "cutTR" || goodE && "cutBot");    
  tr->Draw("P.dc.x_fp>>h2",goodE && "cutTL","same");
  tr->Draw("P.dc.x_fp>>h3",goodE && "cutTR","same");
  tr->Draw("P.dc.x_fp>>h4",goodE && "cutTR","same");  
  
  c2->cd(3);
  gPad->SetLogy();  
  tr->Draw("P.dc.y_fp>>h5",goodE && "cutTL" || goodE && "cutTR" || goodE && "cutBot");    
  tr->Draw("P.dc.y_fp>>h6",goodE && "cutTL","same");
  tr->Draw("P.dc.y_fp>>h7",goodE && "cutTR","same");
  tr->Draw("P.dc.y_fp>>h8",goodE && "cutTR","same");  
  
  c2->cd(5);
  gPad->SetLogy();  
  tr->Draw("P.dc.xp_fp>>h9",goodE && "cutTL" || goodE && "cutTR" || goodE && "cutBot");    
  tr->Draw("P.dc.xp_fp>>h10",goodE && "cutTL","same");
  tr->Draw("P.dc.xp_fp>>h11",goodE && "cutTR","same");
  tr->Draw("P.dc.xp_fp>>h12",goodE && "cutTR","same");  

  c2->cd(6);
  gPad->SetLogy();  
  tr->Draw("P.dc.yp_fp>>h13",goodE && "cutTL" || goodE && "cutTR" || goodE && "cutBot");    
  tr->Draw("P.dc.yp_fp>>h14",goodE && "cutTL","same");
  tr->Draw("P.dc.yp_fp>>h15",goodE && "cutTR","same");
  tr->Draw("P.dc.yp_fp>>h16",goodE && "cutTR","same");  


  for(Int_t j=0;j<2;j++)
      {
	Int_t np=j*3+1; //1st and forth
	c2->cd(np);
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
      }

    
return;
}
