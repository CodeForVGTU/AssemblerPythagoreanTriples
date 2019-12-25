#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int total = 0; // counting how many Pythagorean triples we will get
	float x[4]; // x value
	float y[4]; // y value
	float z[4]; // final z value
	float sub[4]; // skirtumas


	ofstream file;
	file.open("Pythagorean_Triples.txt");
	file << "Pythagorean Triples\nx^2 + y^2 = z^2 (x & y are in interval{1, ..., 1000})\n\n";

	for (float i = 1; i <= 1000; i += 4)
	{
		x[0] = i, x[1] = i + 1, x[2] = i + 2, x[3] = i + 3;

		for (float j = i + 1; j <= 1000; j++)
		{
			y[0] = j, y[1] = j + 1, y[2] = j + 2, y[3] = j + 3;

			_asm {
				// x value are added to xmm0 register and y value are adeed to xmm1 register
				movups xmm0, [x] // first writing: xmm0 = {1, 2, 3, 4} 
				movups xmm1, [y] // first writing: xmm1 = {2, 3, 4, 5}

				// SQUARE of x & y
				mulps xmm0, xmm0 // xmm0^2
				mulps xmm1, xmm1 // xmm1^2

				// addition
				addps xmm0, xmm1 //xmm0 = xmm0 + xmm1

				// SQUARE ROOT
				sqrtps xmm1, xmm0 //xmm1 = sqrt(xmm0)

				// ROUND
				roundps xmm1, xmm1, 1 // ROUND xmm1 to integer
				movups[z], xmm1
				mulps xmm1, xmm1 // SQUARE

				// get SUBSTRACTION
				subps xmm0, xmm1 // SUBSTRACTION
				movups[sub], xmm0 // move SUBSTRACTION value to sub
			}
			for (int k = 0; k < 4; k++)
			{
				if (sub[k] == 0) // if after SUBSTRACTION we got 0, number is Pythagorean!
				{
					file << x[k] << "^2 + " << y[k] << "^2 = " << z[k] << "^2\n";
					total++;
				}
			}
		}
	}
	file << endl << "Total number of Pythagorean Triples: " << total;
	file.close();
	cout << "Pythagorean Triples are written to file!\n";
}
