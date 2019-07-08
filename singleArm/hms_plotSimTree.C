 void hms_plotSimTree(){
  TCanvas *c1=new TCanvas("c1","Single Arm Tree",800,600);
  TFile *f1;
  TTree *tr1;

 f1=new TFile("/work/hallc/shms/wmhenry/mc-single-arm/worksim/hms_use_front_sieve.root");
 tr1=(TTree*)f1->Get("h1");

 TH2F *h1_1=new TH2F("h1_1","Focal Plane Position",1000,-50,50,1000,50,50);
 h1_1->GetXaxis()->SetTitle("X(cm) psxfp"); 
 h1_1->GetYaxis()->SetTitle("Y(cm) psyfp"); 

 TH2F *h4=new TH2F("h4","Sieve Hole Number",51,-0.5,50.5,50,-0.5,50.5);
 h4->GetXaxis()->SetTitle("X Hole "); 
 h4->GetYaxis()->SetTitle("Y Hole"); 

 TH2F *h5=new TH2F("h5","Sieve Position",4000,-20,20,2000,-10,10);
 h5->GetXaxis()->SetTitle("X(cm)"); 
 h5->GetYaxis()->SetTitle("Y(cm)"); 





 tr1->Project("h1_1","hsyfp:hsxfp","","COLZ");
 // tr1->Project("h4","ysnum:xsnum","","COLZ");
 // tr1->Project("h5","ysieve:xsieve","","COLZ");

 c1->Divide(3,2);
 c1->cd(1);
 h1_1->Draw("COLZ");

 c1->cd(4);
 h4->Draw("COLZ");

 c1->cd(5);
 h5->Draw("COLZ");

}
