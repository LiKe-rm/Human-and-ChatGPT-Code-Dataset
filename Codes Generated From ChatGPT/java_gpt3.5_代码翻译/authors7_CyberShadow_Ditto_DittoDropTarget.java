import java.awt.Point;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import javax.swing.JComponent;
import javax.swing.TransferHandler;

public class DittoDropTarget extends TransferHandler {

    private DropTargetInterface target;

    public DittoDropTarget() {
        this.target = null;
    }

    public void setDropTarget(DropTargetInterface target) {
        this.target = target;
    }

    @Override
    public boolean canImport(TransferHandler.TransferSupport support) {
        if (target != null) {
            return target.canImport(support.getDataFlavors());
        }

        return super.canImport(support);
    }

    @Override
    public boolean importData(TransferHandler.TransferSupport support) {
        if (target != null && support.isDrop()) {
            Transferable transferable = support.getTransferable();
            Point dropLocation = support.getDropLocation().getDropPoint();
            return target.onDrop(transferable, dropLocation);
        }

        return super.importData(support);
    }

    public interface DropTargetInterface {
        boolean canImport(DataFlavor[] dataFlavors);

        boolean onDrop(Transferable transferable, Point point);
    }

    public static void main(String[] args) {
        // Example usage of the DittoDropTarget class:
        // 1. Create a Swing component (e.g., JPanel) that will act as the drop target
        // 2. Create an instance of a class that implements the DropTargetInterface
        // 3. Create an instance of DittoDropTarget and set the drop target
        // 4. Set the DittoDropTarget as the transfer handler of the Swing component
    }
}
