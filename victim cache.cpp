#include <bits/stdc++.h>
using namespace std;
 
typedef long long int ll;
typedef long double ld;
typedef unsigned long long int ull;
typedef vector <ll> ve;
typedef vector <ve> vee;
#define FOR(i,vv,n) for(ll i=vv;i<n;i++)
#define FORR(i,n,vv) for(ll i=n-1;i>=vv;i--)
#define maxe(v) *max_element(v.begin(),v.end())
#define mine(v) *min_element(v.begin(),v.end())
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mp make_pair
#define M 1000000007
#define precise cout.precision(18)

int main()
{
	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); 	
    freopen("output.txt", "w", stdout);
	#endif
	FAST

	//Start
	cout<<"VICTIM CACHE"<<endl;
	cout<<"Memory is byte addressable"<<endl;

	//Memory Size
	cout<<"Enter Size of Main Memory in Bytes : ";
	ll main_memory_size;
	cin>>main_memory_size;
	cout<<main_memory_size<<endl;

	//Address Size	
	ll physical_address=(ll)log2(main_memory_size); 

	//Size Of L1 Cache
	cout<<"Enter Size of L1 Cache in Bytes : ";
	ll l1_cache_size;
	cin>>l1_cache_size;
	cout<<l1_cache_size<<endl;

	//Size Of Victim Cache
	cout<<"Enter Size of Victim Cache in Bytes : ";
	ll victim_cache_size;
	cin>>victim_cache_size;
	cout<<victim_cache_size<<endl;

	//Block Size
	cout<<"Enter Block Size in Bytes : ";
	ll block_size;
	cin>>block_size;
	cout<<block_size<<endl;

	//Lines In Main Memory
	ll lines_in_main_memory=(main_memory_size/block_size);

	//Lines In L1 Cache
	ll lines_in_l1_cache=(l1_cache_size/block_size);
	
	//Lines In Victim Cache
	ll lines_in_victim_cache=(victim_cache_size/block_size);

	//Block_offset/Word
	ll block_offset=(ll)log2(block_size);

	//Cache_Index/Line
	ll cache_index=(ll)log2(lines_in_l1_cache);

	//Tag
	ll tag=physical_address-cache_index-block_offset;
	
	// Creating Main Memory
	ll main_memory[lines_in_main_memory][block_size];

	//Initializing Main Memory(can be any integer less than 10^18)
	for(ll i=0;i<lines_in_main_memory;i++)
		for(ll j=0;j<block_size;j++)
			main_memory[i][j]=i*block_size+j; //Sequential Assiging Main Memory
///main_memory[i][j]=j*block_size+i;

	// Creating L1 Cache
	ll l1_cache[lines_in_l1_cache][block_size];

	// Creating Tag array OF L1 Cache
	ll tag_array_of_l1_cache[lines_in_l1_cache];
	
 	// Creating Valid Array Of L1 Cache
	ll valid_array_l1[lines_in_l1_cache];
	memset(valid_array_l1,0,sizeof(valid_array_l1));

	//Creating Victim Cache 
	ll victim_cache[lines_in_victim_cache][block_size];
	
	// Creating Tag Array OF Victim Cache
	ll tag_array_of_victim_cache[lines_in_victim_cache];
	
	// Creating Valid Array Of Victim
	ll valid_array_victim[lines_in_victim_cache];
	memset(valid_array_victim,0,sizeof(valid_array_victim));

	// LRU Counter
	ll LRU_in_victim_cache[lines_in_victim_cache];
	for(ll i=0;i<lines_in_victim_cache;i++)
		LRU_in_victim_cache[i]=i;

	// parameters to evaluate
	ll number_of_hits_l1=0;
	ll number_of_misses_l1=0;
	ll number_of_hits_victim=0;
	ll number_of_misses_victim=0;

	cout<<"Physical address is of "<<physical_address<<" bits."<<endl;
	cout<<"Tag is of "<<tag<<" bits."<<endl;
	cout<<"Cache Index is of "<<cache_index<<" bits."<<endl;
	cout<<"Block Offset is of "<<block_offset<<" bits."<<endl;
	cout<<"Enter number of Queries : ";


	// L1 cache is direct mapped
	// victim cache is fully associative

	// addresses to search
	ll queries;
	cin>>queries;
	cout<<queries<<endl;

	cout<<"Address And Values Fetched Are Following "<<endl;
	while(queries--)
	{
		string query;
		cin>>query;


		ll query_offset=0;
		ll query_index=0;
		ll query_tag_l1=0;
		ll query_tag_victim=0;
		ll counter=1;
		// calculating offset/word value
		for(ll i=physical_address-1;i>=tag+cache_index;i--)
		{
			query_offset+=((ll)query[i]-(ll)'0')*counter;
			counter*=2;
		}
		counter=1;

		// calculating index/line value
		for(ll i=tag+cache_index-1;i>=tag;i--)
		{
			query_index+=((ll)query[i]-(ll)'0')*counter;
			counter*=2;
		}
		counter=1;
		
		// calculating tag value of L1 cache
		for(ll i=tag-1;i>=0;i--)
		{
			query_tag_l1+=((ll)query[i]-(ll)'0')*counter;
			counter*=2;
		}
		counter=1;

		//calcuating tag value for victim cache
		for(ll i=tag+cache_index-1;i>=0;i--)
		{
			query_tag_victim+=((ll)query[i]-(ll)'0')*counter;
			counter*=2;
		}
		counter=1;


		//Operations


		if(valid_array_l1[query_index]==1) // true if  line of l1 cache contains some data 
		{
			if(tag_array_of_l1_cache[query_index]==query_tag_l1) // true if line of l1 cache contains required address
			{
				number_of_hits_l1++;
				cout<<query<<" : ";cout<<l1_cache[query_index][query_offset]<<endl;
			}
			else  //if line of l1 cache don't contain required data
			{
				ll counter2=0;
				number_of_misses_l1++;

				// going inside victim cache
				for(ll i=0;i<lines_in_victim_cache&&counter2==0;i++) //searching for every line in victim cache
				{

					if(valid_array_victim[i]==1 && tag_array_of_victim_cache[i]==query_tag_victim)
						// if line of victim contains some data and that line contains required address
						{
							counter2++;
						number_of_hits_victim++;
						
						// transferring found block to l1 cache and replacing that with of L1 cache 

							//swap valid bit
							swap(valid_array_l1[query_index],valid_array_victim[i]);
							
							// udating tag array of l1 and victim
							ll temp=tag_array_of_l1_cache[query_index]*pow(2,query_index)+query_index;
							tag_array_of_l1_cache[query_index]=query_tag_l1;
							tag_array_of_victim_cache[i]=temp;
							
							// swap address value
							for(ll i1=0;i1<block_size;i1++){
								swap(l1_cache[query_index][i1],victim_cache[i][i1]);
							}

							// updating LRU array for furthur action
							for(ll i2=0;i2<lines_in_victim_cache;i2++){
								if(LRU_in_victim_cache[i2]<LRU_in_victim_cache[i])
									LRU_in_victim_cache[i2]++;
							}	
							LRU_in_victim_cache[i]=0;
								
							cout<<query<<" : ";cout<<l1_cache[query_index][query_offset]<<endl;
						}
				}

				if(counter2==0){
					// if required address not found in victim cache

					number_of_misses_victim++;

					//going inside RAM

					//finding suitable block in victim cache to hold required value
					for(ll i=0;i<lines_in_victim_cache&&counter2==0;i++){
						if(LRU_in_victim_cache[i]==lines_in_victim_cache-1){
							
							//found suitable line in victim cache to replace

							counter2++;

							// transfering block form Ram to victim cache
							tag_array_of_victim_cache[i]=query_tag_victim;
								for(ll i1=0;i1<block_size;i1++){
								victim_cache[i][i1]=main_memory[query_tag_victim][i1];
							}
							valid_array_victim[i]=1;

							//updating LRU array for furthur functions
							for(ll i2=0;i2<lines_in_victim_cache;i2++){
								if(LRU_in_victim_cache[i2]<LRU_in_victim_cache[i])
									LRU_in_victim_cache[i2]++;
							}	
							LRU_in_victim_cache[i]=0;

						}
					}


					//tranfering block of required data from victim cache to l1 cache
					for(ll i=0;i<lines_in_victim_cache;i++)
					{
					if(valid_array_victim[i]==1 && tag_array_of_victim_cache[i]==query_tag_victim)

						{
							
							//swaping blocks of l1 and victim cache
							swap(valid_array_l1[query_index],valid_array_victim[i]);
							
							ll temp=tag_array_of_l1_cache[query_index]*pow(2,query_index)+query_index;
							tag_array_of_l1_cache[query_index]=query_tag_l1;
							tag_array_of_victim_cache[i]=temp;
							
							for(ll i1=0;i1<block_size;i1++){
								swap(l1_cache[query_index][i1],victim_cache[i][i1]);
							}
								
							cout<<query<<" : ";cout<<l1_cache[query_index][query_offset]<<endl;
						}
					}
				}

			}
		}
		else
		{
			// if there is no data present in line of L1 cache
			ll counter2=0;
				number_of_misses_l1++;

				//going inside victim cache
				for(ll i=0;i<lines_in_victim_cache&&counter2==0;i++)
				{
					if(valid_array_victim[i]==1 && tag_array_of_victim_cache[i]==query_tag_victim)

						{	
							// if require address is found in victim cache
							counter2++;
						number_of_hits_victim++;
						
						
						// swaping block of L1 cache with victim cache
							swap(valid_array_l1[query_index],valid_array_victim[i]);
							
							tag_array_of_l1_cache[query_index]=query_tag_l1;
							tag_array_of_victim_cache[i]=0;
							for(ll i1=0;i1<block_size;i1++){
								swap(l1_cache[query_index][i1],victim_cache[i][i1]);
							}

							//updating LRU for victim cache
							for(ll i2=0;i2<lines_in_victim_cache;i2++){
								if(LRU_in_victim_cache[i2]<LRU_in_victim_cache[i])
									LRU_in_victim_cache[i2]++;
							}	
							LRU_in_victim_cache[i]=0;
								
							cout<<query<<" : ";cout<<l1_cache[query_index][query_offset]<<endl;
						}
				}
							if(counter2==0){
								// if required address is not found in victim cache
					number_of_misses_victim++;

					// finding suitable line in victim cache to fetch block of ram to victim
					for(ll i=0;i<lines_in_victim_cache&&counter2==0;i++){
						if(LRU_in_victim_cache[i]==lines_in_victim_cache-1){
							counter2++;


							// found suitable line in victim cache

							// copying data from RAM to Victim Cache
							tag_array_of_victim_cache[i]=query_tag_victim;
								for(ll i1=0;i1<block_size;i1++){
								victim_cache[i][i1]=main_memory[query_tag_victim][i1];
							}
							valid_array_victim[i]=1;

							// updating LRU array
							for(ll i2=0;i2<lines_in_victim_cache;i2++){
								if(LRU_in_victim_cache[i2]<LRU_in_victim_cache[i])
									LRU_in_victim_cache[i2]++;
							}	
							LRU_in_victim_cache[i]=0;

						}
					}

					// swaping block of L1 and victim cache
					for(ll i=0;i<lines_in_victim_cache;i++)
					{
					if(valid_array_victim[i]==1 && tag_array_of_victim_cache[i]==query_tag_victim)

						{
							
							swap(valid_array_l1[query_index],valid_array_victim[i]);
							
							tag_array_of_l1_cache[query_index]=query_tag_l1;
							tag_array_of_victim_cache[i]=0;
							for(ll i1=0;i1<block_size;i1++){
								swap(l1_cache[query_index][i1],victim_cache[i][i1]);
							}
								
							cout<<query<<" : ";cout<<l1_cache[query_index][query_offset]<<endl;
						}
					}


				}

		}
	}
 
cout<<"number_of_hits_l1 : "<<number_of_hits_l1<<endl;
cout<<"number_of_misses_l1 : "<<number_of_misses_l1<<endl;
cout<<"number_of_hits_victim : "<<number_of_hits_victim<<endl;
cout<<"number_of_misses_victim : "<<number_of_misses_victim<<endl;
	return 0;
}