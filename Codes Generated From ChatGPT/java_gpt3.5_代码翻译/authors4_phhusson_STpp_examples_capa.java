import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException, InterruptedException {
        System.out.println("startup");

        Capa capa = new Capa();

        capa.add(GpioD.PIN_0)
            .add(GpioD.PIN_1)
            .add(GpioD.PIN_2);

        capa.update();

        Mean[] slow = {new Mean(4), new Mean(4), new Mean(4)};
        Mean[] fast = {new Mean(1), new Mean(1), new Mean(1)};

        LedO.setDutyCycle(0);
        LedG.setDutyCycle(0);
        LedB.setDutyCycle(0);
        LedR.setDutyCycle(0);
        int[] len = {0, 0, 0};
        while (true) {

            capa.update();

            for (int i = 0; i < 3; ++i) {
                slow[i].add(capa.get(i));
                fast[i].add(capa.get(i));
            }
            LedB.setDutyCycle(0);
            if (capa.get(1) > 14800)
                LedB.setDutyCycle(100);


            for (int i = 0; i < 3; ++i) {
                int d;
                d = fast[i].get() - slow[i].get();
                if (d > 15) {
                    switch (i) {
                        case 0:
                            LedG.setDutyCycle(100);
                            break;
                        case 1:
                            // LedO.setDutyCycle(100);
                            break;
                        case 2:
                            // LedR.setDutyCycle(100);
                            break;
                    }
                }
                if (d < -20) {
                    ++len[i];
                    System.out.println("Fast " + fast[i].get() +
                            " Slow " + slow[i].get() +
                            " Delta " + d +
                            " Len " + len[i] +
                            " Instant " + capa.get(i));
                    switch (i) {
                        case 0:
                            LedG.setDutyCycle(0);
                            break;
                        case 1:
                            // LedO.setDutyCycle(0);
                            break;
                        case 2:
                            LedR.setDutyCycle(0);
                            break;
                    }
                } else {
                    if (len[i] != 0) {
                        System.out.println("Fast " + fast[i].get() +
                                " Slow " + slow[i].get() +
                                " Delta " + d +
                                " Len " + len[i] +
                                " Instant " + capa.get(i));
                    }
                    len[i] = 0;
                }
            }
        }
    }
}
