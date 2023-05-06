/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    MosaicCanvas *result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    vector<Point<3>> averageColor(theTiles.size());
    map<Point<3>, int> sourceMap;
    for (unsigned int i = 0; i < theTiles.size(); i++) {
        averageColor[i] = convertToXYZ(theTiles[i].getAverageColor());
        sourceMap[averageColor[i]] = i;
    }

    KDTree<3> sourceTree(averageColor);

    for (auto row = 0; row < theSource.getRows(); row++){
        for (auto column = 0; column < theSource.getColumns(); column++) {
        auto myQuery = convertToXYZ(theSource.getRegionColor(row, column));
        auto myPoint = sourceTree.findNearestNeighbor(myQuery);
        auto index = sourceMap[myPoint];
        result->setTile(row, column, &theTiles[index]);
        }
    }
    return result;
}

