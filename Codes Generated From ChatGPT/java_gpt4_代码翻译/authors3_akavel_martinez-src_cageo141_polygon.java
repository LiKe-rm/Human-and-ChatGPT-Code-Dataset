import java.util.*;
import java.io.*;

public class Polygon {
    ArrayList<Contour> contours = new ArrayList<>();

    public static void main(String[] args) {
        // Test Polygon
        Polygon polygon = new Polygon("input.txt");
        System.out.println(polygon);
    }

    public Polygon(String filename) {
        try {
            FileReader fr = new FileReader(filename);
            BufferedReader br = new BufferedReader(fr);
            read(br);
            br.close();
        } catch (IOException e) {
            System.err.println("Error opening " + filename);
            System.exit(1);
        }
    }

    public int ncontours() {
        return contours.size();
    }

    public Contour contour(int index) {
        return contours.get(index);
    }

    public Contour pushbackContour() {
        Contour contour = new Contour();
        contours.add(contour);
        return contour;
    }

    public void deletebackContour() {
        contours.remove(contours.size() - 1);
    }

    public void read(BufferedReader br) throws IOException {
        int ncontours = Integer.parseInt(br.readLine().trim());
        for (int i = 0; i < ncontours; i++) {
            String[] npointsAndLevel = br.readLine().trim().split(" ");
            int npoints = Integer.parseInt(npointsAndLevel[0]);
            int level = Integer.parseInt(npointsAndLevel[1]);
            Contour contour = pushbackContour();
            for (int j = 0; j < npoints; j++) {
                String[] pointData = br.readLine().trim().split(" ");
                double px = Double.parseDouble(pointData[0]);
                double py = Double.parseDouble(pointData[1]);
                if (j > 0 && px == contour.vertex(j - 1).x && py == contour.vertex(j - 1).y)
                    continue;
                if (j == npoints - 1 && px == contour.vertex(0).x && py == contour.vertex(0).y)
                    continue;
                contour.add(new Point(px, py));
            }
            if (contour.nvertices() < 3) {
                deletebackContour();
                continue;
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(ncontours()).append("\n");
        for (int i = 0; i < ncontours(); i++) {
            sb.append(contour(i));
        }
        return sb.toString();
    }
}

class Contour {
    ArrayList<Point> points = new ArrayList<>();
    boolean _precomputedCC = false;
    boolean _CC = false;

    public int nvertices() {
        return points.size();
    }

    public Point vertex(int index) {
        return points.get(index);
    }

    public void add(Point p) {
        points.add(p);
    }

    public void boundingbox(Point min, Point max) {
        min.x = min.y = Double.MAX_VALUE;
        max.x = max.y = -Double.MAX_VALUE;
        for (Point p : points) {
            if (p.x < min.x)
                min.x = p.x;
            if (p.x > max.x)
                max.x = p.x;
            if (p.y < min.y)
                min.y = p.y;
            if (p.y > max.y)
                max.y = p.y;
        }
    }

    public boolean counterclockwise() {
        if (_precomputedCC)
            return _CC;
        _precomputedCC = true;
        double area = 0.0;
    }
}