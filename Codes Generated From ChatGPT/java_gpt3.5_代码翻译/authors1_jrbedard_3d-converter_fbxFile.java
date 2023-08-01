public class FbxFile {
    private Object fbxSdkManager;
    private Object scene;

    public FbxFile() {
        fbxSdkManager = null;
        scene = null;

        initializeFbxSdkObjects();
    }

    public boolean initializeFbxSdkObjects() {
        // The first thing to do is to create the FBX SDK manager which is the
        // object allocator for almost all the classes in the SDK.
        // Only one FBX SDK manager can be created. Any subsequent call to
        // createFbxSdkManager() will return NULL.

        // This is just a placeholder, as you need to use a library for FBX handling
        fbxSdkManager = new Object();

        if (fbxSdkManager == null) {
            System.err.println("Unable to create the FBX SDK manager");
            return false;
        }

        // Create the entity that will hold the scene.
        // This is just a placeholder, as you need to use a library for FBX handling
        scene = new Object();
        return true;
    }

    public boolean destroyFbxSdkObjects() {
        // Delete the FBX SDK manager. All the objects that have been allocated
        // using the FBX SDK manager and that haven't been explicitly destroyed
        // are automatically destroyed at the same time.
        if (fbxSdkManager != null) {
            fbxSdkManager = null;
        }
        return true;
    }
}
