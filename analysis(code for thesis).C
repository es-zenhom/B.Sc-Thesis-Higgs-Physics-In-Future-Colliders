
          ////******************////
  ///////The C++ code for the 14 TeV case ://///// 
         ////******************//// 
 //////////////

#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TH1.h"
#include "TLorentzVector.h"
#include <TMath.h>
#include <iostream>
#include "THStack.h"
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <TObject.h>
#include <Math/Vector4D.h>
#include <Math/Vector4Dfwd.h>
#include <iostream>
#include <algorithm>
#include <cmath>

// these files contents are included while loading the analysis.c code

void analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analysis.C
//      root> analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *inputfile = new TFile("tag_1_delphes_events.root", "READ");
   TFile *outputfile = new TFile("Output_14Tev.root", "UPDATE" );

// these two takes input from the tag_1_delphes root file which was created in first place from the delphes program and creates another file with the output of the code with name "Output_14Tev.root"


//""""""""""Now we will define the parametrs for the run and put the weights for the process""""""""

float cross_section = 20.88;  // The Cross-Section in fb
float N = 100000;    // Number of events
float DataLum = 300;		   //  Luminosity of data in fb^-1		
float MCLum = N / cross_section;  // Luminosity of Monte-Carlo  in fb^-1                    
float weight = DataLum / MCLum;       // Weight of the simulation process with repsect to data 



// ***************Now we will create the histograms*****************


 //Histogram for the Photon size

TH1I *PhotonSize = new TH1I("PhotonSize", "No. of Photons per event at 14 TeV ", 5, 0, 4);
   PhotonSize->GetXaxis()->SetTitle("Photons no.");
   PhotonSize->GetYaxis()->SetTitle("Events");

//Histograms for the Transverse Momentum PT and the Pseudorapidity eta
// photon 1 will be the leading photon and photon 2 will be the sub-leading photon

TH1D *Photon1_PT = new TH1D("Photon1_PT", "Transverse Momentum distribution for the leading photon at 14 TeV (LHC)", 100, 0., 800);
   Photon1_PT->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   Photon1_PT->GetYaxis()->SetTitle("Events");
   
   TH1D *Photon1_eta = new TH1D("Photon1_eta", "Pseudorapidity distribution for the leading photon at 14 TeV (LHC)", 80, -3.5, 3.5);
   Photon1_eta->GetXaxis()->SetTitle("eta"); 
   Photon1_eta->GetYaxis()->SetTitle("Events");

TH1D *Photon2_PT = new TH1D("Photon2_PT", "Transverse Momentum distribution for the sub_leading photon at 14 TeV (LHC)", 100, 0., 300);
   Photon2_PT->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   Photon2_PT->GetYaxis()->SetTitle("Events");
   
   TH1D *Photon2_eta = new TH1D("Photon2x_eta", "Pseudorapidity distribution for the sub_leading photon at 14 TeV (LHC)", 80, -3.5, 3.5);
   Photon2_eta->GetXaxis()->SetTitle("eta"); 
   Photon2_eta->GetYaxis()->SetTitle("Events");


// ****The histograms for the Mass and eta of the Higgs

TH1D *Higgs_Mass = new TH1D("Higgs_Mass", "Invariant mass for the Higgs Boson at 14 TeV", 100, 0., 200.);
   Higgs_Mass->GetXaxis()->SetTitle("Mass (GeV)");
   Higgs_Mass->GetYaxis()->SetTitle("Events");
   
   TH1D *Higgs_eta = new TH1D("Higgs_eta", "Pseudorapidity for the Higgs Boson at 14 TeV", 70, -3.5, 3.5);
   Higgs_eta->GetXaxis()->SetTitle("eta"); 
   Higgs_eta->GetYaxis()->SetTitle("Events");




   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

// THe TLorent Vector

TLorentzVector  photon0, photon1, h;
    

	photon0.SetPtEtaPhiE(Photon_PT[0], Photon_Eta[0], Photon_Phi[0], Photon_E[0]);
	photon1.SetPtEtaPhiE(Photon_PT[1], Photon_Eta[1], Photon_Phi[1], Photon_E[1]);		
	


// The Higgs is:

h=photon0 + photon1;


// Now we fill the histograms:

PhotonSize->Fill(Photon_size);
Photon1_PT->Fill(Photon_PT[0], weight);
Photon1_eta->Fill(Photon_Eta[0], weight);
Photon2_PT->Fill(Photon_PT[1], weight);
Photon2_eta->Fill(Photon_Eta[1], weight);
Higgs_Mass->Fill(h.M(), weight);
Higgs_eta->Fill(h.Eta(), weight);

   }
// the for loop is now ended


// Now we write the histograms
PhotonSize->Write();
Photon1_PT->Write();
Photon1_eta->Write();
Photon2_PT->Write();
Photon2_eta->Write();
Higgs_Mass->Write();
Higgs_eta->Write();

// Now we draw the histograms
PhotonSize->Draw();
Photon1_PT->Draw();
Photon1_eta->Draw();
Photon2_PT->Draw();
Photon2_eta->Draw();
Higgs_Mass->Draw();
Higgs_eta->Draw();


outputfile->Close();

} // end of loop member function






          ////******************////
  ///////The C++ code for the 100 TeV case ://///// 
         ////******************//// 




#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TH1.h"
#include "TLorentzVector.h"
#include <TMath.h>
#include <iostream>
#include "THStack.h"
#include <TFile.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <TObject.h>
#include <Math/Vector4D.h>
#include <Math/Vector4Dfwd.h>
#include <iostream>
#include <algorithm>
#include <cmath>

// these files contents are included while loading the analysis.c code

void analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analysis.C
//      root> analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *inputfile = new TFile("ppT0h_hT0aa_100TeV_Cut.root", "READ");
   TFile *outputfile = new TFile("Output(2)_100Tev.root", "UPDATE" );

// these two takes input from the tag_1_delphes root file which was created in first place from the delphes program and creates another file with the output of the code with name "Output_100Tev.root"


//""""""""""Now we will define the parametrs for the run and put the weights for the process""""""""

float cross_section = 292.78;  // The Cross-Section in fb
float N = 100000;    // Number of events
float DataLum = 3000;		   //  Luminosity of data in fb^-1		
float MCLum = N / cross_section;  // Luminosity of Monte-Carlo  in fb^-1                    
float weight = DataLum / MCLum;       // Weight of the simulation process with repsect to data 



// ***************Now we will create the histograms*****************


 //Histogram for the Photon size

TH1I *PhotonSize = new TH1I("PhotonSize", "No. of Photons per event at 100 Tev ", 5, 0, 4);
   PhotonSize->GetXaxis()->SetTitle("Photons no.");
   PhotonSize->GetYaxis()->SetTitle("Events");

//Histograms for the Transverse Momentum PT and the Pseudorapidity eta
// photon 1 will be the leading photon and photon 2 will be the sub-leading photon

TH1D *Photon1_PT = new TH1D("Photon1_PT", "Transverse Momentum distribution for the leading photon at 100 Tev (LHC)", 100, 0., 2000);
   Photon1_PT->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   Photon1_PT->GetYaxis()->SetTitle("Events");
   
   TH1D *Photon1_eta = new TH1D("Photon1_eta", "Pseudorapidity distribution for the leading photon at 100 Tev (LHC)", 80, -3.5, 3.5);
   Photon1_eta->GetXaxis()->SetTitle("eta"); 
   Photon1_eta->GetYaxis()->SetTitle("Events");

TH1D *Photon2_PT = new TH1D("Photon2_PT", "Transverse Momentum distribution for the sub_leading photon at 100 Tev (LHC)", 100, 0., 300);
   Photon2_PT->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   Photon2_PT->GetYaxis()->SetTitle("Events");
   
   TH1D *Photon2_eta = new TH1D("Photon2x_eta", "Pseudorapidity distribution for the sub_leading photon at 100 Tev (LHC)", 80, -3.5, 3.5);
   Photon2_eta->GetXaxis()->SetTitle("eta"); 
   Photon2_eta->GetYaxis()->SetTitle("Events");


// ****The histograms for the Mass and eta of the Higgs

TH1D *Higgs_Mass = new TH1D("Higgs_Mass", "Invariant mass for the Higgs Boson at 100 Tev", 100, 0., 200.);
   Higgs_Mass->GetXaxis()->SetTitle("Mass (GeV)");
   Higgs_Mass->GetYaxis()->SetTitle("Events");
   
   TH1D *Higgs_eta = new TH1D("Higgs_eta", "Pseudorapidity for the Higgs Boson at 100 Tev", 70, -3.5, 3.5);
   Higgs_eta->GetXaxis()->SetTitle("eta"); 
   Higgs_eta->GetYaxis()->SetTitle("Events");




   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

// THe TLorent Vector

TLorentzVector  photon0, photon1, h;
    

	photon0.SetPtEtaPhiE(Photon_PT[0], Photon_Eta[0], Photon_Phi[0], Photon_E[0]);
	photon1.SetPtEtaPhiE(Photon_PT[1], Photon_Eta[1], Photon_Phi[1], Photon_E[1]);		
	


// The Higgs is:
h=photon0 + photon1;


// Now we fill the histograms:

PhotonSize->Fill(Photon_size);
Photon1_PT->Fill(Photon_PT[0], weight);
Photon1_eta->Fill(Photon_Eta[0], weight);
Photon2_PT->Fill(Photon_PT[1], weight);
Photon2_eta->Fill(Photon_Eta[1], weight);
Higgs_Mass->Fill(h.M(), weight);
Higgs_eta->Fill(h.Eta(), weight);

   }
// the for loop is now ended


// Now we write the histograms
PhotonSize->Write();
Photon1_PT->Write();
Photon1_eta->Write();
Photon2_PT->Write();
Photon2_eta->Write();
Higgs_Mass->Write();
Higgs_eta->Write();

// Now we draw the histograms
PhotonSize->Draw();
Photon1_PT->Draw();
Photon1_eta->Draw();
Photon2_PT->Draw();
Photon2_eta->Draw();
Higgs_Mass->Draw();
Higgs_eta->Draw();


outputfile->Close();

} // end of loop member function





