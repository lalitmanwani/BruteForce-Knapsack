#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <math.h>

using namespace std;


int searchList (const string list[], int numElems, string value,const int m[])
{
    int index = 0;      // Used as a subscript to search array
    while (index < numElems)
    {
       if (list[index] == value) // If the value is found 
          return m[index];
       ++index;
    }
    return -1;

}




void bruteforce(int *set, int *set_weight, int *set_profit, int knapsack_capacity, int size_of_set)
{	
	int k, j, total_profit, total_weight, max_weight, max_profit, max_set[size_of_set], count, itemCount, setCounter;
	int number_of_subsets = pow(2.0, size_of_set);

	k = 0;
	j = 0;	
	total_profit = 0;
	total_weight = 0;
	max_weight = 0;
	max_profit = 0;
	count = 0;
	itemCount = 0;
	setCounter = 0;	
	int max_set2[size_of_set];
	
 
    /*counter for sets*/
         k = 0;
while(k < number_of_subsets)
	{
		int m=0;
		// will get execute for size_of_set times
                j = 0;
		while(j < size_of_set)
		{
          		//will check every possible subset
			if((1<<j) & k)
	   		{
				count++;
				total_profit = total_profit + set_profit[j];
				total_weight = total_weight + set_weight[j];
				max_set[count-1]=j+1;
	   		}j++;
       		}

		if(total_weight <= knapsack_capacity)
		{
			if(total_profit >= max_profit)
			{
				max_weight = total_weight;
				max_profit = total_profit-max_weight;
				int z;
				for(z=0;z<count;z++)
				{
					max_set2[z]=max_set[z];
				}
				itemCount = count;
			}
    		}
		total_profit = 0;
		total_weight = 0;
		count = 0;

       k++;
	}

	cout<< max_profit<<endl;
	cout<<itemCount<<endl;

}
 



int main()
{


	struct timespec tbrut1,tbrut2;

	 ifstream theFile;
	 theFile.open("price-list-file.txt");	 
	 int nc;
	 string s;
	 int i = 0;
	 int v = 0 ;	
	 string n;
	 double m;	
	 string name[100];
	 int money[100];
	 int subsets;
         string set[100];
         int tmp;
        int super_set_size;
        int set_weight[100];
	int capacity;
	int set_profit[100];

	
	 while(theFile >> n >> m)
	 {
		name[i] = n;
                money[i] = (int)m;
		//cout << n << m << "\n";
	 i++;
	 }


         
 
	ifstream mFile;
	 mFile.open("market-price-file.txt");	 
	 string line;
	 if (getline(mFile, line)) std::istringstream(line) >> nc;
	
	//	 cout<< nc;
	 
	 int wc = 1;
	 string marketname[100];
	 int marketmoney[100];
	 
	 while(mFile >> n >> m)
	 {
		marketname[wc] = n;
                marketmoney[wc] =(int) m;
	 wc++;
	 }





	int j = 0;
        int count = 0;
        int p = 0; 
	
        for(j = 0 ; j< i-1 ; j++)
        {
	
                capacity = money[j];
		s = name[j];
		stringstream geek(s);  
	        geek >> count; 
                super_set_size = count;               
 
              cout<<super_set_size<<endl;



       
         for( v =  j + 1; v <= count + j ; v++)
          {
    
           	string x = name[v]; 

                set_weight[p] = money[v];  
                set_profit[p] = searchList(marketname, nc+1, x,marketmoney);
 
                p++;
            }
            

	int set[100];
	int y;
	for(y=0;y<super_set_size;y++){set[y] = y+1;}

	clock_gettime(CLOCK_MONOTONIC, &tbrut1);
	bruteforce(set, set_weight, set_profit, capacity, super_set_size);
	clock_gettime(CLOCK_MONOTONIC, &tbrut2);
        double tbrut = 1000.0*tbrut2.tv_sec + 1e-6*tbrut2.tv_nsec - (1000.0*tbrut1.tv_sec + 1e-6*tbrut1.tv_nsec);
        cout<<tbrut<<endl;

                 p = 0;
		j+=count;

       }  

          
}
