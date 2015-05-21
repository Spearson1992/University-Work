
#include <iostream>
#include "BinaryImage.h"
#include <math.h>
//#include <vld.h>

extern double* readTXT(char *fileName, int sizeR, int sizeC);
extern void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);
extern void WritePGM(char *filename, unsigned char *data, int sizeR, int sizeC, int Q);


double normalisedCorellation(Matrix<double> inputA, Matrix<double> inputB)
{
    double inputAMean = 0, inputBMean = 0;
    //compute mean for a and b
    for(int i = 0; i < inputA.getSize(); i++)
    {
        inputBMean += inputB.get(i);
        inputAMean += inputA.get(i);
    }
    inputAMean /= inputA.getSize();
    inputBMean /= inputB.getSize();

    //subtract  means from a and b
    for(int i = 0; i < inputA.getSize(); i++)
    {
        inputA.set(i, inputA.get(i) - inputAMean);
        inputB.set(i, inputB.get(i) - inputBMean);
    }

    double sumA = 0, sumB= 0, sumAxB = 0;
    //sum the squares
    for(int i = 0; i < inputA.getSize(); i++)
    {
        sumA += inputA.get(i) * inputA.get(i);
        sumB += inputB.get(i) * inputB.get(i);
        sumAxB += inputA.get(i) * inputB.get(i);
    }
    return sumAxB / sqrt((sumA * sumB));
}

void task1FromNoisy()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                      Initialise image size and read in images from files                    //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    int m = 512;
	int n = 512;
	double *shuffledData = 0;
    char* filePath = "Images\\logo_shuffled.txt";
    cout << "Reading shuffled image from " << filePath << " \n";
    shuffledData = readTXT(filePath,m,n);
    cout << "Finished reading shuffled image \n";
    char* noisyLogo = "Images\\logo_with_noise.txt";
    cout << "Reading noisy image from " << noisyLogo << " \n";
    double* noisyData = readTXT(noisyLogo,m,n);
    //WritePGM("Images\\Shuffled_logo_test.pgm",inputData,m,n,255);
    cout << "Finished reading noisy image \n";
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Create matrices                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Matrix<double> *shuffled= new Matrix<double> (m,n, readTXT(filePath,m,n));
    Matrix<double> *noisyImage = new Matrix<double>(m,n,readTXT(noisyLogo,m,n)); 
	delete [] shuffledData;
    delete [] noisyData;
    noisyData = 0;
	shuffledData = 0;
    cout << "Assigned data to matrices and cleared temporary arrays \n";
    cout << "Created binary image and saved it \n";
    Matrix<double> *sorted = new Matrix<double>(m,n);
    cout << "Created matrix for final sorted image \n";
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Temporary stores                                           //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Matrix<double> diff;
    Matrix<double> shuffledTemp;
    Matrix<double> noisyTemp;
    double lowest = 1000000000000000000;
    int lowestK = 0, lowestL = 0;
    int noisyRows = (noisyImage->getRows() - 31), noisyColumns = (shuffled->getColumns() - 31),
        shuffledRows = (shuffled->getRows() - 31), shuffledColumns = (shuffled->getColumns() - 31);
    cout << "Created temporary stores\n";

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Main execution loops                                       //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < noisyRows; i +=32)
        for(int j = 0; j < noisyColumns; j += 32)
        {
            //cout << i << " \n";
            lowest = 1000000000000000000;
            noisyTemp = noisyImage->getBlock(i, i+32, j, j+32);
            for(int k = 0; k < shuffledRows; k += 32)
                for(int l = 0; l < shuffledColumns; l += 32)
                {
                    shuffledTemp = shuffled->getBlock(k, k + 32, l, l+32);
                    diff = noisyTemp - shuffledTemp;
                    diff = diff * diff;
                    double temp = diff.sum();
                    /*This conditional was really annoying, it kept messing up the sorted image
                      fixed by setting lowest to a large value that there's no chance of the ssd
                      exceeding*/
                    /*if(lowest == 0)
                       lowest = temp;*/
                    if(temp < lowest)
                    {
                        lowest = temp;
                        lowestK = k;
                        lowestL = l;
                    }
                }
            shuffledTemp = shuffled->getBlock(lowestK, lowestK + 32, lowestL, lowestL+32);
            sorted->setBlock(i, i+32,j, j + 32, shuffledTemp.getData());
        }
        WritePGM("Images\\logo_sorted.pgm",sorted->getData(),m,n,255);
    delete shuffled;
    delete noisyImage;
    delete sorted;
}

void task1FromBinary()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                      Initialise image size and read in images from files                    //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    int m = 512;
	int n = 512;
	double *shuffledData = 0;
    char* filePath = "Images\\logo_shuffled.txt";
    cout << "Reading shuffled image from " << filePath << " \n";
    shuffledData = readTXT(filePath,m,n);
    cout << "Finished reading shuffled image \n";
    char* noisyLogo = "Images\\logo_with_noise.txt";
    char* savedImage ="Images\\logo_without_noise.pgm";
    cout << "Reading noisy image from " << noisyLogo << " \n";
    double* noisyData = readTXT(noisyLogo,m,n);
    //WritePGM("Images\\Shuffled_logo_test.pgm",inputData,m,n,255);
    cout << "Finished reading noisy image \n";

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Create matrices                                              //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    binaryImage *noiseless = new binaryImage(m,n,noisyData,180);
    binaryImage *shuffled = new binaryImage(m,n,shuffledData,180);
    WritePGM("Images\\noiseless.pgm",noiseless->getData(),m,n,1);
    WritePGM("Images\\shuffled_noiseless.pgm",shuffled->getData(),m,n,1);
    delete [] shuffledData;
    delete [] noisyData;
    noisyData = 0;
	shuffledData = 0;
    cout << "Assigned data to matrices and cleared temporary arrays \n";
    cout << "Created binary image and saved it \n";
    binaryImage *sorted = new binaryImage(m,n, 180);
    cout << "Created matrix for final sorted image \n";
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Temporary stores                                           //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    binaryImage diff;
    binaryImage shuffledTemp;
    binaryImage noisyTemp;
    double lowest;
    int lowestK = 0, lowestL = 0;
    int noisyRows = (noiseless->getRows() - 31), noisyColumns = (noiseless->getColumns() - 31),
        shuffledRows = (shuffled->getRows() - 31), shuffledColumns = (shuffled->getColumns() - 31);
    cout << "Created temporary stores\n";

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //                                  Main execution loops                                       //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < noisyRows; i +=32)
        for(int j = 0; j < noisyColumns; j += 32)
        {
            //cout << i << " \n";
            lowest = 1000000000000000000;
            noisyTemp = noiseless->getBlock(i, i+32, j, j+32);
            for(int k = 0; k < shuffledRows; k += 32)
                for(int l = 0; l < shuffledColumns; l += 32)
                {
                    shuffledTemp = shuffled->getBlock(k, k + 32, l, l+32);
                    diff = (noisyTemp - shuffledTemp);
                    diff = diff * diff;
                    double temp = diff.sum();
                    /*if(lowest == 0)
                    {
                       lowest = temp;
                        lowestK = k;
                        lowestL = l;
                    }*/
                    if(temp < lowest)
                    {
                        lowest = temp;
                        lowestK = k;
                        lowestL = l;
                    }
                }
            shuffledTemp = shuffled->getBlock(lowestK, lowestK + 32, lowestL, lowestL+32);
            sorted->setBlock(i, i+32,j, j + 32, shuffledTemp.getData());
        }
        WritePGM("Images\\logo_sorted_from_noiseless.pgm",sorted->getData(),m,n,1);
    delete shuffled;
    delete noiseless;
    delete sorted;
}

void task2()
{
    int rows = 768, columns = 1024, wallyRows = 49, wallyColumns = 36;
    double *clutteredScene = 0, *wally = 0;
    clutteredScene = readTXT("Images\\Cluttered_scene.txt",rows,columns);
    wally = readTXT("Images\\Wally_grey.txt",wallyRows, wallyColumns);
    WritePGM("Images\\ClutteredScene.pgm",clutteredScene,rows,columns,255);
    Matrix<double> *scene = new Matrix<double>(rows, columns, clutteredScene);
    Matrix<double> *wallyMat = new Matrix<double> (wallyRows, wallyColumns, wally);
    Matrix<double> sceneTemp;
    double nc = -1;
    double closestMatch = 0;
    int iClosest = 0, jClosest = 0;


    delete [] clutteredScene;
    delete [] wally;
    clutteredScene = 0;
    wally = 0;

    for(int i = 0; i < (rows - wallyRows); i++)
        for(int j = 0; j < (columns - wallyColumns); j++)
        {
            //cout << i << " " << j << "\n";
            sceneTemp = scene->getBlock(i,i+wallyRows,j,j+wallyColumns);
            nc = normalisedCorellation(sceneTemp, *wallyMat);
            if(nc > closestMatch)
            {
                closestMatch = nc;
                iClosest = i;
                jClosest = j;
            }
        }
        cout << "Wally found \n";
        cout << "Removing wally \n";
        scene->setBlock(iClosest, iClosest + wallyRows, jClosest, jClosest + wallyColumns, 0.0);
        cout << "Wally removed \n";
        cout << "Writing image \n";
        WritePGM("Images\\wally_removed.pgm",scene->getData(),rows,columns,255);
        cout << "Image written \n";
        delete scene;
        delete wallyMat;
        
}
int main()
{
	cout << "Executing task1 using noisy image \n";
    task1FromNoisy();
    cout << "Executing task1 using binary image \n";
    task1FromBinary();
    cout << "Finding wally \n";
    task2();
	std::cin.get();
}