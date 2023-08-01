import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

public class RPCEmu {

    private static final String CONFIG_FILE = "rpc.cfg";
    private Config config;

    public static void main(String[] args) {
        RPCEmu rpcEmu = new RPCEmu();
        rpcEmu.config = new Config();
        rpcEmu.configLoad();
        // ... run the emulator ...
        rpcEmu.configSave();
    }

    private void configLoad() {
        Properties properties = new Properties();
        File configFile = new File(CONFIG_FILE);

        if (configFile.exists()) {
            try (FileInputStream fis = new FileInputStream(configFile)) {
                properties.load(fis);
            } catch (IOException e) {
                System.err.println("Error loading configuration: " + e.getMessage());
            }
        }

        // Load and process configuration properties
        config.loadFromProperties(properties);
    }

    private void configSave() {
        Properties properties = new Properties();

        // Save configuration properties
        config.saveToProperties(properties);

        try (FileOutputStream fos = new FileOutputStream(CONFIG_FILE)) {
            properties.store(fos, "RPCEmu Configuration");
        } catch (IOException e) {
            System.err.println("Error saving configuration: " + e.getMessage());
        }
    }
}
import java.util.Properties;

public class Config {
    // Declare configuration variables here
    private int memSize;
    // ...

    public void loadFromProperties(Properties properties) {
        // Load and process configuration properties
        memSize = Integer.parseInt(properties.getProperty("mem_size", "16"));
        // ...
    }

    public void saveToProperties(Properties properties) {
        // Save configuration properties
        properties.setProperty("mem_size", String.valueOf(memSize));
        // ...
    }
}

