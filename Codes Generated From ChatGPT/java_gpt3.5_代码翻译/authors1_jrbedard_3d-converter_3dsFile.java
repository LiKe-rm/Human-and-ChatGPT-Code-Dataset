import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ThreeDSFile {
    private Map<Integer, Material> materials = new HashMap<>();

    public static class Object {
        public static class Mesh {
            public static class Face {
                private int flag;
                private List<Boolean> smoothingGroup;
                private int materialID;

                public Face() {
                    flag = 0;
                    smoothingGroup = new ArrayList<>(0);
                    materialID = 0;
                }
            }
        }
    }

    public static class Material {
        private String materialName;

        public Material(String materialName) {
            this.materialName = materialName;
        }

        public String getMaterialName() {
            return materialName;
        }
    }

    public int addMaterial(String materialName) {
        int materialID = materials.size();
        materials.put(materialID, new Material(materialName));
        return materialID;
    }

    public int findMaterial(String materialName) {
        for (Map.Entry<Integer, Material> entry : materials.entrySet()) {
            if (entry.getValue().getMaterialName().equals(materialName)) {
                return entry.getKey();
            }
        }

        System.out.println("Warning: Invalid Material Name: '" + materialName + "'. Returning the first material.");
        return 0;
    }
}
