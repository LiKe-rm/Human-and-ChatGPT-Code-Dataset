import java.util.*;

public class XsiFtkGeometryUtil {

    public static double[] transformAndConvertVector(Transform transform, Vector3D vector3D) {
        double[] vertPos = new double[3];

        if (transform == null || vector3D == null) {
            return vertPos; // failed
        }

        Matrix4x4 transMatrix4 = transform.getMatrix();
        Vector4D vector4Dtrans = transMatrix4.multiply(vector3D);

        vertPos[0] = vector4Dtrans.getX();
        vertPos[1] = vector4Dtrans.getY();
        vertPos[2] = vector4Dtrans.getZ();

        return vertPos;
    }

    public static boolean setModelDefaultAttributes(Model model, String name) {
        Vector3D defaultVector = new Vector3D(1.0, 1.0, 1.0);

        model.setName(name);
        model.setVisibility(true);
        model.getTransform().setScale(defaultVector);

        // Custom pSet: Mesh_Subdivision_Info
        addSubdivisionPSet(model);

        return true;
    }

    public static CustomPSet addCustomPSet(Template template) {
        CustomPSet newPSet = template.addCustomPSet();
        newPSet.setName("MyCustomPSet");

        // add a parameter
        VariantParameter newParameter = newPSet.addParameter();
        newParameter.setName("MyParameter");

        TinyVariant variant = new TinyVariant();
        variant.setType(TinyVariant.Type.PCHAR);
        variant.setValue("MyVariantValue");

        newParameter.setValue(variant);

        // add a second parameter
        VariantParameter newParameter2 = newPSet.addParameter();
        newParameter2.setName("MyParameter2");

        TinyVariant variant2 = new TinyVariant();
        variant2.setType(TinyVariant.Type.DOUBLE);
        variant2.setValue(0.12345);

        newParameter2.setValue(variant2);

        CustomPSet newPSet2 = template.addCustomPSet();
        newPSet2.setName("MyCustomPSet2");

        // add custom parameter info
        XsiCustomParamInfo info = newPSet.createCustomParamInfo(1);

        TinyVariant range = new TinyVariant();
        range.setType(TinyVariant.Type.DOUBLE);
        range.setValue(10.0);
        info.setMaxValue(range);

        range.setValue(0.0);
        info.setMinValue(range);

        return newPSet;
    }

    public static boolean addSubdivisionPSet(Model model) {
        // TODO
        return true;
    }
}
