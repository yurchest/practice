#include "plant.h"

//#include <discpp.h>

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using std::vector;
#include <iomanip>
#include <string.h>

#define ARR 100

void
input(int &M, int &K, int L[ARR], double &D, double U[]){

    cout << "Enter number of sensor : ";
    cin >> M;

    cout << "Enter the number of control channels : ";
    cin >> K;
    cout << endl << "************************************************************************" <<endl;

    cout << "         NUMBERS OF CONTOL CHANNELS     " << endl;
    for(int i = 0; i < K; i++){
        cout << "Enter the number of the " << i + 1 << "st  control channnel : ";
        cin >> L[i];
    }
    cout << endl << "************************************************************************" <<endl;

    cout << "         INITIALS VALUES    " << endl;
     for(int i = 0; i < K; i++){
        cout << "Enter the initial value of the " << L[i] << "st  control channnel : ";
        cin >> U[i];
    }
    cout << endl << "************************************************************************" <<endl;

        cout << "Enter search step value : ";
    cin >> D;
    cout << endl << "************************************************************************" <<endl;

    return;
}

double
gradient(int L[], double U[], int i, double D ,int M, double Y, double &Y1, Plant plant){


    plant_control(L[i], U[i] + D, plant);

    Y1 = plant_measure(M, plant);


    double P = (Y1-Y)/D;
    return P;
}

void
new_U(double U2[], int K, double Q, double P[], double U[]){
    for (int i = 0; i < K; i++){
        U2[i] = U[i] + Q*P[i];
    }
return;
}

double
sqrt_sum_squares(double P[], int K){
    double sum = 0;
    for (int i = 0; i < K; i++){
        sum = sum + pow(P[i], 2);
    }
    return sqrt(sum);
}

int main()
{
    Plant plant;
    plant_init(plant);

    int M, K, L[ARR], N;
    double U[ARR], Q, P[ARR], U2[ARR], Y, Y1, D, Y1x[ARR];

    cout << "Enter the number of search steps : ";
    cin >> N;

    int current_research = 1;

    input(M, K, L, D, U);

        cout << setiosflags(ios::left);
        cout << "         RESULT OUTPUTS" << endl;
        cout << setw(4) << "N";


        for (int i = 0; i < K; i++){
            cout << "U" << setw(13) << i + 1;
        }
        cout << setw(13) << "Y";
        for (int i = 0; i < K; i++){
            cout << "Y1_" << setw(11) << i + 1;
        }
        for (int i = 0; i < K; i++){
            cout << "P" << setw(13) << i + 1;
        }
        for (int i = 0; i < K; i++){
            cout << "U'" << setw(13) << i + 1;
        }

        cout << endl << endl;

    while (current_research <= N) {

        for(int i = 0; i < K; i++){
            plant_control(L[i],U[i],plant);
            }

        Y = plant_measure(M,plant);

        for (int i = 0; i < K; i++){
           P[i] = gradient(L, U, i, D, M ,Y ,Y1, plant);
           Y1x[i] = Y1;
        }

        Q = D / sqrt_sum_squares(P, K);

        new_U(U2, K, Q, P, U);

        cout << setw(4) << current_research;

        for (int i = 0; i < K; i++){
            cout << setw(14) << U[i];
        }

        cout << setw(13) << Y;

        for (int i = 0; i < K; i++){
            cout << setw(14) << Y1x[i];
        }

        memcpy(U, U2, sizeof(U));

        for (int i = 0; i < K; i++){
            cout << setw(14) << P[i];
        }
        for (int i = 0; i < K; i++){
            cout << setw(14) << U2[i];
        }

        cout << endl;

        current_research++;

    }

    cout << endl << " Q = " << Q;
    cout << endl << " Y = " << Y;
    cout << endl << " M = " << M;
    cout << endl << " D = " << D;

    cout << endl <<endl;

    return 0;
}
