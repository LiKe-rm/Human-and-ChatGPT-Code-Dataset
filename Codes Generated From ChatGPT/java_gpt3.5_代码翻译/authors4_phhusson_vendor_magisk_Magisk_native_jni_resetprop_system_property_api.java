import java.util.HashMap;
import java.util.Map;

public class SystemProperties {
    private final Map<String, String> properties = new HashMap<>();

    public boolean init(String propFilename) {
        // Load properties from the given file
        return true; // Return true if initialization is successful, otherwise false
    }

    public String get(String name) {
        return properties.get(name);
    }

    public int set(String name, String value) {
        properties.put(name, value);
        return 0; // Return 0 if successful, otherwise a non-zero value
    }

    public int delete(String name) {
        properties.remove(name);
        return 0; // Return 0 if successful, otherwise a non-zero value
    }

    public static void main(String[] args) {
        SystemProperties systemProperties = new SystemProperties();

        if (systemProperties.init("prop_filename")) {
            System.out.println("Initialization successful");
        } else {
            System.out.println("Initialization failed");
        }

        systemProperties.set("property1", "value1");
        System.out.println("Property1: " + systemProperties.get("property1"));

        systemProperties.delete("property1");
        System.out.println("Property1 after deletion: " + systemProperties.get("property1"));
    }
}
