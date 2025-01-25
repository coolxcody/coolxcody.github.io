#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "UnitATM_tools.h"

int parseArguments(int argc, char *argv[], int *scaleExponent, int resources[3], int *descriptor, unsigned int *seed, double *delay)
{
	// Flagi służą weryfikacji, czy parametry obowiązkowe zostały podane
	int mFlag = 0, tFlag = 0;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-u") == 0 && i + 1 < argc)
		{
			*scaleExponent = atoi(argv[++i]);
			if (*scaleExponent < 0)
			{
				return 0; // Skala musi być nieujemna
			}
		}
		else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc)
		{
			mFlag = 1;
			if (!parseResources(argv[++i], resources))
			{
				return 0; // Niepoprawne zasoby
			}
		}
		else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
		{
			tFlag = 1;
			*descriptor = atoi(argv[++i]);
			if (*descriptor <= 0)
			{
				return 0; // Deskryptor musi być > 0
			}
		}
		else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
		{
			*seed = (unsigned int)atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
		{
			*delay = atof(argv[++i]);
			if (*delay <= 0)
			{
				return 0; // Opóźnienie musi być dodatnie
			}
		}
	}

	if (!mFlag || !tFlag)
	{
		return 0; // Parametry obowiązkowe nie zostały ustawione
	}

	return 1;
}

int parseResources(const char *str, int resources[3])
{
	// Format x:y:z
	int count = 0;
	char *token = NULL;
	char buffer[256];
	strncpy(buffer, str, 256);
	buffer[255] = '\0';

	token = strtok(buffer, ":");

	while (token != NULL && count < 3)
	{
		int val = atoi(token);
		if (val < 0) return 0;

		resources[count++] = val;
		token = strtok(NULL, ":");
	}

	if (count != 3) return 0;
	return 1;
}

long computeScale(int exponent)
{
	// skala
	long scale = 1;
	
	for (int i = 0; i < exponent; i++)
	{
		scale *= 10;
	}

	return scale;
}

int isLineEmpty(const char *line)
{
	// Sprawdzenie, czy linia jest pusta lub zawiera tylko białe znaki
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (!isspace((unsigned char)line[i]))
		{
			return 0;
		}
	}

	return 1;
}

long parseInputLine(const char *line)
{
	// Próba konwersji jednego nieujemnego inta
	char *endptr;
	long value = strtol(line, &endptr, 10);

	if (endptr == line)
	{
		// Nie udało się sparsować żadnej liczby
		return -1;
	}

	if (value < 0)
	{
		// Wartość nie może być ujemna
		return -1;
	}

	// Sprawdzamy, czy po liczbie nie ma żadnych niedozwolonych znaków
	while (*endptr != '\0')
	{
		if (!isspace((unsigned char)*endptr))
		{
			return -1;
		}

		endptr++;
	}

	return value;
}

long dispenseTokens(long amount, long scaleValue, int resources[3], int descriptor, double delay)
{
	// Obliczamy ile faktycznie należy wydać w  skali
	long totalToIssue = amount;
	long rema = totalToIssue;

	// Lista nominałów
	int denominations[3] = {5, 2, 1};

	// Próbujemy wydać (dla uproszczenia, bez wstępnego sortowania, najpierw zliczamy ile w danym nominale jest potrzebne
	int issued[3] = {0, 0, 0};
	for (int i = 0; i < 3; i++)
	{
		int needed = rema / denominations[i];
		if (needed > 0)
		{
			if (resources[i] >= needed)
			{
				issued[i] = needed;
				resources[i] -= needed;
				rema -= needed * denominations[i];
			}
			else
			{
				// Jeśli nie mamy wystarczających zasobów danego nominału, wydajemy tyle, ile mamy
				issued[i] = resources[i];
				resources[i] = 0;
				rema -= issued[i] * denominations[i];
			}
		}
	}

	// Każdy pojedynczy żeton jako (nominał * skala), kończony nową linią
	writeTokensRandomOrder(denominations, issued, scaleValue, descriptor, delay);

	return rema;
}

void writeTokensRandomOrder(const int denominations[3], const int issued[3], long scaleValue, int descriptor, double delay)
{
	// Tworzymy tablicę  wszystkich żetonów i tasujemy ją przed wypisem
	int totalCoins = issued[0] + issued[1] + issued[2];
	if (totalCoins == 0)
	{
		// Nie ma co wypisywać – pusta linia i kończymy
		dprintf(descriptor, "\n");
		return;
	}

	int *coinsList = (int*)malloc(sizeof(int) * totalCoins);
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < issued[i]; j++)
		{
			coinsList[index++] = denominations[i];
		}
	}

	// Tasowanie
	for (int i = totalCoins - 1; i > 0; i--)
	{
		int r = rand() % (i + 1);
		int temp = coinsList[i];
		coinsList[i] = coinsList[r];
		coinsList[r] = temp;
	}

	// Wypisujemy w wylosowanej kolejności
	for (int i = 0; i < totalCoins; i++)
	{
		long scaledValue = coinsList[i] * scaleValue;
		dprintf(descriptor, "%ld\n", scaledValue);

		// Dodajemy opóźnienie
		useconds_t usecDelay = (useconds_t)(delay * 10000);
		usleep(usecDelay);
	}

	// Pusta linia na koniec informacji o wydanych monetach
	dprintf(descriptor, "\n");
	free(coinsList);
}
