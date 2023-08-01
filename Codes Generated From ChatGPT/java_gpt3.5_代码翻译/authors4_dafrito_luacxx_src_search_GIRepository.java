import jnr.ffi.LibraryLoader;
import jnr.ffi.Pointer;
import jnr.ffi.Runtime;
import jnr.ffi.Struct;
import jnr.ffi.annotations.In;
import jnr.ffi.annotations.Out;
import jnr.ffi.byref.IntByReference;

public class GIRepository {
    public interface GObjectIntrospection {
        Pointer g_irepository_get_default();
        Pointer g_irepository_require(Pointer self, String namespace, String version, int flags, Pointer error);
        int g_irepository_get_n_infos(Pointer self, String namespace);
        Pointer g_irepository_get_info(Pointer self, String namespace, int index);
        String g_base_info_get_name(Pointer info);
        int g_base_info_get_type(Pointer info);
        void g_base_info_unref(Pointer info);
        Pointer g_irepository_get_loaded_namespaces(Pointer self);
        void g_free(Pointer ptr);
    }

    public static void main(String[] args) {
        GObjectIntrospection gi = LibraryLoader.create(GObjectIntrospection.class)
                .load("girepository-1.0");

        Pointer repository = gi.g_irepository_get_default();
        Pointer gtkNamespace = gi.g_irepository_require(repository, "Gtk", null, 0, null);

        if (gtkNamespace != null) {
            int nInfos = gi.g_irepository_get_n_infos(repository, "Gtk");

            for (int i = 0; i < nInfos; ++i) {
                Pointer info = gi.g_irepository_get_info(repository, "Gtk", i);
                String entryName = gi.g_base_info_get_name(info);
                int infoType = gi.g_base_info_get_type(info);
                System.out.println(entryName + ": " + infoType);
                gi.g_base_info_unref(info);
            }
        }

        Pointer namespaceList = gi.g_irepository_get_loaded_namespaces(repository);
        for (int i = 0; namespaceList.getPointer(i * Pointer.SIZE) != null; i++) {
            String namespace = namespaceList.getPointer(i * Pointer.SIZE).getString(0);
            System.out.println(namespace);
        }

        gi.g_free(namespaceList);
    }
}
