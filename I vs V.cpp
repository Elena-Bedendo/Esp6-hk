//g++ -o fit fit.cpp $(root-config --cflags --libs)


//Grafico
#include <TGraphErrors.h>
#include <TF1.h>
#include <TApplication.h>
#include <TAxis.h>
//Altro
#include <iostream>
using namespace std;


int main() {
    TApplication app ("app", 0, 0);

    //Creo il grafico
    TGraphErrors gr("I_vs_V.dat" , "%lg %lg %lg");

    //Disegno il grafico e metto il nome ai due assi del grafico
    gr.Draw("ap");
    gr.GetXaxis()->SetTitle("V[V]");
    gr.GetYaxis()->SetTitle("I[A]");
    gr.SetTitle("");

    //Creo la funzione di fit
    TF1 fun("fun", "[0]*pow(x,(4*[1]-1)/(4*[1]+1))");
    fun.SetLineColor(433);  //Definisco colore

    //Inizializzo i parametri
    fun.SetParameter(0, .05);
    fun.SetParameter(1, 1);
    //Disegno la funzione nel grafico
    gr.Fit("fun");

    //Calcolo e stampo il Chi quadro (chi2), il numero gradi di libertà (ndf) e la probabilità (prob)
    double chi2 = fun.GetChisquare();
    int ndf = fun.GetNDF();
    double prob = fun.GetProb();
    cout << endl << "Chi quadro: " << chi2 << endl 
    << "Numero di gradi di liberta: " << ndf << endl 
    <<"Probabilita del chi quadro: " << prob << endl;

    //Prendo i parametri(con errori) della funzione di fit
    double p0 , p0_err;//Nome paramtri
    p0 = fun.GetParameter(0);
    p0_err = fun.GetParError(0);

    cout << "p0 = " << p0 << "±" << p0_er << endl;

    app.Run();    
    return 0;
}
