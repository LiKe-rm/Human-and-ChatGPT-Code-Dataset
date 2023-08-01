import java.awt.geom.Point2D;

public class IntersectionFinder {

    public static void main(String[] args) {
        // Test the code here if needed
    }

    private static int findIntersection(double u0, double u1, double v0, double v1, double[] w) {
        if ((u1 < v0) || (u0 > v1))
            return 0;
        if (u1 > v0) {
            if (u0 < v1) {
                w[0] = (u0 < v0) ? v0 : u0;
                w[1] = (u1 > v1) ? v1 : u1;
                return 2;
            } else {
                w[0] = u0;
                return 1;
            }
        } else {
            w[0] = u1;
            return 1;
        }
    }

    public static int findIntersection(Segment seg0, Segment seg1, Point2D.Double pi0, Point2D.Double pi1) {
        Point2D.Double p0 = seg0.begin();
        Point2D.Double d0 = new Point2D.Double(seg0.end().x - p0.x, seg0.end().y - p0.y);
        Point2D.Double p1 = seg1.begin();
        Point2D.Double d1 = new Point2D.Double(seg1.end().x - p1.x, seg1.end().y - p1.y);
        double sqrEpsilon = 0.0000001;
        Point2D.Double E = new Point2D.Double(p1.x - p0.x, p1.y - p0.y);
        double kross = d0.x * d1.y - d0.y * d1.x;
        double sqrKross = kross * kross;
        double sqrLen0 = d0.x * d0.x + d0.y * d0.y;
        double sqrLen1 = d1.x * d1.x + d1.y * d1.y;

        if (sqrKross > sqrEpsilon * sqrLen0 * sqrLen1) {
            double s = (E.x * d1.y - E.y * d1.x) / kross;
            if ((s < 0) || (s > 1)) {
                return 0;
            }
            double t = (E.x * d0.y - E.y * d0.x) / kross;
            if ((t < 0) || (t > 1)) {
                return 0;
            }
            pi0.x = p0.x + s * d0.x;
            pi0.y = p0.y + s * d0.y;
            if (pi0.distance(seg0.begin()) < 0.00000001) pi0.setLocation(seg0.begin());
            if (pi0.distance(seg0.end()) < 0.00000001) pi0.setLocation(seg0.end());
            if (pi0.distance(seg1.begin()) < 0.00000001) pi0.setLocation(seg1.begin());
            if (pi0.distance(seg1.end()) < 0.00000001) pi0.setLocation(seg1.end());
            return 1;
        }

        double sqrLenE = E.x * E.x + E.y * E.y;
        kross = E.x * d0.y - E.y * d0.x;
        sqrKross = kross * kross;
        if (sqrKross > sqrEpsilon * sqrLen0 * sqrLenE) {
            return 0;
        }

        // Lines of the segments are the same. Need to test for overlap of segments.
        double s0 = (d0.x * E.x + d0.y * E.y) / sqrLen0;
        double s1 = s0 + (d0.x * d1.x + d0.y * d1.y) / sqrLen0;
        double smin = Math.min(s0, s1);
        double smax = Math.max(s0, s1);
        double[] w = new double[2];
        int imax = findIntersection(0.0, 1.0, smin, smax, w);
    
        if (imax > 0) {
            pi0.x = p0.x + w[0] * d0.x;
            pi0.y = p0.y + w[0] * d0.y;
            if (pi0.distance(seg0.begin()) < 0.00000001) pi0.setLocation(seg0.begin());
            if (pi0.distance(seg0.end()) < 0.00000001) pi0.setLocation(seg0.end());
            if (pi0.distance(seg1.begin()) < 0.00000001) pi0.setLocation(seg1.begin());
            if (pi0.distance(seg1.end()) < 0.00000001) pi0.setLocation(seg1.end());
            if (imax > 1) {
                pi1.x = p0.x + w[1] * d0.x;
                pi1.y = p0.y + w[1] * d0.y;
            }
        }
    
        return imax;
    }
}
class Segment {
    private Point2D.Double beginPoint;
    private Point2D.Double endPoint;
    public Segment(Point2D.Double beginPoint, Point2D.Double endPoint) {
        this.beginPoint = beginPoint;
        this.endPoint = endPoint;
    }
    
    public Point2D.Double begin() {
        return beginPoint;
    }
    
    public Point2D.Double end() {
        return endPoint;
    }
}    