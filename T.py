# calcolo di T eT, temperatura.

import   ROOT 
import   math as m
import numpy as np
import time 

#Parametri e misure
T_amb = 298.6 # dai colleghi.
eT_amb = 0.5
R_amb = 44.605 # misurata in lab.
eR_amb = 0.021
gamma = 0.9614 # ricavata dal fit.
egamma = 0.001375

#Funzione 
def GetT(T_amb, V, I, R_amb, gamma):
    
    T = T_amb*(V/(I*R_amb))**gamma
    return T

def GeteT(T_amb, V, I, eI, R_amb, gamma):
    '''a) calcolo dell'errore su A e su B tramite variazione della funzione'''

    # Variazioni delle singole variabili di A e B.
    T = GetT(T_amb, V, I, R_amb, gamma)
    T0 = GetT(T_amb+eT_amb, V, I, R_amb, gamma)
    T1 = GetT(T_amb, V, I+eI, R_amb, gamma)
    T2 = GetT(T_amb, V, I, R_amb+eR_amb, gamma)
    T3 = GetT(T_amb, V, I, R_amb, gamma+egamma)


    # Errore di A e B, quanto quelli variati distano dal valore vero.
    eT = m.sqrt((T0-T)**2 + (T1-T)**2 + (T2-T)**2 + (T3-T)**2)

    return eT

#Main
# Assumendo errore gaussiano (eth/sqrt(3))

V,I,eI = np.loadtxt('T_in.dat',usecols=(0,1,2),unpack=True)

file = open("T_out.dat", "w") 

for i in range(0,V.size):
    T = GetT(T_amb, V[i], I[i], R_amb, gamma)
    eT = GeteT(T_amb, V[i], I[i], eI[i], R_amb, gamma)

    file.write(str(T) + "\t " + str(eT) + "\n")
    print("T +/- eT = %6.3f +- %6.3f" %(T,eT))

    
    



