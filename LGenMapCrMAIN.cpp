#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include "mapcr.h"
using namespace std;

FILE* STDOUT=stdout;

signed main(int argc, char** argv) {
	/*** if any of these below is commented, it means it's currently unavailable. ***/
	/* special maps */
	gene_random("random_map.txt",argc>1?atoi(argv[1]):25);
	gene_allcity("allcity_map.txt",argc>1?atoi(argv[1]):25,argc>2?atoi(argv[2]):40);
	gene_allswamp("allswamp_map.txt",argc>1?atoi(argv[1]):25);
	gene_allplain("allplain_map.txt",argc>1?atoi(argv[1]):25);
	/* dlk series */
	gene_dlk();
	gene_dlk_wtcz();
	gene_dlk2();
	gene_dlk3();
	gene_dlk4();
	gene_dlk5();
	// gene_dlk6();
	gene_dlk7();
	// gene_dlk8();
	gene_dlk9();
	// gene_dlk9_wtcz();
	gene_dlk10();
	gene_dlk11();
	// gene_dlk12();
	gene_dlk13();
	gene_dlk14();
	gene_dlk15();
	// gene_dlk16();
	// gene_dlk17();
	gene_dlk18();
	gene_dlk19();
	return 0;
}

