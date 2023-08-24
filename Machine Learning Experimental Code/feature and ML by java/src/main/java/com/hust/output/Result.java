package com.hust.output;

import java.util.Map;

public interface Result {
    public double getScalarResult();

    public Map<String, Double> getDictResult();
}
