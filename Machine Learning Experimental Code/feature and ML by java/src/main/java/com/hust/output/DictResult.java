package com.hust.output;

import java.util.Map;

public class DictResult implements Result {
    private Map<String, Double> value;

    public DictResult(Map<String, Double> value) {
        this.value = value;
    }

    @Override
    public double getScalarResult() {
        return 0;
    }

    @Override
    public Map<String, Double> getDictResult() {
        return value;
    }
}
