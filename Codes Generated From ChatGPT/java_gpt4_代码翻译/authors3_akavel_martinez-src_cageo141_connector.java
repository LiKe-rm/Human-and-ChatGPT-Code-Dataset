import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

class PointChain {
    LinkedList<Point> points;
    boolean closed;

    public PointChain() {
        points = new LinkedList<>();
        closed = false;
    }

    public void init(Segment s) {
        points.add(s.begin());
        points.add(s.end());
    }

    public boolean linkSegment(Segment s) {
        if (s.begin().equals(points.getFirst())) {
            if (s.end().equals(points.getLast()))
                closed = true;
            else
                points.addFirst(s.end());
            return true;
        }
        if (s.end().equals(points.getLast())) {
            if (s.begin().equals(points.getFirst()))
                closed = true;
            else
                points.addLast(s.begin());
            return true;
        }
        if (s.end().equals(points.getFirst())) {
            if (s.begin().equals(points.getLast()))
                closed = true;
            else
                points.addFirst(s.begin());
            return true;
        }
        if (s.begin().equals(points.getLast())) {
            if (s.end().equals(points.getFirst()))
                closed = true;
            else
                points.addLast(s.end());
            return true;
        }
        return false;
    }

    public boolean linkPointChain(PointChain chain) {
        if (chain.points.getFirst().equals(points.getLast())) {
            chain.points.removeFirst();
            points.addAll(chain.points);
            return true;
        }
        if (chain.points.getLast().equals(points.getFirst())) {
            points.removeFirst();
            points.addAll(0, chain.points);
            return true;
        }
        if (chain.points.getFirst().equals(points.getFirst())) {
            points.removeFirst();
            chain.points = reverse(chain.points);
            points.addAll(0, chain.points);
            return true;
        }
        if (chain.points.getLast().equals(points.getLast())) {
            points.removeLast();
            chain.points = reverse(chain.points);
            points.addAll(chain.points);
            return true;
        }
        return false;
    }

    private LinkedList<Point> reverse(LinkedList<Point> points) {
        LinkedList<Point> reversed = new LinkedList<>();
        for (Point p : points) {
            reversed.addFirst(p);
        }
        return reversed;
    }

    public boolean isClosed() {
        return closed;
    }
}

class Connector {
    List<PointChain> openPolygons;
    List<PointChain> closedPolygons;

    public Connector() {
        openPolygons = new ArrayList<>();
        closedPolygons = new ArrayList<>();
    }

    public void add(Segment s) {
        for (PointChain pointChain : openPolygons) {
            if (pointChain.linkSegment(s)) {
                if (pointChain.isClosed()) {
                    closedPolygons.add(pointChain);
                    openPolygons.remove(pointChain);
                } else {
                    for (PointChain anotherChain : openPolygons) {
                        if (pointChain != anotherChain && pointChain.linkPointChain(anotherChain)) {
                            openPolygons.remove(anotherChain);
                            break;
                        }
                    }
                }
                return;
            }
        }

        // The segment cannot be connected with any open polygon
        PointChain newChain = new PointChain();
        newChain.init(s);
        openPolygons.add(newChain);
    }

    public void toPolygon(Polygon p) {
        for (PointChain pointChain : closedPolygons) {
            Contour contour = p.addContour();
            for (Point point : pointChain.points) {
                contour.add(point);
            }
        }
    }
}
