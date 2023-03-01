#include<iostream>

using namespace std;

struct Users
{
	double x; /* coordinate x */
	double y; /* coordinate y */
	double c; /* requested content amount */
};

struct G /* gNB RU */
{
	double x;
	double y;
	double d_gc;
	double d_gd;
};

struct PSA_UPF /* PSA UPF */
{
	double x;
	double y;
};

struct EAS
{
	double x;
	double y;
};

int Num_Users = 4; /* Number of Users */
int Num_gNB_RU = 3; /* Number of gNB RUs */
int Num_PSA_UPF = 3; /* Number of PSA UPFs */
int Num_EAS = 3; /* Number of EASs */

int T = 20; /* Number of Time Slots */

Users** users = new Users*[Num_Users]; /* UEs */

bool** history = new bool*[Num_Users]; /* History of visited paths for each user */

int* Last_gNU_RU = new int[Num_Users]; /* Shows the latest allocated gNU_RU for each user */
int* Last_PSA_UPF = new int[Num_Users]; /* Shows the latest allocated PSA_UPF for each user */
int* Last_EAS = new int[Num_Users]; /* Shows the latest allocated EAS for each user */

/* relocation cost and migration cost */
double** R = new double*[Num_PSA_UPF];
double** S = new double*[Num_EAS];

/* initiate network components */

G* gNB_RUs = new G[Num_gNB_RU];
PSA_UPF* PSA_UPFs = new PSA_UPF[Num_PSA_UPF];
EAS* EASs = new EAS[Num_EAS];

/* parameters for MAB */
double alpha = 0.5;
double beta = 0.5;
double Closeness = 300; /* to show gNU_RU, PSA_UPF, and EAS must be at most in this range */

/* Counters for the number of times each path is selected */
int** X = new int*[Num_Users];

/* transmission speeds */
double** D_ng = new double*[Num_Users]; /* wireless transmission speed based on 5G  between  UE n and  its  corresponding  gNB RU g */
double** D_gi = new double*[Num_gNB_RU]; /* the speed of transmitting content between  gNB RU g and  PSA  UPF i */
double** D_ij = new double*[Num_PSA_UPF]; /* the  speed  of  transmitting  content  between  PSA UPF i and the targeted EAS j */

/* Average Delay for Paths per each user */
double** D = new double*[Num_Users];

void Initialization()
{
	
	for (int i = 0;i < Num_gNB_RU;i++)
	{
		/*
		gNB_RUs[i].d_gc = ;
		gNB_RUs[i].d_gd = ;
		gNB_RUs[i].x = ;
		gNB_RUs[i].y = ;
		*/
	}

	for (int i = 0;i < Num_PSA_UPF;i++)
	{
		/*
		PSA_UPFs[i].x = ;
		PSA_UPFs[i].y = ;
		*/
	}

	for (int i = 0;i < Num_EAS;i++)
	{
		/*
		EASs[i].x = ;
		EASs[i].y = ;
		*/
	}

	for (int i = 0; i < Num_Users; i++)
	{
		for (int j = 0; j < T; j++)
		{
			/*
			users[i][j].x =  ;
			users[i][j].y =  ;
			users[i][j].c =  ;
			*/
			
		}
	}

	for (int i = 0; i < Num_Users; i++)
	{
		for (int j = 0; j < Num_gNB_RU; j++)
		{
			/*
			D_ng[i][j] = ;
			*/

		}
	}

	for (int i = 0; i < Num_gNB_RU; i++)
	{
		for (int j = 0; j < Num_PSA_UPF; j++)
		{
			/*
			D_gi[i][j] = ;
			*/

		}
	}

	for (int i = 0; i < Num_PSA_UPF; i++)
	{
		for (int j = 0; j < Num_EAS; j++)
		{
			/*
			D_ij[i][j] = ;
			*/

		}
	}

	for(int i = 0; i<Num_PSA_UPF; i++)
		for (int j = 0; j < Num_PSA_UPF; j++)
		{
			/*
			R[i][j] = 
			*/
		}

	for(int i=0; i<Num_EAS; i++)
		for (int j = 0; j < Num_EAS; j++)
		{
			/*
			S[i][j] = 
			*/
		}

	for (int i = 0; i < Num_Users; i++)
	{
		for (int j = 0; j < Num_gNB_RU * Num_PSA_UPF * Num_EAS; j++)
			history[i][j] = false;
	}

}
void QCSCD(Users** users)
{
	for(int n = 0; n<Num_Users; n++)
		for (int t = 0; t < T; t++)
		{
			bool flag_newpath = false; /* check the availibility of a new unvisited path */

			/* check the availibility of unvisited paths in close proximity of the user */
			for (int g = 0; g<Num_gNB_RU; g++)
				for (int i = 0; i<Num_PSA_UPF; i++)
					for (int j = 0; j < Num_EAS; j++)
					{
						bool flag_gNU_RU = false;
						bool flag_PSA_UPF = false;
						bool flag_EAS = false;

						if (pow(abs(users[n][t].x - gNB_RUs[g].x), 2) + pow(abs(users[n][t].y - gNB_RUs[g].y), 2) < Closeness * Closeness) /* it not sqrt, so it is in power of 2 */
						{
							flag_gNU_RU = true;
						}
						if (pow(abs(users[n][t].x - PSA_UPFs[i].x), 2) + pow(abs(users[n][t].y - PSA_UPFs[i].y), 2) < Closeness * Closeness)
						{
							flag_PSA_UPF = true;
						}
						if (pow(abs(users[n][t].x - EASs[j].x), 2) + pow(abs(users[n][t].y - EASs[j].y), 2) < Closeness * Closeness) 
						{
							flag_EAS = true;
						}

						int path_index = g * Num_PSA_UPF * Num_EAS + i * Num_EAS + j;

						/* unselected path in close proximity of the user */
						if (!history[n][path_index] && flag_gNU_RU && flag_PSA_UPF && flag_EAS)
						{
							flag_newpath = true;

							history[n][path_index] = true;

							D[n][path_index] = (users[n][t].c) / (gNB_RUs[g].d_gc + gNB_RUs[g].d_gd + D_ng[n][g] + D_gi[g][i] + D_ij[i][j]);

							if (t != 0)
							{
								if (Last_PSA_UPF[n] != i)
									D[n][path_index] += R[Last_PSA_UPF[n]][i];
								if (Last_EAS[n] != j)
									D[n][path_index] += S[Last_EAS[n]][j];
							}

							D[n][path_index] /= users[n][t].c;
							
							Last_gNU_RU[n] = g;
							Last_PSA_UPF[n] = i;
							Last_EAS[n] = j;

							X[n][path_index] = 1;						

						}
					}

			if (!flag_newpath) /* no unselected path */
			{
				int min = INT_MAX;
				int index = -1; /* shows the index of the best path */

				int g_index; /* shows the gNB RU of the best path */
				int i_index; /* shows the PSA UPF of the best path */
				int j_index; /* shows the EAS of the best path */

				/* check all previously visited paths and select the min */
				for (int g = 0; g<Num_gNB_RU; g++)
					for (int i = 0; i<Num_PSA_UPF; i++)
						for (int j = 0; j < Num_EAS; j++)
						{
							bool flag_gNU_RU = false;
							bool flag_PSA_UPF = false;
							bool flag_EAS = false;

							if (pow(abs(users[n][t].x - gNB_RUs[g].x), 2) + pow(abs(users[n][t].y - gNB_RUs[g].y), 2) < Closeness * Closeness)
							{
								flag_gNU_RU = true;
							}
							if (pow(abs(users[n][t].x - PSA_UPFs[i].x), 2) + pow(abs(users[n][t].y - PSA_UPFs[i].y), 2) < Closeness * Closeness)
							{
								flag_PSA_UPF = true;
							}
							if (pow(abs(users[n][t].x - EASs[j].x), 2) + pow(abs(users[n][t].y - EASs[j].y), 2) < Closeness * Closeness)
							{
								flag_EAS = true;
							}

							int path_index = g * Num_PSA_UPF * Num_EAS + i * Num_EAS + j;

							/* unselected path in close proximity of the user */
							if (history[n][path_index] && flag_gNU_RU && flag_PSA_UPF && flag_EAS)
							{
								if (alpha * D[n][path_index] - beta * sqrt((2 * log(t + 1) / log(2.71828183)) / (X[n][path_index])) < min)
								{
									min = alpha * D[n][path_index] - beta * sqrt((2 * log(t + 1) / log(2.71828183)) / (X[n][path_index]));

									index = path_index;

									g_index = g;
									i_index = i;
									j_index = j;
								}
							
							}
						}

				double temporary = 0;

				temporary =  (users[n][t].c / (gNB_RUs[g_index].d_gc + gNB_RUs[g_index].d_gd + D_ng[n][g_index] + D_gi[g_index][i_index] + D_ij[i_index][j_index]));
				
				if (Last_PSA_UPF[n] != i_index)
					temporary += R[Last_PSA_UPF[n]][i_index];
				if (Last_EAS[n] != j_index)
					temporary += S[Last_EAS[n]][j_index];

				temporary /= users[n][t].c;

				D[n][index] = X[n][index] * D[n][index] + temporary;

				D[n][index] /= (X[n][index] + 1);

				X[n][index] = X[n][index] + 1; 
			}
		}

}

int main()
{
	

	for (int i = 0; i < Num_Users; i++)
	{
		/* Declare a memory block  of size T for each user */
		users[i] = new Users[T];
	}
	
	for (int i = 0; i < Num_Users; i++)
	{
		/* Declare a memory block  of size T for each user */
		history[i] = new bool[Num_gNB_RU * Num_PSA_UPF * Num_EAS];
	}

	for (int i = 0; i < Num_Users; i++)
	{
		/* Declare a memory block  of size Num_gNB_RU for each user */
		D_ng[i] = new double[Num_gNB_RU];
	}
	for (int i = 0; i < Num_gNB_RU; i++)
	{
		/* Declare a memory block  of size Num_PSA_UPF for each gNB_RU */
		D_gi[i] = new double[Num_PSA_UPF];
	}
	for (int i = 0; i < Num_PSA_UPF; i++)
	{
		/* Declare a memory block  of size Num_EAS for each PSA_UPF */
		D_ij[i] = new double[Num_EAS];
	}

	for (int i = 0; i < Num_Users; i++)
	{
		D[i] = new double[Num_gNB_RU * Num_PSA_UPF * Num_EAS];
	}

	for (int i = 0; i < Num_Users; i++)
	{
		X[i] = new int[Num_gNB_RU * Num_PSA_UPF * Num_EAS];
	}

	for (int i = 0; i < Num_PSA_UPF; i++)
	{
		R[i] = new double[Num_PSA_UPF];
	}

	for (int i = 0; i < Num_EAS; i++)
	{
		S[i] = new double[Num_EAS];
	}

	Initialization(); /* initialization of the variables */

	QCSCD(users); /* calling MAB framework */


	system("pause");
}