#include "Fractal.h"
#include <cmath>

//-------- class Fractal --------//

/**
 * @brief sets the abstract fractal to hold the dimensions it must have, called only from one of
 * it's sons
 * @param dims the dimensions of the fractal
 */
Fractal::Fractal(int dims) : dimensions(dims)
{
}

/**
 * @brief this resets the vector to the wanted size, with the value of not printing anything
 * in each cell
 * @param size the size of the wanted vector (will be set to size*size)
 */
void Fractal::resetVector(int size)
{
    f.resize(size);
    for (int i = 0; i < size; i++)
    {
        f[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            f[i][j] = NOT_DROW;
        }
    }
}

/**
 * @brief sets the vector to hold the whole fractal, recursively
 * @param rowIdx the row index to start filling at
 * @param colIdx the column index to start filling at
 * @param thisSize the root size of the current fractal's smallest size (when dim=1)
 * @param dims the dimension of the wanted fractal
 * @param places the points that should be filled (at the dimension of 1, for other
 * dimensions must be multiplied)
 * @param pointNum the number of points in @param places
 */
void Fractal::setVector(int rowIdx, int colIdx, int thisSize, int dims, const Point *places, int
                        pointNum)
{
    if (dims == 0)
    {
        f[rowIdx][colIdx] = TO_DROW;
    }
    else
    {
        dims = dims - 1;
        int diff_idx = std::pow(thisSize, dims);
        for (int i = 0; i < pointNum; i++)
        {
            Point point = places[i];
            setVector(rowIdx + diff_idx * point.row, colIdx + diff_idx * point.col, thisSize,
                      dims, places, pointNum);
        }
    }
}

/**
 * @brief prints the fractal
 * @param size the root size of the fractal
 */
void Fractal::toPrint(int size) const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << f[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//-------- class SierpinskiCarpet --------//

/**
 * @brief the constructor of this class, which resets the dimensions and vector as given from
 * the user
 * @param dims the dimensions of the fractal
 */
SierpinskiCarpet::SierpinskiCarpet(int dims) : Fractal(dims)
{
    resetVector(std::pow(CARPET_SIZE, dimensions));
}

/**
 * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
 */
void SierpinskiCarpet::makeAndPrint()
{
    setVector(0, 0, CARPET_SIZE, dimensions, _points, CARPET_NUM_POINTS);
    toPrint(std::pow(CARPET_SIZE, dimensions));
}

//-------- class SierpinskiTriangle --------//

/**
 * @brief the constructor of this class, which resets the dimensions and vector as given from
 * the user
 * @param dims the dimensions of the fractal
 */
SierpinskiTriangle::SierpinskiTriangle(int dims) : Fractal(dims)
{
    resetVector(std::pow(TRIANGLE_SIZE, dimensions));
}

/**
 * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
 */
void SierpinskiTriangle::makeAndPrint()
{
    setVector(0, 0, TRIANGLE_SIZE, dimensions, _points, TRIANGLE_NUM_POINTS);
    toPrint(std::pow(TRIANGLE_SIZE, dimensions));
}

//-------- class VicsekFractal --------//

/**
 * @brief the constructor of this class, which resets the dimensions and vector as given from
 * the user
 * @param dims the dimensions of the fractal
 */
VicsekFractal::VicsekFractal(int dims) : Fractal(dims)
{
    resetVector(std::pow(VICSEK_SIZE, dimensions));
}

/**
 * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
 */
void VicsekFractal::makeAndPrint()
{
    setVector(0, 0, VICSEK_SIZE, dimensions, _points, VICSEK_NUM_POINTS);
    toPrint(std::pow(VICSEK_SIZE, dimensions));
}

//-------- class FractalFactory --------//

/**
 * @brief the static method that makes the fractal from the given index and dimension
 * @param index the index of the wanted fractal, should be from 1 to 3
 * @param dims the dimensions of the wanted fractal, should be from 1 to 6
 * @note there is memory allocated in this method that should be freed!
 */
Fractal *FractalFactory::makeFractal(int index, int dims)
{
    if (index == CARPET_INDEX)
    {
        return new SierpinskiCarpet(dims);
    }
    if (index == TRIANGLE_INDEX)
    {
        return new SierpinskiTriangle(dims);
    }
    if (index == VICSEK_INDEX)
    {
        return new VicsekFractal(dims);
    }
    // this won't happen because we validate the information before we send it here
    exit(EXIT_FAILURE);
}



