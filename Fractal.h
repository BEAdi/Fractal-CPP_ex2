#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H
// ------------------------------ includes ------------------------------
#include <vector>
#include <iostream>
// -------------------------- const definitions -------------------------

/**
 * @brief holds the char that is to be printed if we want to draw the current cell
 */
#define TO_DROW '#'
/**
 * @brief holds the char that is to be printed if we don't want to draw the current cell
 */
#define NOT_DROW ' '

/**
 * @brief the minimum dimension that a fractal can have
 */
#define MIN_DIM (1)
/**
 * @brief the maximum dimension that a fractal can have
 */
#define MAX_DIM (6)

/**
 * @brief the size of a sierpinski carpet of dimension 1 (the lowest that can be)
 */
#define CARPET_SIZE (3)
/**
 * @brief the size of a sierpinski triangle of dimension 1 (the lowest that can be)
 */
#define TRIANGLE_SIZE (2)
/**
 * @brief the size of a vicsek fractal of dimension 1 (the lowest that can be)
 */
#define VICSEK_SIZE (3)

/**
 * @brief the number of points that the sierpinski carpet is filling in every step
 */
#define CARPET_NUM_POINTS (8)
/**
 * @brief the number of points that the sierpinski triangle carpet is filling in every step
 */
#define TRIANGLE_NUM_POINTS (3)
/**
 * @brief the number of points that the vicsek fractal is filling in every step
 */
#define VICSEK_NUM_POINTS (5)

/**
 * @brief the index got from the user that stands for the sierpinski carpet
 */
#define CARPET_INDEX (1)
/**
 * @brief the index got from the user that stands for the sierpinski triangle
 */
#define TRIANGLE_INDEX (2)
/**
 * @brief the index got from the user that stands for the vicsek fractal
 */
#define VICSEK_INDEX (3)

/**
 * @brief the minimum index that represents a fractal
 */
#define MIN_INDEX (1)
/**
 * @brief the maximum index that represents a fractal
 */
#define MAX_INDEX (3)

// ------------------------------ classes -----------------------------
/**
 * @brief This stands for a point in the vector*vector, that is to be filled at the fractal it is
 * held at
 */
struct Point
{
    int row;
    int col;
} typedef Point;

/**
 * @brief the abstract fractal base class
 */
class Fractal
{
protected:
    /**
     * @brief sets the abstract fractal to hold the dimensions it must have, called only from one of
     * it's sons
     * @param dims the dimensions of the fractal
     */
    explicit Fractal(int dims);

    /**
     * @brief the dimensions of the wanted fractal
     */
    int dimensions;

    /**
     * @brief the vector of vectors of chars that holds the fractal itself
     */
    std::vector<std::vector<char>> f;

    /**
     * @brief this resets the vector to the wanted size, with the value of not printing anything
     * in each cell
     * @param size the size of the wanted vector (will be set to size*size)
     */
    void resetVector(int size);

    /**
     * @brief sets the vector to hold the whole fractal
     * @param rowIdx the row index to start filling at
     * @param colIdx the column index to start filling at
     * @param thisSize the root size of the current fractal's smallest size (when dim=1)
     * @param dims the dimension of the wanted fractal
     * @param places the points that should be filled
     * @param pointNum the number of points in @param places
     */
    void setVector(int rowIdx, int colIdx, int thisSize, int dims, const Point *places, int
                   pointNum);

    /**
     * @brief prints the fractal
     * @param size the root size of the fractal
     */
    void toPrint(int size) const;

public:
    /**
     * @brief a method that only the sons have, that makes the fractal and prints it (using other
     * methods as well)
     */
    virtual void makeAndPrint() = 0;

    /**
     * @brief the virtual destructor of the fractal (as it is abstract and base class for other
     * classes)
     */
    virtual ~Fractal() = default;
};

/**
 * @brief the sierpinski carpet fractal that inherits from the fractal class
 */
class SierpinskiCarpet : public Fractal
{
private:
    /**
     * @brief an array of points that are to be filled in this fractal
     */
    const Point _points[CARPET_NUM_POINTS]{{0, 0},
                                     {0, 1},
                                     {0, 2},
                                     {1, 0},
                                     {1, 2},
                                     {2, 0},
                                     {2, 1},
                                     {2, 2}};

public:
    /**
     * @brief the constructor of this class, which resets the dimensions and vector as given from
     * the user
     * @param dims the dimensions of the fractal
     */
    explicit SierpinskiCarpet(int dims);

    /**
     * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
     */
    void makeAndPrint() override;
};

/**
 * @brief the sierpinski triangle fractal that inherits from the fractal class
 */
class SierpinskiTriangle : public Fractal
{
private:
    /**
     * @brief an array of points that are to be filled in this fractal
     */
    const Point _points[TRIANGLE_NUM_POINTS]{{0, 0},
                                       {0, 1},
                                       {1, 0}};
public:
    /**
     * @brief the constructor of this class, which resets the dimensions and vector as given from
     * the user
     * @param dims the dimensions of the fractal
     */
    explicit SierpinskiTriangle(int dims);

    /**
     * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
     */
    void makeAndPrint() override;
};

/**
 * @brief the vicsek fractal fractal that inherits from the fractal class
 */
class VicsekFractal : public Fractal
{
private:
    /**
     * @brief an array of points that are to be filled in this fractal
     */
    const Point _points[VICSEK_NUM_POINTS]{{0, 0},
                                     {0, 2},
                                     {1, 1},
                                     {2, 0},
                                     {2, 2}};
public:
    /**
     * @brief the constructor of this class, which resets the dimensions and vector as given from
     * the user
     * @param dims the dimensions of the fractal
     */
    explicit VicsekFractal(int dims);

    /**
     * @brief this sets the vector to hold the whole fractal, and prints it (using other methods)
     */
    void makeAndPrint() override;

};

/**
 * @brief this is the fractal factory which makes a fractal as the index given
 */
class FractalFactory
{
public:
    /**
     * @brief the fractal factory can't have an instance as it is not needed
     */
    FractalFactory() = delete;

    /**
     * @brief the static method that makes the fractal from the given index and dimension
     * @param index the index of the wanted fractal, should be from 1 to 3
     * @param dims the dimensions of the wanted fractal, should be from 1 to 6
     * @note there is memory allocated in this method that should be freed!
     */
    static Fractal *makeFractal(int index, int dims);
};

#endif //CPP_EX2_FRACTAL_H
