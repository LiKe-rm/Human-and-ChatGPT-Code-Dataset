import java.util.ArrayList;
import java.util.List;

public class LwoFile {
    public static class Layer {
        private short layerID;
        private String layerName;
        private int flag;
        private Vector3D pivot;
        private int parent;
        private List<String> images;

        public Layer(short layerID) {
            this.layerID = layerID;
            this.layerName = "";
            this.flag = 0;
            this.pivot = new Vector3D(0.0f, 0.0f, 0.0f);
            this.parent = 0;
            this.images = new ArrayList<>();
        }

        public static class Surface {
            private String surfaceName;
            private int imageIndex;
            private int stateSet;
            private Vector3D vertexColor;
            private int size;

            public Surface() {
                this.surfaceName = "";
                this.imageIndex = -1;
                this.stateSet = 0;
                this.vertexColor = new Vector3D(0.0f, 0.0f, 0.0f);
                this.size = 0;
            }
        }

        public String getImagePath(int imageIndex) {
            if (imageIndex == -1 || images.isEmpty()) {
                return "";
            }
            return images.get(imageIndex);
        }

        public boolean addImage(int index, String imagePath) {
            if (index < 0) {
                return false;
            }
            if (index + 1 > images.size()) {
                images.ensureCapacity(index + 1);
                while (images.size() <= index) {
                    images.add(null);
                }
            }
            images.set(index, imagePath);
            return true;
        }

        public static class Face {
            private SmoothingGroup smoothingGroup;
            private Surface surface;
            private int part;

            public Face() {
                this.smoothingGroup = new SmoothingGroup(false, 0);
                this.surface = null;
                this.part = 0;
            }
        }

        public static class SmoothingGroup {
            private boolean enabled;
            private int group;

            public SmoothingGroup(boolean enabled, int group) {
                this.enabled = enabled;
                this.group = group;
            }
        }
    }
}
