#include "PerlinGenerator.h"
#include <vector>
#include <ctime>

PerlinGenerator::PerlinGenerator()
{
	newPerm();
}

void PerlinGenerator::newPerm()
{
	int permutations[256];
	std::vector<int> set;
	for (int a = 0; a < 256; a++)
	{
		set.emplace_back(a);
	}
	srand(time(0));

	int counter = 0;
	while (set.size() > 0)
	{
		int ni = rand() % set.size();

		permutations[counter] = set[ni];
		set.erase(set.begin() + ni);
		counter++;
	}
	for (int a = 0; a < 256; a++)
	{
		p[a + 256] = p[a] = permutations[a];
	}
}

double PerlinGenerator::noise(double x, double y)
{
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	x -= floor(x);
	y -= floor(y);
	double u = fade(x), v = fade(y);
	int AA = p[p[X] + Y], AB = p[p[X] + Y + 1];
	int BA = p[p[X + 1] + Y], BB = p[p[X + 1] + Y + 1];

	return lerp(v, lerp(u, gradiate(p[AA], x, y), gradiate(p[BA], x - 1, y)), 
		           lerp(u, gradiate(p[AB], x, y - 1), gradiate(p[BB], x - 1, y - 1)));
}

double PerlinGenerator::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinGenerator::lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

double PerlinGenerator::gradiate(int hash, double x, double y)
{
	switch (hash & 0xF)
	{
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  y;
	case 0x5: return -y;
	case 0x6: return  x;
	case 0x7: return -x;
	case 0x8: return   -x - y;
	case 0x9: return  y;
	case 0xA: return  x - y;
	case 0xB: return x + y;
	case 0xC: return  -x + y;
	case 0xD: return -y;
	case 0xE: return  x;
	case 0xF: return -x;
	}
	return 0;
}