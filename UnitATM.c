#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "UnitATM_tools.h"

int main(int argc, char *argv[])
{
	// Zmienne dla parametrów
	int scaleExponent = 0;
	int descriptor = -1;
	int resources[3] = {0, 0, 0};
	unsigned int seed = 0;
	double delay = 1.0;

	// Wczytanie i weryfikacja parametrów
	if (!parseArguments(argc, argv, &scaleExponent, resources, &descriptor, &seed, &delay))
	{
		fprintf(stderr, "Błędne parametry uruchomienia.\n");
		return 1;
	}

	// Ustawienie ziarna dla losowania kolejności wydawania
	if (seed == 0)
	{
		// Jeśli nie podano -s, ustawiamy PID jako ziarno (zgodnie z założeniem)
		seed = (unsigned int)getpid();
	}

	srand(seed);

	// Obliczenie faktycznej skali (10^scaleExponent)
	long scaleValue = computeScale(scaleExponent);

	// Główna pętla przetwarzania wejścia
	char line[256];

	while (fgets(line, sizeof(line), stdin))
	{
		// Usunięcie białych znaków i sprawdzenie poprawności
		if (isLineEmpty(line))
		{
			// Ignorujemy puste wiersze bez komentarza
			continue;
		}

		long amount = parseInputLine(line);

		if (amount < 0)
		{
			// Linia niepoprawna – wypisujemy komunikat na strumień diagnostyczny
			fprintf(stderr, "Niepoprawna linia danych: %s", line);
			continue;
		}

		// Próbujemy wydać żetony
		long remainder = dispenseTokens(amount, scaleValue, resources, descriptor, delay);

		// Wypisanie reszty na standardowe wyjście
		printf("%ld\n", remainder);
	}

	return 0;
}
