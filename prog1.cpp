#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int comparisons;
struct Point{
public:
	double x,y;
	Point(double x,double y):x(x),y(y){}
	Point(){}
	bool operator<(const Point& val) const {
		comparisons++; 
        if(x!=val.x)return x < val.x;
        else return y<val.y; 
    }
};
double distSquared(Point p1,Point p2){
	comparisons++;
	double dx=(p1.x-p2.x);
	double dy=(p1.y-p2.y);
	return dx*dx+dy*dy;
}
vector<Point>pts;
vector<Point>ptsY;
double smallestDist;
Point smallestPoint1;
Point smallestPoint2;

void bruteForce(vector<Point>pts){
	smallestDist=distSquared(pts[0],pts[1]);
	smallestPoint1=pts[0];
	smallestPoint2=pts[1];
	int n=pts.size();
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			double tempDist=distSquared(pts[i],pts[j]);
			if(tempDist<smallestDist){
				smallestDist=tempDist;
				smallestPoint1=pts[i];
				smallestPoint2=pts[j];
			}
		}
	}
}
bool cY(Point a,Point b){
	comparisons++;
	return a.y<b.y;
}
pair<Point,Point> shortestPairInRange(vector<Point>ptsX,vector<Point>ptsY){
	if(ptsX.size()<=3){
		bruteForce(ptsX);
		return make_pair(smallestPoint1,smallestPoint2);
	}
	int mid=(ptsX.size())/2;
	vector<Point>ptsLY;
	vector<Point>ptsRY;
	vector<Point>ptsLX;
	vector<Point>ptsRX;
	for(int i=0;i<ptsX.size();i++){
		if(ptsY[i].x<ptsX[mid].x)ptsLY.push_back(ptsY[i]);
		else ptsRY.push_back(ptsY[i]);
		if(i<mid)ptsLX.push_back(ptsX[i]);
		else ptsRX.push_back(ptsX[i]);
	}
	pair<Point,Point>leftShortest=shortestPairInRange(ptsLX,ptsLY);
	pair<Point,Point>rightShortest=shortestPairInRange(ptsRX,ptsRY);
	double packingDist=pow(min(distSquared(leftShortest.first,leftShortest.second),distSquared(rightShortest.first,rightShortest.second)),.5);
	if(distSquared(leftShortest.first,leftShortest.second)<distSquared(rightShortest.first,rightShortest.second)){
		smallestPoint1=leftShortest.first;
		smallestPoint2=leftShortest.second;
	}else{
		smallestPoint1=rightShortest.first;
		smallestPoint2=rightShortest.second;
	}
	double center=(ptsX[mid-1].x+ptsX[mid].x)/2;
	vector<Point>packPts;
	for(int i=0;i<ptsY.size();i++){
		if(abs(center-ptsY[i].x)<packingDist)
			packPts.push_back(ptsY[i]);
	}
	for(int i=0;i<packPts.size();i++){
		for(int j=i+1;j<packPts.size()&&(packPts[j].y-packPts[i].y<packingDist);j++){
			double tempDist=distSquared(packPts[j],packPts[i]);
			if(pow(tempDist,0.5)<packingDist){
				packingDist=pow(tempDist,0.5);
				smallestPoint1=packPts[i];
				smallestPoint2=packPts[j];
			}
		}
	}
	smallestDist=packingDist;
	return make_pair(smallestPoint1,smallestPoint2);
}
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		double x,y;
		cin>>x>>y;
		Point temp(x,y);
		pts.push_back(temp);
	}
	bruteForce(pts);
	if(smallestPoint1<smallestPoint2)
		cout<<showpoint<<smallestPoint1.x<<" "<<smallestPoint1.y<<" "<<smallestPoint2.x<<" "<<smallestPoint2.y<<endl;
	else
		cout<<showpoint<<smallestPoint2.x<<" "<<smallestPoint2.y<<" "<<smallestPoint1.x<<" "<<smallestPoint1.y<<endl;
	cout<<comparisons<<endl;

	comparisons=0;
	sort(pts.begin(),pts.end());
	vector<Point>ptsY;
	for(int i=0;i<pts.size();i++)ptsY.push_back(pts[i]);
	sort(ptsY.begin(),ptsY.end(),cY);
	pair<Point,Point> shortestPts=shortestPairInRange(pts,ptsY);
	smallestPoint1=shortestPts.first;
	smallestPoint2=shortestPts.second;
	if(smallestPoint1<smallestPoint2)
		cout<<showpoint<<smallestPoint1.x<<" "<<smallestPoint1.y<<" "<<smallestPoint2.x<<" "<<smallestPoint2.y<<endl;
	else
		cout<<showpoint<<smallestPoint2.x<<" "<<smallestPoint2.y<<" "<<smallestPoint1.x<<" "<<smallestPoint1.y<<endl;
	cout<<comparisons<<endl;
	return 0;
}