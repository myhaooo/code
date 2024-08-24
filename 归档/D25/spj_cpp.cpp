#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>

const int MAX_N = 1000005;

bool vis[MAX_N];
int A[MAX_N], N = -1;

int main(int argc, char *argv[]) {
	std::ifstream fin("input");
    std::ifstream fstd("answer");
	std::ifstream fout("user_out");
	
	fin>>N;	

  	for (int i = 1; i <= N; ++i)
		fin>>A[i];    	

  	int sum = 0, score = 100;
  	static int M;
	
	if (!(fout >> M)) {
                std::cerr << "Can't read the number" << std::endl;
                std::cout << 0 << std::endl;
                exit(0);
        }
	if (M <= 0) {
		std::cerr << "M <= 0" << std::endl;
        std::cout << 0 << std::endl;
        exit(0);
	}


  	if (M == -1) {
		std::cerr << "Wrong Answer M = -1" << std::endl;
                std::cout << 0 << std::endl;
                exit(0);
	}
  
  	for (int i = 1, pos; i <= M; ++i) {
    		if (!(fout >> pos)) {
			std::cerr << "Can't read the number" << std::endl;
	                std::cout << 0 << std::endl;
        	        exit(0);
		}
    		if (vis[pos]) {
			std::cerr << "Number " << pos << " have already appeared" << std::endl;
	                std::cout << 0 << std::endl;
        	        exit(0);
		}
    		sum = (sum + A[pos]) % N, vis[pos] = 1;
  	}

  	if (sum != 0) {
		std::cerr << "Wrong Answer sum != 0" << std::endl;
                std::cout << 0 << std::endl;
                exit(0);
	}
	std::cout << 100 << std::endl;
	return 0;
}
