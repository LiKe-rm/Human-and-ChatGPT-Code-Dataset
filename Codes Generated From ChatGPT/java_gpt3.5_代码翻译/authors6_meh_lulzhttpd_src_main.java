import java.io.IOException;
import java.nio.file.Paths;
import java.util.Arrays;

public class LulzHTTPd {

    public static void main(String[] args) {
        boolean daemonize = true;
        boolean testConfig = false;
        String configFile = "/etc/lulzhttpd/lulzhttpd.conf";
        String configType = "none";

        for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "-h":
                    System.out.println(showHelp());
                    return;

                case "-f":
                    configFile = args[++i];
                    break;

                case "-c":
                    configType = args[++i];
                    break;

                case "-t":
                    testConfig = true;
                    break;

                case "-D":
                    daemonize = false;
                    break;

                case "-v":
                    System.out.println(showVersion());
                    return;

                default:
                    System.out.println(showHelp());
                    return;
            }
        }

        if (testConfig) {
            try {
                Config.test(Paths.get(configFile));
                System.out.println(Config.testLog());
            } catch (Exception e) {
                System.err.println(e.getMessage());
            }

            return;
        }

        try {
            Server.init(configFile, configType);
            Server.start();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static String showHelp() {
        StringBuilder help = new StringBuilder();
        help.append("lulzHTTPd - The webserver for the lulz.\n")
                .append("\n")
                .append("Usage:\n")
                .append("  -f <name>  filename of the config-file.\n")
                .append("  -m <name>  module directory (default: dunno .-.).\n")
                .append("  -p         print the parsed config-file in internal form, and exit\n")
                .append("  -t         test the config-file, and exit.\n")
                .append("  -D         don't go to background (default: go to background)\n")
                .append("  -v         show version.\n")
                .append("  -V         show compile-time features.\n")
                .append("  -h         show this help.\n");
        return help.toString();
    }

    private static String showVersion() {
        return "THE GAME\n";
    }
}
