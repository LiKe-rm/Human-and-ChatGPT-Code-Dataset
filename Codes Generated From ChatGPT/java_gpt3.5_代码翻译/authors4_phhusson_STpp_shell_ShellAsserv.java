import java.io.PrintStream;

public class ShellAsserv {
    public static class VelocityAccel {
        // Implement getters and setters for the required properties here
    }

    public static class Position {
        // Implement getters and setters for the required properties here
    }

    public static class Asserv {
        // Implement required properties, getters and setters, and methods here
    }

    public static void printVelocityAccelInfo(PrintStream out, VelocityAccel velocityAccel) {
        out.println("Current Angle = " + velocityAccel.getAngle());
        out.println("Current Distance = " + velocityAccel.getDist());
        // And so on for the rest of the properties
    }

    public static void printPositionInfo(PrintStream out, Position position) {
        out.println("X = " + (int) (position.getX() * 1000) + " mm");
        out.println("Y = " + (int) (position.getY() * 1000) + " mm");
        out.println("Theta = " + (int) (position.getTheta() * 10) + " deciDegres");
    }

    public static class Shell {
        private Asserv asserv;

        public Shell(Asserv asserv) {
            this.asserv = asserv;
        }

        // Implement the required methods to interact with the Asserv class
    }

    public static void main(String[] args) {
        Asserv asserv = new Asserv();
        Shell shell = new Shell(asserv);
        
        // Interact with the shell instance as needed
    }
}
