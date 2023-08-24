package com.hust.output;

import java.util.HashMap;
import java.util.Map;

public class ScalarResult implements Result {
    private double value = 0;

    public ScalarResult(double value) {
        this.value = value;
    }

    @Override
    public double getScalarResult() {
        return value;
    }

    @Override
    public Map<String, Double> getDictResult() {
        Map<String, Double> rtn = new HashMap<>();
        return rtn;
    }
}