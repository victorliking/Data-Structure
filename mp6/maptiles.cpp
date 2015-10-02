/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	int row = theSource.getRows();
	int col = theSource.getColumns();
	int size = theTiles.size();
	MosaicCanvas * ret= new MosaicCanvas(row,col);
	
	vector < Point<3> > hi_points;
	map<Point<3>,TileImage> my_map;
	for(int i=0;i<size;i++)
	{
		RGBAPixel avg = theTiles[i].getAverageColor();
		Point<3> my_point(avg.red,avg.green,avg.blue);
		my_map.insert(pair<Point<3>,TileImage>(my_point,theTiles[i]));
		hi_points.push_back(my_point); 	
	}
	KDTree<3> theTilesTree(hi_points);
	
	for(int i=0; i< theSource.getRows(); i++)
	{
		for(int j=0; j<theSource.getColumns();j++)
		{
			RGBAPixel Pixel = theSource.getRegionColor(i,j);
			Point<3> targetPoint(Pixel.red, Pixel.green, Pixel.blue);
			Point<3> candidatePoint = theTilesTree.findNearestNeighbor(targetPoint);
			TileImage candidateTileImage = my_map[candidatePoint];
			ret->setTile(i, j, candidateTileImage);
		}
	}
	return ret;
}
