#include <iostream>
#include "debug.h"
#include "ssevec.h"
#include "ssemat44.h"

using namespace std;
using namespace gofxmath;

namespace gofxengine
{
	void PrintGofFofXMatrix(const SseMat44& mat)
	{
		array<float, 16> matArr = MatrixToArray(mat);

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				printf("% 3.5f ", matArr[i * 4 + j]);
			}
			cout << endl;
		}

		cout << endl;
	}

    void PrintGofFofXMatrix(const Mat44& mat)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                printf("% 3.5f ", mat.m[i][j]);
            }
            cout << endl;
        }

        cout << endl;
    }

	void PrintMat4WithHeader(const string& header, const Mat44& toPrint)
	{
		cout << header << endl << endl;
		PrintGofFofXMatrix(toPrint);
		cout << endl;
	}

	void PrintMat4WithHeader(const string& header, const SseMat44& toPrint)
	{
		cout << header << endl << endl;
		PrintGofFofXMatrix(toPrint);
		cout << endl;
	}

	void PrintSseVecWithHeader(const string& header, const SseVec& vec)
	{
		cout << header << endl << endl;
		PrintSseVec4(vec);
		cout << endl;
	}
}