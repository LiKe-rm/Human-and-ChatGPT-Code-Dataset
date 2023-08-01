import java.awt.geom.Point2D;
import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

class Point extends Point2D.Double {
    public Point(double x, double y) {
        super(x, y);
    }
}

class Segment {
    Point start;
    Point end;

    public Segment(Point start, Point end) {
        this.start = start;
        this.end = end;
    }
}

class Contour {
    private List<Point> points;
    private boolean precomputedCC;
    private boolean CC;

    public Contour() {
        points = new ArrayList<>();
        precomputedCC = false;
    }

    public void add(Point point) {
        points.add(point);
    }

    public int nvertices() {
        return points.size();
    }

    public Point vertex(int index) {
        return points.get(index);
    }

    public void boundingBox(Point min, Point max) {
        min.x = Double.MAX_VALUE;
        min.y = Double.MAX_VALUE;
        max.x = Double.MIN_VALUE;
        max.y = Double.MIN_VALUE;

        for (Point point : points) {
            min.x = Math.min(min.x, point.x);
            max.x = Math.max(max.x, point.x);
            min.y = Math.min(min.y, point.y);
            max.y = Math.max(max.y, point.y);
        }
    }

    public boolean counterclockwise() {
        if (precomputedCC) {
            return CC;
        }
        precomputedCC = true;
        double area = 0.0;
        for (int i = 0; i < nvertices() - 1; i++) {
            area += vertex(i).x * vertex(i + 1).y - vertex(i + 1).x * vertex(i).y;
        }
        area += vertex(nvertices() - 1).x * vertex(0).y - vertex(0).x * vertex(nvertices() - 1).y;
        return CC = area >= 0.0;
    }

    public void move(double x, double y) {
        for (Point point : points) {
            point.x += x;
            point.y += y;
        }
    }

    public boolean clockwise() {
        return !counterclockwise();
    }

    public void changeOrientation() {
        List<Point> reversedPoints = new ArrayList<>(points);
        java.util.Collections.reverse(reversedPoints);
        points = reversedPoints;
        CC = !CC;
    }

    public void setCounterClockwise() {
        if (clockwise()) {
            changeOrientation();
        }
    }

    public void setClockwise() {
        if (counterclockwise()) {
            changeOrientation();
        }
    }
}

public class Polygon {
    private List<Contour> contours;

    public Polygon() {
        contours = new ArrayList<>();
    }

    public Polygon(String filename) {
        this();
        try (Scanner scanner = new Scanner(Paths.get(filename))) {
            int numContours = scanner.nextInt();
            for (int i = 0; i < numContours; i++) {
                Contour contour = new Contour();
                int numPoints = scanner.nextInt();
                scanner.nextInt(); // Skip level information
                for (int j = 0; j < numPoints; j++) {
                    double x = scanner.nextDouble();
                    double y = scanner.nextDouble();
                    contour.add(new Point(x, y));
                }
                contours.add(contour);
            }
        } catch (IOException e) {
            System.err.println("Error reading polygon file: " + e.getMessage());
        }
    }

    public void addContour(Contour contour) {
        contours.add(contour);
    }

    public int numberOfContours() {
        return contours.size();
    }

    public Contour contour(int index) {
        return contours.get(index);
    }

    public void boundingBox(Point min, Point max) {
        min.x = Double.MAX_VALUE;
        min.y = Double.MAX_VALUE;
        max.x = Double.MIN_VALUE;
        max.y = Double.MIN_VALUE;

        for (Contour contour : contours) {
            Point contourMin = new Point(Double.MAX_VALUE, Double.MAX_VALUE);
            Point contourMax = new Point(Double.MIN_VALUE, Double.MIN_VALUE);
            contour.boundingBox(contourMin, contourMax);

            min.x = Math.min(min.x, contourMin.x);
            min.y = Math.min(min.y, contourMin.y);
            max.x = Math.max(max.x, contourMax.x);
            max.y = Math.max(max.y, contourMax.y);
        }
    }

    public void move(double x, double y) {
        for (Contour contour : contours) {
            contour.move(x, y);
        }
    }

    public void setCounterClockwise() {
        for (Contour contour : contours) {
            contour.setCounterClockwise();
        }
    }

    public void setClockwise() {
        for (Contour contour : contours) {
            contour.setClockwise();
        }
    }
}
