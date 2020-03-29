//POJ 3970

#include <stdio.h>

int gcd(int a,int b)
{
	if (a > 0 && b > 0) return b == 0 ? a : gcd(b, a % b);
}

int LCM(int x, int y){
	return x*y/gcd(x, y);
} 

int main()
{
	int team_number;
	long int poeple[25];
	
	while (team_number && scanf("%d", &team_number)){
		if (team_number == 1){
			if (scanf("%d", &poeple[0]) != EOF && poeple[0] < 1000000){
				printf("The CEO must bring %d pounds.\n", poeple[0]);
			}
			else{
				printf("Too much money to pay!\n");
			}
		}

		else if (team_number > 1){
			for (int i = 0; i < team_number; ++i)
			{
				scanf("%d", &poeple[i]);
			}
		
			long long int min_lcm = LCM(poeple[0], poeple[1]);
			//printf("第一次打印%d\n", min_lcm);
		
			if (team_number > 2){
				int j = 1;
			
				while (j < team_number-1)
				{
					min_lcm = LCM(min_lcm, poeple[j+1]);
					//printf("第二次打印%d\n", min_lcm);
					j++;
				}
			}
			if (min_lcm >= 1000000) {printf("Too much money to pay!\n");}
			else {printf("The CEO must bring %d pounds.\n", min_lcm);}
		
		}
		
	}
	return 0;
}
