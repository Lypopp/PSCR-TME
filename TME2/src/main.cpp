#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <string>
#include <algorithm>
#include <vector>
#include "FreqMap.h"

// helper to clean a token (keep original comments near the logic)
static std::string cleanWord(const std::string& raw) {
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	static const std::regex re( R"([^a-zA-Z])");
	// élimine la ponctuation et les caractères spéciaux
	std::string w = std::regex_replace(raw, re, "");
	// passe en lowercase
	std::transform(w.begin(), w.end(), w.begin(), ::tolower);
	return w;
}

void sortAndPrintTop(std::vector<WordCount>& counts, size_t topN = 10){
	std::sort(counts.begin(), counts.end(), [] (WordCount a, WordCount b) {return a.second > b.second;});
	for (size_t i = 0 ; i < topN ; i++){
		std::cout << i + 1 << ". " << counts[i].first << std::endl;
	}
}

int main(int argc, char** argv) {
	using namespace std;
	using namespace std::chrono;

	// Allow filename as optional first argument, default to project-root/WarAndPeace.txt
	// Optional second argument is mode (e.g. "count" or "unique").
	string filename = "../WarAndPeace.txt";
	string mode = "count";
	if (argc > 1) filename = argv[1];
	if (argc > 2) mode = argv[2];

	ifstream input(filename);
	if (!input.is_open()) {
		cerr << "Could not open '" << filename << "'. Please provide a readable text file as the first argument." << endl;
		cerr << "Usage: " << (argc>0?argv[0]:"countword") << " [path/to/textfile]" << endl;
		return 2;
	}
	cout << "Parsing " << filename << " (mode=" << mode << ")" << endl;

	auto start = steady_clock::now();

	// prochain mot lu
	string word;

	if (mode == "count") {
		size_t nombre_lu = 0;

		// default counting mode: count total words
		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			// un token sans aucune lettre (e.g. "--" ou "1812") devient vide : on l'ignore
			if (word.empty()) continue;

			// word est maintenant "tout propre"
			if (nombre_lu % 100 == 0)
				// on affiche un mot "propre" sur 100
				cout << nombre_lu << ": "<< word << endl;
			nombre_lu++;
		}
	input.close();
	cout << "Finished parsing." << endl;
	cout << "Found a total of " << nombre_lu << " words." << endl;

	} else if (mode == "unique") {
		// skeleton for unique mode
		// before the loop: declare a vector "seen"
		// TODO
		std::vector<string> seen;

		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// add to seen if it is new
			// TODO
			bool addelt = true;
			for (string& e : seen){
				if (word == e) {
					addelt = false;
					break;
				}
			}
			if (addelt){seen.push_back(word);}
		}
	input.close();
	// TODO
	cout << "Found " << seen.size() << " unique words." << endl;

	} else if (mode == "freq") {
		std::vector<pair<string, int>> seen;

		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// add to seen if it is new
			bool addelt = true;
			for (pair<string, int>& e : seen){
				if (word == e.first) {
					e.second++;
					addelt = false;
					break;
				}
			}
			if (addelt){seen.push_back(make_pair(word, 1));}
		}
	input.close();
	cout << "Found " << seen.size() << " unique words." << endl;
	for (pair<string, int>& e : seen){
		if ("war" == e.first) {
			cout << "War : " << e.second << endl;
		} else if ("peace" == e.first) {
			cout << "Peace : " << e.second << endl;
		} else if ("toto" == e.first) {
			cout << "Toto : " << e.second << endl;
		} 
	}
	sortAndPrintTop(seen);
	

	} else if (mode == "freqstd") {
		std::unordered_map<string,int> seen;

		while (input >> word) {
			// élimine la ponctuation et les caractères spéciaux
			word = cleanWord(word);
			if (word.empty()) continue;

			// add to seen if it is new
			if (seen.find(word) == seen.end()){
				seen[word] = 1;
			} else {
				seen[word]++;
			}
		}
	input.close();
	cout << "Found " << seen.size() << " unique words." << endl;

	if (seen.find("war") != seen.end()){
		cout << "War : " << seen["war"] << endl;
	} else {
		cout << "War : " << 0 << endl;
	}

	if (seen.find("peace") != seen.end()){
		cout << "Peace : " << seen["peace"] << endl;
	} else {
		cout << "Peace : " << 0 << endl;
	}

	if (seen.find("toto") != seen.end()){
		cout << "Toto : " << seen["toto"] << endl;
	} else {
		cout << "Toto : " << 0 << endl;
	}

	
	std::vector<pair<string, int>> seen_vec;
	for (auto& e : seen){
		seen_vec.push_back(e);
	}
	sortAndPrintTop(seen_vec);
	

	} else {
		// unknown mode: print usage and exit
		cerr << "Unknown mode '" << mode << "'. Supported modes: count, unique" << endl;
		input.close();
		return 1;
	}

	// print a single total runtime for successful runs
	auto end = steady_clock::now();
	cout << "Total runtime (wall clock) : " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

	return 0;
}
