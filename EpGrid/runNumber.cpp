#include <iostream>
#include <iomanip>
#include "epCalo.cpp"

using namespace std;

int main(){

  TString testfile;
  cout << "Hello. Lets make some delta slices" << endl << endl;
  gDirectory->Delete();
  gStyle->SetOptStat(kFALSE);

  FILE *fp = fopen("runs.txt","r");  
  Int_t run;
  Int_t ncols; 
  Int_t nlines = 0; 
  Int_t i = 0;

  while (1) { 
    ncols = fscanf(fp,"%i",&run); 
    if (ncols < 0) break;
    cout << "SHMS run is: " << run << endl;     
    if(run%10==0)
      {    
	epCalo(run);
      }
  }
  return 0;
}

