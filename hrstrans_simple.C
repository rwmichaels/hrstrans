#include "THRSTrans.h"
#include "TGraph.h"
#include "TCanvas.h"
#include <iostream>

// At root prompt:
//    .L THRSTrans.C+
//    .L hrstrans_simple.C+
//     hrstrans_simple()


using namespace std;

void hrstrans_simple(){

  // Standard tune
  //    THRSTrans *trans = new THRSTrans( 0.1746, -0.1385, -0.1281, 0.050178, 0.037056, THRSTrans::kStd);
  //    THRSTrans *trans = new THRSTrans( 0.1319, -0.1385, -0.1281, 0.050178, 0.037056, THRSTrans::kStd);

    THRSTrans *trans = new THRSTrans( 0.107, -0.107, -0.107, 0.050178, 0.037056, THRSTrans::kStd);

    cout << "Result of initial THRSTrans "<<endl;
    trans->ShowOutput();
    trans->ShowAcc();
    trans->ShowFocalLengths();
    trans->GetOptics()->Print();
    cout << "----------------- end ----------------- "<<endl;

    return;

}


