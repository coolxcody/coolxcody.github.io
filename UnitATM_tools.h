#ifndef UNITATM_TOOLS_H
#define UNITATM_TOOLS_H

// Funkcja do wczytania i weryfikacji parametrów
int parseArguments(int argc, char *argv[], int *scaleExponent, int resources[3], int *descriptor, unsigned int *seed, double *delay);

// Funkcja pomocnicza do parsowania zasobów "x:y:z"
int parseResources(const char *str, int resources[3]);

// Funkcja obliczająca 10^exponent
long computeScale(int exponent);

// Funkcja sprawdzająca, czy linia jest pusta
int isLineEmpty(const char *line);

// Funkcja parsująca wiersz wejścia
long parseInputLine(const char *line);

// Funkcja wydająca żetony
long dispenseTokens(long amount, long scaleValue, int resources[3], int descriptor, double delay);

// Funkcja wypisująca żetony w losowej kolejności
void writeTokensRandomOrder(const int denominations[3], const int issued[3], long scaleValue, int descriptor, double delay);

#endif // UNITATM_TOOLS_H
