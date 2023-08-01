import java.util.concurrent.Semaphore;

// You will need to create these classes/interfaces or use external libraries to implement the required functionality
class DMA_TypeDef {
    // ...
}

class DMA_Stream_TypeDef {
    // ...
}

class Irq {
    // ...
}

public class DmaStream {
    private int streamId, dmaId;
    private DMA_TypeDef dma;
    private DMA_Stream_TypeDef stream;

    private Semaphore[][] dmaSem = new Semaphore[8][2];

    public DmaStream(int dmaId, int streamId, int channel) {
        this.streamId = streamId;
        this.dmaId = dmaId;
        // Initialize the Semaphores
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 2; j++) {
                dmaSem[i][j] = new Semaphore(0);
            }
        }

        // DMA configuration
        // ...

        // Enable Irq
        // ...
    }

    // Other methods
    // ...
}
