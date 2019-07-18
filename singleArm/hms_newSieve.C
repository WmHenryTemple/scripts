 void hms_newSieve(){
 
   //Declare Variables
  TCanvas *c1=new TCanvas("c1","Single Arm Tree",800,600);
  TFile *f1;
  TFile *f2;
  TTree *tr1;
  TTree *tr2;
  Float_t hsdelta, hsdeltai;
  //Get File and Trees
 f1=new TFile("/work/hallc/shms/wmhenry/mc-single-arm/worksim/hms_run8401_b4.root");
 f2=new TFile("/work/hallc/shms/wmhenry/mc-single-arm/worksim/hms_run8401_af.root");
 tr1=(TTree*)f1->Get("h1");
 tr2=(TTree*)f2->Get("h1");


 //Make histograms
 TH1F *h1x=new TH1F("h1x","Target dx/dz",1000,-.1,.1);
 TH1F *h2x=new TH1F("h2x","Target dx/dz",1000,-.1,.1);

 TH1F *h1y=new TH1F("h1y","Target dy/dz",1000,-.1,.1);
 TH1F *h2y=new TH1F("h2y","Target dy/dz",1000,-.1,.1);

 TH1F *h1d=new TH1F("h1d","delta",200,-20,20);
 TH1F *h2d=new TH1F("h2d","delta",200,-20,20);

 TH1F *res1=new TH1F("res1","Momentum Resolution",200,-.3,.3);
 TH1F *res2=new TH1F("res2","Momentum Resolution",200,-.3,.3);

 //Fill histograms
 tr1->Project("h1x","hsxptari","","");
 tr2->Project("h2x","hsxptari","","");

 tr1->Project("h1y","hsyptari","","");
 tr2->Project("h2y","hsyptari","","");

 tr1->Project("h1d","hsdelta","","");
 tr2->Project("h2d","hsdelta","","");


 Float_t temp;
 Int_t nentries= tr1->GetEntries();

 tr1->SetBranchAddress("hsdelta",&hsdelta);
 tr1->SetBranchAddress("hsdeltai",&hsdeltai);
 for(Int_t i=0;i<nentries;i++){
   tr1->GetEntry(i);
   temp=(hsdelta-hsdeltai)/hsdeltai;
   res1->Fill(temp);
 }

 nentries= tr2->GetEntries();

 tr2->SetBranchAddress("hsdelta",&hsdelta);
 tr2->SetBranchAddress("hsdeltai",&hsdeltai);
 for(Int_t i=0;i<nentries;i++){
   tr2->GetEntry(i);
   temp=(hsdelta-hsdeltai)/hsdeltai;
   res2->Fill(temp);
 }
 //xpfp
 h1x->GetXaxis()->SetTitle("psxpfp"); 
 h1x->GetYaxis()->SetTitle("Counts"); 
 h2x->GetXaxis()->SetTitle("psxpfp"); 
 h2x->GetYaxis()->SetTitle("Counts"); 

 h1x->SetLineColor(kRed);

 h2x->SetLineColor(kBlack);
 h2x->SetFillStyle(1001);
 h2x->SetFillColor(kGray+1);

 //ypfp
 h1y->GetXaxis()->SetTitle("psypfp"); 
 h1y->GetYaxis()->SetTitle("Counts"); 
 h2y->GetXaxis()->SetTitle("psypfp"); 
 h2y->GetYaxis()->SetTitle("Counts"); 

 h1y->SetLineColor(kRed);
 h2y->SetLineColor(kBlack);
 h2y->SetFillStyle(1001);
 h2y->SetFillColor(kGray+1);

 //delta
 h1d->GetXaxis()->SetTitle("delta (recon.)"); 
 h1d->GetYaxis()->SetTitle("Counts"); 
 h2d->GetXaxis()->SetTitle("delta (recon)"); 
 h2d->GetYaxis()->SetTitle("Counts"); 

 h1d->SetLineColor(kRed);
 h2d->SetLineColor(kBlack);
 h2d->SetFillStyle(1001);
 h2d->SetFillColor(kGray+1);

 //delta resol.
 res1->GetXaxis()->SetTitle("(delta-deltai)/deltai"); 
 res1->GetYaxis()->SetTitle("Counts"); 
 res2->GetXaxis()->SetTitle("(delta-deltai)/deltai"); 
 res2->GetYaxis()->SetTitle("Counts"); 

 res1->SetLineColor(kRed);
 res2->SetLineColor(kBlack);
 res2->SetFillStyle(1001);
 res2->SetFillColor(kGray+1);

 TLegend *leg=new TLegend(.65,.75,.98,.9);
 c1->Divide(2,2);

 c1->cd(1);
 h1x->Draw();
 h2x->Draw("same");
 h1x->Draw("same");
 leg->AddEntry("h1x","Sieve: One Plane","lf");
 leg->AddEntry("h2x","Sieve: Two Planes","lf");
 leg->Draw();

 c1->cd(2);
 h1y->Draw();
 h2y->Draw("same");
 h1y->Draw("same");
 leg->Draw();

 c1->cd(3);
 h1d->Draw();
 h2d->Draw("same");
 h1d->Draw("same");
 leg->Draw();
 c1->cd(4);
 res1->Draw();
 gPad->Update();


  //collect stat of the first histogram (h1)
  TPaveStats *tps1 = (TPaveStats*) res1->FindObject("stats");
  tps1->SetName("Old Sieve");
  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();


 res2->Draw();
 gPad->Update();
 // collect stat of the second histogram (h2) 
 
 
 TPaveStats *tps2 = (TPaveStats*) res2->FindObject("stats");
 tps2->SetName("New Sieve");
 tps2->SetTextColor(kRed);
 tps2->SetLineColor(kRed);
 tps2->SetX1NDC(X1);
 tps2->SetX2NDC(X2);
 tps2->SetY1NDC(Y1-(Y2-Y1));
 tps2->SetY2NDC(Y1);
 
 res1->Draw();
 res2->Draw("same");
 res1->Draw("same");
 tps1->Draw("same");
 tps2->Draw("same");
 
}


