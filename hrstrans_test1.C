#include "THRSTrans.h"
#include "TGraph.h"
#include "TCanvas.h"
#include <iostream>

// At root prompt:
//    .L THRSTrans.C+
//    .L hrstrans_test1.C+
//     hrstrans_test1()


using namespace std;

void hrstrans_test1(){

  // Standard tune
  //    THRSTrans *trans = new THRSTrans( 0.1746, -0.1385, -0.1281, 0.050178, 0.037056, THRSTrans::kStd);
  //    THRSTrans *trans = new THRSTrans( 0.1319, -0.1385, -0.1281, 0.050178, 0.037056, THRSTrans::kStd);

    THRSTrans *trans = new THRSTrans( 0.13, -0.11, -0.12, 0.050178, 0.037056, THRSTrans::kStd);

    cout << "Result of initial THRSTrans "<<endl;
    trans->ShowOutput();
    cout << "matrix again "<<endl;
    cout << trans->GetMatrElem(0,0)<<"  "<<trans->GetMatrElem(0,1)<<"  "<<trans->GetMatrElem(0,2)<<"  "<<trans->GetMatrElem(0,3)<<"  "<<trans->GetMatrElem(0,4)<<endl;
    cout << trans->GetMatrElem(1,0)<<"  "<<trans->GetMatrElem(1,1)<<"  "<<trans->GetMatrElem(1,2)<<"  "<<trans->GetMatrElem(1,3)<<"  "<<trans->GetMatrElem(1,4)<<endl;
    cout << trans->GetMatrElem(2,0)<<"  "<<trans->GetMatrElem(2,1)<<"  "<<trans->GetMatrElem(2,2)<<"  "<<trans->GetMatrElem(2,3)<<"  "<<trans->GetMatrElem(2,4)<<endl;
    cout << trans->GetMatrElem(3,0)<<"  "<<trans->GetMatrElem(3,1)<<"  "<<trans->GetMatrElem(3,2)<<"  "<<trans->GetMatrElem(3,3)<<"  "<<trans->GetMatrElem(3,4)<<endl;
    cout << trans->GetMatrElem(4,0)<<"  "<<trans->GetMatrElem(4,1)<<"  "<<trans->GetMatrElem(4,2)<<"  "<<trans->GetMatrElem(4,3)<<"  "<<trans->GetMatrElem(4,4)<<endl;

    cout << "----------------- end ----------------- "<<endl;

    return;

}


