#include "THRSTrans.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#ifndef __CINT__
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TRandom.h"
#endif
#include "TGraph.h"
#include "TCanvas.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv) 
{
 
   Int_t debug = 1;

 // Initialize root and output.  
   TROOT scalana("hrsroot","Hall A spectrometer optics analysis");
   TFile hfile("hrs.root","RECREATE","HRSTrans analysis");

// Define the ntuple here. 
//               0  1  2    3 4   5    6    7      8     9    10    11    12    13    14    15    16    17    18  19     20
   char ctrans[]="i:j:chisq:q1:q2:q3:hrs11:hrs12:hrs13:hrs14:hrs15:hrs21:hrs22:hrs23:hrs24:hrs25:hrs31:hrs32:hrs33:hrs34:hrs35:hrs41:hrs42:hrs43:hrs44:hrs45:hrs51:hrs52:hrs53:hrs54:hrs55";
// 21    22   23    24    25    26    27   28    29   30

   Int_t nlen = strlen(ctrans);
   char *string_ntup = new char[nlen+1];
   strcpy(string_ntup, ctrans);

   TNtuple *hrt = new TNtuple("hrt","HRS Trans analysis",string_ntup);
   Float_t* farray_ntup = new Float_t[nlen+1];  
// end of ntuple definition

   Float_t weight[30], nim_matrix[30];

   // How important are the parameters ?  my judgement

   weight[0*5+0] = 1.0; 
   weight[0*5+1] = 5.0;
   weight[0*5+2] = 0.2;
   weight[0*5+3] = 0.2;
   weight[0*5+4] = 4.0;

   weight[1*5+0] = 1.0;  
   weight[1*5+1] = 1.0;
   weight[1*5+2] = 0.2;
   weight[1*5+3] = 0.2;
   weight[1*5+4] = 1.0;  

   weight[2*5+0] = 0.2;  
   weight[2*5+1] = 0.2;
   weight[2*5+2] = 1.0;
   weight[2*5+3] = 5.0;  
   weight[2*5+4] = 0.2;

   weight[3*5+0] = 0.2;  
   weight[3*5+1] = 0.2;  
   weight[3*5+2] = 1.0;
   weight[3*5+3] = 2.0;
   weight[3*5+4] = 0.2;

   weight[4*5+0] = 0.2;   
   weight[4*5+1] = 0.2;
   weight[4*5+2] = 0.2;
   weight[4*5+3] = 0.2;
   weight[4*5+4] = 1.0;

   // NIM paper matrix elements

   nim_matrix[0*5+0] = -2.48;
   nim_matrix[0*5+1] = 0;
   nim_matrix[0*5+2] = 0;
   nim_matrix[0*5+3] = 0;
   nim_matrix[0*5+4] = 12.4;

   nim_matrix[1*5+0] = -0.15;  
   nim_matrix[1*5+1] = -0.40;
   nim_matrix[1*5+2] = 0;
   nim_matrix[1*5+3] = 0;
   nim_matrix[1*5+4] = 2.04;  

   nim_matrix[2*5+0] = 0;  
   nim_matrix[2*5+1] = 0;
   nim_matrix[2*5+2] = -0.40;
   nim_matrix[2*5+3] = -1.30;  
   nim_matrix[2*5+4] = 0;

   nim_matrix[3*5+0] = 0;  
   nim_matrix[3*5+1] = 0;  
   nim_matrix[3*5+2] = 0.54;
   nim_matrix[3*5+3] = -0.78;
   nim_matrix[3*5+4] = 0;

   nim_matrix[4*5+0] = 0;   
   nim_matrix[4*5+1] = 0;
   nim_matrix[4*5+2] = 0;
   nim_matrix[4*5+3] = 0;
   nim_matrix[4*5+4] = 1.0;


// Loop over parameters, try to find optimum.

   Double_t chisq, chisqmin, chisqcut;
   Double_t xdiff, q1, q2, q3;
   Int_t isoln, iq1,iq2,iq3,i,j;
   Int_t heartbeat=0;

   Int_t NQ1 = 10;
   Int_t NQ2 = 7;
   Int_t NQ3 = 7;
 
   Double_t q1lo =  0.090;   Double_t q1hi =  0.125;
   Double_t q2lo = -0.150;   Double_t q2hi = -0.11;
   Double_t q3lo = -0.150;   Double_t q3hi = -0.11;

   chisqmin = 999999999; 
   chisqcut = 2000;

   THRSTrans *trans = 0;
   isoln = -1;

   for (iq1=0; iq1<NQ1; iq1++) {

     cout << "===============            iq1 loop "<<iq1<<endl;


   for (iq2=0; iq2<NQ1; iq2++) {

   for (iq3=0; iq3<NQ1; iq3++) {


     q1 = q1lo + (q1hi - q1lo)*1.0*iq1/(1.0*NQ1);
     q2 = q2lo + (q2hi - q2lo)*1.0*iq2/(1.0*NQ2);
     q3 = q3lo + (q3hi - q3lo)*1.0*iq3/(1.0*NQ3);

     if(debug) cout << "trans ?  "<<trans<<"   "<<heartbeat++<<endl;
     if (trans) {
       if(debug) cout << "deleting trans"<<endl;
       delete trans;
       trans=0;
     }

     trans = new THRSTrans(q1,q2,q3, 0.050178, 0.037056, THRSTrans::kStd);

     //     trans->ShowOutput();

     chisq = 0;
     xdiff = 0;

     for (i=0; i<5; i++) {

        for (j=0; j<5; j++) {

	  if (trans) {
            if(debug) cout << "i "<<i<<"    "<<j<<endl;
            xdiff = trans->GetMatrElem(i,j) - nim_matrix[5*i + j];
	  } else {
	    cout << "ERROR: no trans ?"<<endl;
	  }  
         
           chisq += weight[5*i + j] * xdiff*xdiff;

	}
     }
   
     if (chisq < chisqmin) {
       chisqmin = chisq;
       isoln = 5*i+j;
     }

     if (chisq < chisqcut) {

       farray_ntup[0] = i;
       farray_ntup[1] = j;
       farray_ntup[2] = chisq;
       farray_ntup[3] = q1;
       farray_ntup[4] = q2;
       farray_ntup[5] = q3;

       for (i = 0; i<5; i++) {
	 for (j=0; j<5; j++) {
	   farray_ntup[6+5*i+j] = trans->GetMatrElem(i,j);
	 }
       }

       hrt->Fill(farray_ntup);

     }
   }
   }
   }

   cout << "solution "<<isoln<<"   "<<chisqmin<<endl;

    hfile.Write();
    hfile.Close();

    return 1;

}



