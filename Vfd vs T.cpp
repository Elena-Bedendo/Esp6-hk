//g++ -o fit fit2.cpp $(root-config --cflags --libs)

//Grafico
#include <TGraphErrors.h>
#include <TF1.h>
#include <TApplication.h>
#include <TAxis.h>

using namespace std;

int main() {
    TApplication app ("app", 0, 0);

    //Creo il grafico
    TGraphErrors gr("Vfd_vs_T.dat" , "%lg %lg %lg %lg");

    //Disegno il grafico e metto il nome ai due assi del grafico
    gr.Draw("ap");
    gr.GetXaxis()->SetTitle("T[K]");
    gr.GetYaxis()->SetTitle("V_fd[V]");
    gr.SetTitle("");

    //Creo la funzione di fit
    TF1 fun("fun", "[0]*pow(exp((TMath::C()*[1])/(x))-1 ,-1)");
    fun.SetLineColor(433);  //Definisco colore
    //Inizializzo i parametri
    fun.SetParameter(0, 1);
    fun.SetParameter(1, 5e-11/635e-9); // h/(k*lambda)
    //Disegno la funzione nel grafico
    gr.Fit("fun");

    //Calcolo e stampo il Chi quadro (chi2), il numero gradi di libertà (ndf) e la probabilità (prob)
    double chi2 = fun.GetChisquare();
    int ndf = fun.GetNDF();
    double prob = fun.GetProb();
    cout << endl << "Chi quadro: " << chi2 << endl 
    << "Numero di gradi di liberta: " << ndf << endl 
    <<"Probabilita del chi quadro: " << prob << endl;

    //Calcolo h/k e il suo errore
    double par_1 = fun.GetParameter(1) , lambda = 635e-9;
    double epar_1 = fun.GetParError(1) , elambda = 5e-9;

    double h_k = par_1 * lambda , eh_k = par_1 * elambda + lambda * epar_1;
    cout << h_k << " +- " << eh_k;

    app.Run();    
    return 0;
}
