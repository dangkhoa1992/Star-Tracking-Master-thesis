#ifndef ALGORITHM_
#define ALGORITHM_
#include <vector>
#include <cmath>
#include <algorithm>
struct Star {
	int X;
	int Y;
	double starDistance2Centre;
	double starDistance2StarRef;
};

struct StarPattern {
	int N;
	int d1;
	int d2;
	int d3;
	int starID;
	double sqError;
};

std::vector<Star> chooseStarRef(int *X, int *Y, unsigned centroidCount, int imgHeight, int imgWidth) {
	std::vector<Star> starList;
	for(int i = 0; i < (int)centroidCount; ++i)
		starList.push_back({X[i], Y[i], sqrt((X[i] - imgHeight/2)*(X[i] - imgHeight/2) + (Y[i] - imgWidth/2)*(Y[i] - imgWidth/2)),0});
	std::make_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2Centre > b.starDistance2Centre; });
	return starList;
}

StarPattern getStarPattern(std::vector<Star> &starList,int FOV) {
	StarPattern starPattern;

	//Calculate the star distance to starRef
	Star starRef = starList.front();
	std::pop_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2Centre > b.starDistance2Centre; });
	starList.pop_back();

	for (int i = 0; i < (int)starList.size(); ++i)
		starList[i].starDistance2StarRef = sqrt((starRef.X - starList[i].X)*(starRef.X - starList[i].X) + (starRef.Y - starList[i].Y)*(starRef.Y - starList[i].Y));
	std::make_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2StarRef > b.starDistance2StarRef; });

	//Traverse through the sorted list to get star pattern
	int count = 0;
	float distance[3] = { 0,0,0 };

	while (!starList.empty()) {
		if (starList.front().starDistance2StarRef > FOV / 2) break;
		if (count < 3) distance[count] = starList.front().starDistance2StarRef;

		std::pop_heap(starList.begin(), starList.end(), [](const Star &a, const Star &b) {return a.starDistance2StarRef > b.starDistance2StarRef; });
		starList.pop_back();
		++count;
	}

	//Update Starpattern
	starPattern.N = count;
	starPattern.d1 = distance[0];
	starPattern.d2 = distance[1];
	starPattern.d3 = distance[2];

	return starPattern;
}



#endif
