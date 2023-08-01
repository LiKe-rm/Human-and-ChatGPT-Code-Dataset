import java.util.ArrayList;
import java.util.List;

public class Greiner {
    // Utility methods and classes go here
    // ...

    public static class Vertex {
        double x, y;
        Segment s;
        boolean intersect;
        double alpha;
        Vertex next, prev;
        boolean processed, entry;

        public Vertex(double x, double y, Segment s, boolean intersect, double alpha) {
            this.x = x;
            this.y = y;
            this.s = s;
            this.intersect = intersect;
            this.alpha = alpha;
            this.next = null;
            this.prev = null;
            this.processed = false;
            this.entry = false;
        }

        @Override
        public String toString() {
            return "Point: (" + x + "," + y + ") Intersect: " + intersect + " alpha: " + alpha;
        }
    }

    public static class GreinerContour {
        List<Vertex> v;
        int nint;
        // Additional properties go here
        // ...

        // Constructor and methods go here
        // ...
    }

    public static class GreinerHormann {
        List<GreinerContour> gp1, gp2;
        Polygon subject, clipping;

        public GreinerHormann(Polygon subject, Polygon clipping) {
            this.gp1 = new ArrayList<>();
            this.gp2 = new ArrayList<>();
            this.subject = subject;
            this.clipping = clipping;

            // Additional initialization code goes here
            // ...
        }

        // Destructor-equivalent cleanup method
        public void cleanup() {
            for (GreinerContour gc : gp1) {
                // Perform cleanup tasks for gc
            }
            for (GreinerContour gc : gp2) {
                // Perform cleanup tasks for gc
            }
        }

        // Methods go here
        // ...
    }

    public static void main(String[] args) {
        // Test code goes here
    }
}
