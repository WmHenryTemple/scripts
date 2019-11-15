int DataFrameAddBranch(){

    Float_t zDrift=292.64;
    
    ROOT::RDataFrame d("T","shms_replay_production_3021_-1.root");

    auto d_mod = d.Define("P_dc_x_calo","P.dc.x_fp + P.dc.xp_fp * 292.64").Define("P_dc_y_calo","P.dc.y_fp + P.dc.yp_fp * 292.64");    

    auto hx = d_mod.Histo1D(
			    {"hx","Position at Calo; X (cm); entries",100,-70,70},"P_dc_x_calo");

    auto hy = d_mod.Histo1D(
			    {"hy","Position at Calo; Y (cm); entries",100,-70,70},"P_dc_y_calo");

    auto hxy = d_mod.Histo2D(
			     {"hxy","Position at Calo; Y (cm); X (cm)",100,-70,70,100,-70,70},"P_dc_y_calo","P_dc_x_calo");    

    TCanvas *c=new TCanvas();
    c->Divide(2,1);
    c->cd(1);
    hy->Draw();
    hx->Draw("same");    
    hx->SetLineColor(kRed);
    c->cd(2);
    hxy->Draw("COLZ");
    c->Print("out.pdf");

    //    d_mod.Snapshot("newtree","shms3021.root");
    return 0;
}
