// You may need to create these classes/interfaces or use external libraries to implement
// the required functionality.
class Adc {
    enum Samples {
        N_3, N_15, N_28, N_56, N_84, N_112, N_144, N_480
    }

    public Adc() {
        // Enable ADC
        // ADC1->CR2 |= ADC_CR2_ADON;
        // ...

        // Set TSVREFE bit
        // ADC->CCR|= ADC_CCR_TSVREFE;
        // ...

        // Clock = APB1/8
        // ADC->CCR |= 2 << 16;
        // ...
    }

    public void setSamples(int chan, Samples s) {
        // ...
    }

    public int oneShot(int chan) {
        // Enable ADC clock
        // ...

        // Only one conversion
        // ADC1->SQR1 = 0;
        // ADC1->SQR3 = chan;
        // ...

        // 12 bits
        // ADC1->CR1 &= 3 << 24;
        // ...

        // Trigger
        // ADC1->CR2 |= ADC_CR2_SWSTART;
        // ...

        // Wait for end of conversion
        // while (!(ADC1->SR & ADC_SR_EOC));
        // ...

        // Read data
        // unsigned int val = ADC1->DR & 0xfff;
        // ADC1->CR2 &= ~ADC_CR2_SWSTART;

        // For demonstration purposes only, return a dummy value
        return 0;
    }

    public float getTemperature() {
        setSamples(16, Samples.N_480);
        int ret = oneShot(16);

        // Temp = (vsense - v25) / avg_slope + 25
        // return ret;

        // For demonstration purposes only, return a dummy value
        return 0.0f;
    }
}

public class Main {
    public static void main(String[] args) {
        Adc adc = new Adc();
        float temperature = adc.getTemperature();
        System.out.println("Temperature: " + temperature);
    }
}
