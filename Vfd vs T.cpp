//g++ -o fit fit.cpp $(root-config --cflags --libs)

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
    TF1 fun("fun", "[0]*pow(exp((TMath::C()*[1])/(x*635e-9))-1 ,-1)");
    fun.SetLineColor(433);  //Definisco colore
    //fun.SetNpx(10000);  METTERE SOLO SE SERVE!
    //Inizializzo i parametri
    fun.SetParameter(0, 1);
    fun.SetParameter(1, 5e-11);
    //Disegno la funzione nel grafico
    gr.Fit("fun");

    //Calcolo e stampo il Chi quadro (chi2), il numero gradi di libertà (ndf) e la probabilità (prob)
    double chi2 = fun.GetChisquare();
    int ndf = fun.GetNDF();
    double prob = fun.GetProb();
    cout << endl << "Chi quadro: " << chi2 << endl 
    << "Numero di gradi di liberta: " << ndf << endl 
    <<"Probabilita del chi quadro: " << prob << endl;

    app.Run();    
    return 0;
}
