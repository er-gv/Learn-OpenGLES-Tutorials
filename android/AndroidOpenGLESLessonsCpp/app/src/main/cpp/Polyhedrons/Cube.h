//
// Created by nathan on 10/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_CUBE_H
#define ANDROIDOPENGLESLESSONSCPP_CUBE_H

#include "Mesh.h"

class Cube : public Mesh {

private:
    /*
     * FloatBuffer verticesBuffer;
 ShortBuffer triangleStripsIndicesBuffer;

 final int POSITION_DATA_SIZE = 3;
 final int POSITION_OFFSET = 0;

final int NORMAL_DATA_SIZE = 3;
final int NORMAL_OFFSET = 3;

final int COLOR_DATA_SIZE = 3;
final int COLOR_OFFSET = 6;
final int VERTEX_DATA_SIZE = COLOR_DATA_SIZE +NORMAL_DATA_SIZE+ POSITION_DATA_SIZE;
final int stride = VERTEX_DATA_SIZE * BYTES_PER_FLOAT;
float[] mLightPos;

    */

public:
    Cube();
    virtual ~Cube();
};


#endif //ANDROIDOPENGLESLESSONSCPP_CUBE_H
