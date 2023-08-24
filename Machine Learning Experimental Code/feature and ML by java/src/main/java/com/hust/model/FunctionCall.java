package com.hust.model;

public class FunctionCall {
    public String name;
    public int startLine;
    public int endLine;

    public FunctionCall(String name, int startLine, int endLine) {
        this.name = name;
        this.startLine = startLine;
        this.endLine = endLine;
    }
}
