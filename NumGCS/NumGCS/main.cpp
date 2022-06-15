//
//  main.cpp
//  NumGCS
//
//  Created by Ashwani Chandil on 13/04/22.
//

#include <iostream>

#include "stdafx.h"
#include "lib.h"

void lineToCircle(lib& solver, int& cx, int& cy, int& r)
{
    // Find Circle conitinuous to line p1,p2
    // Point p1 = 5,5
    // Point p2 = 15,5
    // Point p3 (moving point) = -5, -5
    // circle = ?
    
    // Line point
    auto p1x = solver.addParameter(5.0, 5.0, 5.0, true);
    auto p1y = solver.addParameter(5.0, 5.0, 5.0, true);
    auto p2x = solver.addParameter(15.0, 15.0, 15.0, true);
    auto p2y = solver.addParameter(5.0, 5.0, 5.0, true);
    
    // Moving point.
    auto p3x = solver.addParameter(-5.0, -5.0, -5.0, true);
    auto p3y = solver.addParameter(-5.0, -5.0, -5.0, true);
    
    std::vector<int> vars1 = {p1x, p1y, p2x, p2y, p1x, p1y, cx, cy};
    solver.addConstraint("perpendicular", vars1);
    
    std::vector<int> vars2 = {p1x, p1y, cx, cy, r};
    solver.addConstraint("coincident", vars2);
    
    std::vector<int> vars3 = {p3x, p3y, cx, cy, r};
    solver.addConstraint("coincident", vars3);
}

void circleToCircle(lib& solver, int& cx, int& cy, int& r)
{
    // Find Circle B conitinuous to circle A
    // Point on A = 5,18
    // Point on B (moving point) = 20, 50
    // circle A = 5, 10; 8
    // circle B = ?
    
    // Point A
    int ax = 5, ay = 18;
    auto pax = solver.addParameter(ax, ax, ax, true);
    auto pay = solver.addParameter(ay, ay, ay, true);
    
    // Moving point
//    int x = 18, y = 25;
    int x = 13, y = 15;
    auto px = solver.addParameter(x, x, x, true);
    auto py = solver.addParameter(y, y, y, true);
    
    // Circle A
    int cax = 5, cay = 10, car = 8;
//    int cax = 5, cay = 5, car = 5;
    auto pcax = solver.addParameter(cax, cax, cax, true);
    auto pcay = solver.addParameter(cay, cay, cay, true);
    auto pcar = solver.addParameter(car, car, car, true);
        
    std::vector<int> vars2 = {px, py, cx, cy, r};
    solver.addConstraint("coincident", vars2);
    
    std::vector<int> vars3 = {pax, pay, cx, cy, r};
    solver.addConstraint("coincident", vars3);
    
    std::vector<int> vars1 = {cx, cy, r, pcax, pcay, pcar};
//    std::vector<int> vars1 = {pcax, pcay, pcar, cx, cy, r};
    solver.addConstraint("tangent_internal", vars1);
//    solver.addConstraint("ec", vars1);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    lib solver;
    
    // variables
    // center
    double max = 1e+4;
    auto cx = solver.addParameter(0, -max, max, false);
    auto cy = solver.addParameter(0, -max, max, false);
    
    // radius
    auto r = solver.addParameter(0, 0, max, false);
    
//    lineToCircle(solver, cx, cy, r);
    
    circleToCircle(solver, cx,cy, r);
    
    if (solver.solve())
    {
        std::cout<<"c: "<< solver.getParameter(cx) << ", " << solver.getParameter(cy) <<"\n";
        std::cout<<"r: "<< solver.getParameter(r) <<"\n";
    }
    else
    {
        std::cout<<"Failed\n";
    }
    
    
    
    return 0;
}
