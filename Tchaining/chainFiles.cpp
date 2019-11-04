
int chainFiles(){

  TChain chain("T");

  Int_t start = 1974;
  Int_t stop =  1984;

  for(Int_t run=start; run<stop+1 ; run++)
    {
      if(!gSystem->AccessPathName(Form("/work/hallc/shms/wmhenry/f2/ROOTfiles/hms_replay_production_%i_-1.root",run)))
      {
	chain.Add(Form("/work/hallc/shms/wmhenry/f2/ROOTfiles/hms_replay_production_%i_-1.root",run));
	cout<<Form("/work/hallc/shms/wmhenry/f2/ROOTfiles/hms_replay_production_%i_-1.root",run)<<endl;
      }
    }



  chain.Draw("H.cal.etottracknorm>>h1(100,0,2)");
  chain.Merge("/work/hallc/shms/wmhenry/f2/ROOTfiles/hms1974-1984.root");
  return 0;
}
