#pragma once

class PerlinGenerator
{
private:
	int p[512];
public:
	PerlinGenerator();

	void newPerm();

	double noise(double x, double y);
	double fade(double t);
	double lerp(double t, double a, double b);
	double gradiate(int hash, double x, double y);
};