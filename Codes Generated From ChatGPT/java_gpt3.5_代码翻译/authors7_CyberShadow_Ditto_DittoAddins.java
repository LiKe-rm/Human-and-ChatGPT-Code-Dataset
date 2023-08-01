import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DittoAddins {
    private List<DittoAddin> addins;
    private Map<Integer, FunctionLookup> functionMap;

    public DittoAddins() {
        this.addins = new ArrayList<>();
        this.functionMap = new HashMap<>();
    }

    public boolean unloadAll() {
        System.out.println("Ditto Addin - Unloading all addins Count: " + addins.size());

        for (DittoAddin addin : addins) {
            addin.cleanup();
        }

        addins.clear();

        return true;
    }

    public boolean loadAll() {
        DittoInfo dittoInfo = new DittoInfo();
        dittoInfo.loadDittoInfo();

        String addinsPath = "path/to/addins/directory"; // Replace with the actual path

        File dir = new File(addinsPath);
        File[] dllFiles = dir.listFiles((d, name) -> name.endsWith(".dll"));

        if (dllFiles != null) {
            for (File dllFile : dllFiles) {
                System.out.println("Ditto Addin - Trying to load addin file " + dllFile.getPath());

                DittoAddin addin = new DittoAddin();
                if (addin.doLoad(dllFile.getPath(), dittoInfo)) {
                    System.out.println("Ditto Addin - Success, loaded addin: " + dllFile.getPath());
                    addins.add(addin);
                } else {
                    System.err.println("Ditto Addin - Failed loading Addin Error: " + addin.lastError());
                }
            }
        }

        return addins.size() > 0;
    }

    public boolean addPrePasteAddinsToMenu(Menu menu) {
        // Implement adding menu items based on your GUI framework
        // For example, using Swing, JavaFX, or other libraries
        // This code is just a reference for handling menu creation

        boolean result = false;
        functionMap.clear();
        int menuId = 3000;

        // AllAddinsMenu creation and handling

        for (DittoAddin addin : addins) {
            // AddinMenu creation and handling
            // Appending menu items based on the functions in the addin
        }

        return result;
    }

    public boolean callPrePasteFunction(int id, IClip clip) {
        FunctionLookup func = functionMap.get(id);
        if (func != null) {
            DittoInfo dittoInfo = new DittoInfo();
            dittoInfo.loadDittoInfo();
            return func.getAddin().prePasteFunction(dittoInfo, func.getFunctionName(), clip);
        }
        return false;
    }

    public void aboutScreenText(List<String> arr) {
        for (DittoAddin addin : addins) {
            String line = String.format("%s Ver: %d, Ver2: %d",
                    addin.displayName(), addin.version(), addin.privateVersion());
            arr.add(line);

            for (Function function : addin.getPrePasteFunctions()) {
                String line2 = String.format("    %s (%s)", function.getDisplayName(), function.getDetailDescription());
                arr.add(line2);
            }

            arr.add("");
        }
    }
}
