package com.hust.model;

public class Variable {
    public String name;
    public int line;
    public int column;
    public String type;

    public Variable(String name, String type) {
        this.name = name;
        this.type = type;
    }

    public Variable(String name, String type, int line, int column) {
        this.name = name;
        this.type = type;
        this.line = line;
        this.column = column;
    }
}
