import java.util.*;

public class Channels {

    public static class MessageSwitch {
        private final List<Route> defaultRoutes = new ArrayList<>();
        private final SortedSet<RangeRoute> routes = new TreeSet<>();

        public void addDefaultRoute(BufferedTransformation destination, String channel) {
            defaultRoutes.add(new Route(destination, channel));
        }

        public void addRoute(int begin, int end, BufferedTransformation destination, String channel) {
            RangeRoute route = new RangeRoute(begin, end, new Route(destination, channel));
            routes.add(route);
        }
    }

    public static class BufferedTransformation {
        // Implement necessary methods and functionality for BufferedTransformation class
    }

    public static class Route {
        private final BufferedTransformation destination;
        private final String channel;

        public Route(BufferedTransformation destination, String channel) {
            this.destination = destination;
            this.channel = channel;
        }

        public BufferedTransformation getDestination() {
            return destination;
        }

        public String getChannel() {
            return channel;
        }
    }

    public static class RangeRoute extends Route implements Comparable<RangeRoute> {
        private final int begin;
        private final int end;

        public RangeRoute(int begin, int end, Route route) {
            super(route.getDestination(), route.getChannel());
            this.begin = begin;
            this.end = end;
        }

        public int getBegin() {
            return begin;
        }

        public int getEnd() {
            return end;
        }

        @Override
        public int compareTo(RangeRoute other) {
            if (this.begin != other.begin) {
                return Integer.compare(this.begin, other.begin);
            }
            return Integer.compare(this.end, other.end);
        }
    }

    public static void main(String[] args) {
        // Test the implementation
        BufferedTransformation destination1 = new BufferedTransformation();
        BufferedTransformation destination2 = new BufferedTransformation();
        BufferedTransformation destination3 = new BufferedTransformation();

        MessageSwitch messageSwitch = new MessageSwitch();
        messageSwitch.addDefaultRoute(destination1, "channel1");
        messageSwitch.addDefaultRoute(destination2, "channel2");
        messageSwitch.addRoute(1, 5, destination3, "channel3");
    }
}
