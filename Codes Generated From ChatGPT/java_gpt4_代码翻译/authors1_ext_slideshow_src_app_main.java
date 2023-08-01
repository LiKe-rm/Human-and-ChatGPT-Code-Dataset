import java.io.File;
import java.io.IOException;

public class Slideshow {
    private static Kernel application;

    public static void main(String[] args) {
        try {
            Kernel.Arguments arguments = new Kernel.Arguments();
            // Parse command-line arguments and update the arguments object
            if (!Kernel.parseArguments(arguments, args)) {
                throw new RuntimeException("Failed to parse command-line arguments");
            }

            // Initialize the logger based on the arguments
            Log.initialize(arguments);

            // Create the platform backend
            PlatformBackend backend = PlatformBackend.factory("sdl");
            if (backend == null) {
                throw new RuntimeException("Failed to create a backend named \"sdl\"");
            }

            switch (arguments.mode) {
                case FOREGROUND:
                    application = new ForegroundApp(arguments, backend);
                    break;
                case DAEMON:
                    application = new DaemonApp(arguments, backend);
                    break;
                case LIST_TRANSITIONS:
                    Kernel.printTransitions();
                    System.exit(0);
                default:
                throw new RuntimeException("No valid mode. This should not happen, please report this to the maintainer. Modeid: " + arguments.mode);
            }

            application.init();
            application.run();
            application.cleanup();

            Log.cleanup();

        } catch (ExitException e) {
            System.out.println("Exit exception");
            System.exit(e.getCode());

        } catch (Exception e) {
            // Handle unhandled exceptions. If anything makes it here, it is a fatal
            // error, and it is not possible to continue operation.
            String cwd = "";
            try {
                cwd = new File(".").getCanonicalPath();
            } catch (IOException ioException) {
                System.err.println("Failed to get cwd");
            }

            System.err.println(" *** Slideshow unhandled exception ***");
            System.err.println("\tversion: Slideshow-Java");
            System.err.println("\tcwd:     " + cwd);
            System.err.println("\tMessage: " + e.getMessage() + "\n");
            System.err.println("Troubleshooting:");
            System.err.println(" - Make sure that all required shared libraries are installed.");
            System.err.println(" - Make sure that the cwd is correct.\n");
            System.err.println("If the problem persists, report the bug and
            copy the entire output from the console.\n\n");
            System.err.println("This is a fatal error, the application will now terminate!\n\n");

            e.printStackTrace();

            System.exit(1);
        }
    }
}
