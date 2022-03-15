/* Copyright (c) 2007-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P2.turtle;

import java.util.*;

public class TurtleSoup {

    /**
     * Draw a square.
     * 
     * @param turtle the turtle context
     * @param sideLength length of each side
     */
    public static void drawSquare(Turtle turtle, int sideLength) {
        for (int i=0; i<4; ++i) {
        	turtle.forward(sideLength);
        	turtle.turn(90);
        }
    }

    /**
     * Determine inside angles of a regular polygon.
     * 
     * There is a simple formula for calculating the inside angles of a polygon;
     * you should derive it and use it here.
     * 
     * @param sides number of sides, where sides must be > 2
     * @return angle in degrees, where 0 <= angle < 360
     */
    public static double calculateRegularPolygonAngle(int sides) {
        if (sides <= 2) throw new RuntimeException("The numbers of sides must be more than 2");
        return 180 - 360.0/sides;
    }

    /**
     * Determine number of sides given the size of interior angles of a regular polygon.
     * 
     * There is a simple formula for this; you should derive it and use it here.
     * Make sure you *properly round* the answer before you return it (see java.lang.Math).
     * HINT: it is easier if you think about the exterior angles.
     * 
     * @param angle size of interior angles in degrees, where 0 < angle < 180
     * @return the integer number of sides
     */
    public static int calculatePolygonSidesFromAngle(double angle) {
        if (angle <= 0 || angle > 180) throw new RuntimeException("The angle must be between 0 and 180(excluded 0 and 180).");
        return (int) Math.round(360 / (180 - angle));
    }

    /**
     * Given the number of sides, draw a regular polygon.
     * 
     * (0,0) is the lower-left corner of the polygon; use only right-hand turns to draw.
     * 
     * @param turtle the turtle context
     * @param sides number of sides of the polygon to draw
     * @param sideLength length of each side
     */
    public static void drawRegularPolygon(Turtle turtle, int sides, int sideLength) {
        double ang = 180 - calculateRegularPolygonAngle(sides);
        for (int i=0; i<sides; ++i) {
        	turtle.forward(sideLength);
        	turtle.turn(ang);
        }
    }

    /**
     * Given the current direction, current location, and a target location, calculate the Bearing
     * towards the target point.
     * 
     * The return value is the angle input to turn() that would point the turtle in the direction of
     * the target point (targetX,targetY), given that the turtle is already at the point
     * (currentX,currentY) and is facing at angle currentBearing. The angle must be expressed in
     * degrees, where 0 <= angle < 360. 
     *
     * HINT: look at http://en.wikipedia.org/wiki/Atan2 and Java's math libraries
     * 
     * @param currentBearing current direction as clockwise from north
     * @param currentX current location x-coordinate
     * @param currentY current location y-coordinate
     * @param targetX target point x-coordinate
     * @param targetY target point y-coordinate
     * @return adjustment to Bearing (right turn amount) to get to target point,
     *         must be 0 <= angle < 360
     */
    public static double calculateBearingToPoint(double currentBearing, int currentX, int currentY,
                                                 int targetX, int targetY) {
        double deltaAngle = Math.atan2(targetX - currentX, targetY - currentY) * 180 / Math.PI;
        deltaAngle -= currentBearing;
        if (deltaAngle < 0)  deltaAngle += 360;
        return deltaAngle;
    }

    /**
     * Given a sequence of points, calculate the Bearing adjustments needed to get from each point
     * to the next.
     * 
     * Assumes that the turtle starts at the first point given, facing up (i.e. 0 degrees).
     * For each subsequent point, assumes that the turtle is still facing in the direction it was
     * facing when it moved to the previous point.
     * You should use calculateBearingToPoint() to implement this function.
     * 
     * @param xCoords list of x-coordinates (must be same length as yCoords)
     * @param yCoords list of y-coordinates (must be same length as xCoords)
     * @return list of Bearing adjustments between points, of size 0 if (# of points) == 0,
     *         otherwise of size (# of points) - 1
     */
    public static List<Double> calculateBearings(List<Integer> xCoords, List<Integer> yCoords) {
        int n = xCoords.size();
        if (n != yCoords.size()) throw new RuntimeException("The lengths of xCoords and yCoords are different.");
        if (n < 2) return new ArrayList<Double>();
        
        List <Double> BearingList = new ArrayList<Double>();
        
        double currentBearing = 0;
        for (int i=1; i<n; ++i) {
        	double deltaAngle = calculateBearingToPoint(currentBearing, xCoords.get(i-1), yCoords.get(i-1), xCoords.get(i), yCoords.get(i));
        	BearingList.add(deltaAngle);
        	currentBearing += deltaAngle;
        }
        
        return BearingList;
    }
    
    private static double xx,yy;
    
    private static int sgn(double x) {
    	double eps = 1e-8;
    	if (x > eps) return 1;
    	else if (x < -eps) return -1;
    	else return 0;
    }
    
    private static double cross(Point x,Point y) {
    	return x.x()*y.y() - x.y()*y.x();
    }
    
    private static double dis(Point x,Point y) {
    	return Math.sqrt((x.x()-y.x()) * (x.x()-y.x()) + (x.y()-y.y()) * (x.y()-y.y()));
    }
    
    public static Comparator<Point> cmp = new Comparator<Point>() {
    	public int compare(Point a,Point b) {
    		Point x = new Point(a.x() - xx,a.y() - yy);
    		Point y = new Point(b.x() - xx,b.y() - yy);
    		
    		int tmp = sgn(cross(x,y));
    		if (tmp != 0) return tmp;
    		Point z = new Point(xx,yy);
    		if (dis(z,x) < dis(z,y)) return 1;
    		else return -1;
    	}
    };
    
    /**
     * Given a set of points, compute the convex hull, the smallest convex set that contains all the points 
     * in a set of input points. The gift-wrapping algorithm is one simple approach to this problem, and 
     * there are other algorithms too.
     * 
     * @param points a set of points with xCoords and yCoords. It might be empty, contain only 1 point, two points or more.
     * @return minimal subset of the input points that form the vertices of the perimeter of the convex hull
     */
    public static Set<Point> convexHull(Set<Point> points) {
        int n = points.size();
        if (n < 3) return points;
        
        List <Point> arr = new Vector <Point> ();
        List <Point> st  = new Vector <Point> ();
        Set <Point> ret = new HashSet<Point> ();
        Iterator<Point> it = points.iterator();
        
        while (it.hasNext()) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        	arr.add(it.next());
        }
        
        xx = arr.get(0).x();
        yy = arr.get(0).y();
        int id = 0;
        
        for (int i=1; i<arr.size(); ++i) {
        	if (arr.get(i).y() < yy || (arr.get(i).y() == yy && arr.get(i).x() < xx)) {
        		xx = arr.get(i).x();
        		yy = arr.get(i).y();
        		id = i;
        	}
        }
        
        Point p = arr.get(id);
        arr.set(id, arr.get(0));
        arr.remove(0);
        arr.sort(cmp);
        st.add(p);
        st.add(arr.get(0));
        
        int top = 1;
        for (int i=1; i<arr.size(); ++i) {
        	while (top > 0) {
        		Point a = new Point (st.get(top).x() - st.get(top-1).x(), st.get(top).y() - st.get(top-1).y());
        		Point b = new Point (arr.get(i).x() - st.get(top-1).x(), arr.get(i).y() - st.get(top-1).y());
        		if (sgn(cross(a,b)) <= 0) break;
        		st.remove(top);
        		top--;
        	}
        	st.add(arr.get(i));
        	top++;
        }
        
        for (int i=0; i<st.size(); ++i) ret.add(st.get(i));
        return ret;
    }
    
    /**
     * Draw your personal, custom art.
     * 
     * Many interesting images can be drawn using the simple implementation of a turtle.  For this
     * function, draw something interesting; the complexity can be as little or as much as you want.
     * 
     * @param turtle the turtle context
     */
    public static void drawPersonalArt(Turtle turtle) {
    	Random random = new Random();
    	for (int t=0; t<4; ++t) {
    		int mod;
    		if (t == 1 || t == 3) mod = 2;
    		else mod = 3;
    		for (int i=1; i<=90; ++i) {
    			for (int j=1; j<=100; ++j) {
    				switch(j%mod) {
	    				case 0: {
	    					switch(t) {
		    					case 0: turtle.color(PenColor.GREEN); break;
		    	    			case 1: turtle.color(PenColor.YELLOW); break;
		    	    			case 2: turtle.color(PenColor.BLUE); break;
		    	    			case 3: turtle.color(PenColor.RED); break;
		    	    		}
	    					break;
	    				}
	    				default: {
	    					
	    					turtle.color(PenColor.GRAY); break;
	    				}
	    					
	    			}
    				turtle.forward(2);
    			}
        		turtle.turn(92);
        	}
    		turtle.turn(90);
    	}
    	
    }

    /**
     * Main method.
     * 
     * This is the method that runs when you run "java TurtleSoup".
     * 
     * @param args unused
     */
    public static void main(String args[]) {
        DrawableTurtle turtle = new DrawableTurtle();

//        drawSquare(turtle, 40);
//        drawRegularPolygon(turtle,6,30);
        drawPersonalArt(turtle);
        // draw the window
        turtle.draw();
    }

}
