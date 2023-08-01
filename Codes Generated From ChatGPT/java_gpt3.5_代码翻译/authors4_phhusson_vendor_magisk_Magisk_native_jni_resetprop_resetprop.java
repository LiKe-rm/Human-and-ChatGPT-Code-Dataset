import java.util.*;
import java.util.regex.Pattern;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;

public class ResetProp {

    private static boolean usePb = false;
    private static boolean verbose = false;

    private static final String PERSISTENT_PROPERTY_DIR = "/data/property";
    private static final Pattern LEGAL_PROPERTY_NAME = Pattern.compile("^[a-zA-Z0-9._:-]{1,}$");

    public static void main(String[] args) {
        if (args.length == 0) {
            printAllProperties();
        } else {
            // Handle arguments and options here
        }
    }

    private static boolean checkLegalPropertyName(String name) {
        if (name == null || name.isEmpty()) {
            System.err.println("Illegal property name: [" + name + "]");
            return false;
        }
        if (name.startsWith(".") || name.endsWith(".")) {
            System.err.println("Illegal property name: [" + name + "]");
            return false;
        }
        if (!LEGAL_PROPERTY_NAME.matcher(name).matches()) {
            System.err.println("Illegal property name: [" + name + "]");
            return false;
        }
        return true;
    }

    private static void printAllProperties() {
        Properties properties = System.getProperties();
        List<String> keys = new ArrayList<>(properties.stringPropertyNames());
        Collections.sort(keys);
        for (String key : keys) {
            System.out.printf("[%s]: [%s]%n", key, properties.getProperty(key));
        }
    }

    // Implement other methods and classes, such as prop_exist, getprop, setprop, deleteprop, etc.

}
